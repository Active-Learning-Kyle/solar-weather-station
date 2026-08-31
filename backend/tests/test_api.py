import json
import shutil
import sqlite3
import subprocess
from pathlib import Path

import pytest

from fastapi.testclient import TestClient

from app.main import create_app


def payload(station="ws-test-001"):
    sensor = {"initialized": True, "valid": True, "stale": False, "consecutive_failures": 0, "total_failures": 0}
    return {
        "schema_version": "weather.measurement.v1",
        "station_id": station,
        "firmware_version": "0.3.0",
        "uptime_ms": 123456,
        "device_timestamp": None,
        "environment": {"temperature_c": 24.1, "humidity_percent": 66.3, "pressure_hpa": 994.2, "light_lux": 250.4, "uv_index": 1.2},
        "particulate": {"pm1_ugm3": 3, "pm25_ugm3": 7, "pm10_ugm3": 10},
        "wind": {"speed_mps": 3.6, "status": "OK", "last_modbus_result": 0},
        "gnss": {
            "state": "COMMUNICATION OK - NO FIX",
            "communication_ok": True,
            "fix_valid": False,
            "utc": None,
            "latitude": None,
            "longitude": None,
            "altitude_m": None,
            "satellites": 0,
            "speed_kmph": None,
            "course_deg": None,
            "mode": "GPS + BeiDou + GLONASS",
            "last_successful_fix_ms": None,
        },
        "health": {name: dict(sensor) for name in ("sht4x", "bmp180", "bh1750", "ltr390", "pms7003", "wind_speed")},
    }


def test_database_post_latest_history_and_dashboard(tmp_path):
    database_path = tmp_path / "measurements.db"
    with TestClient(create_app(database_path)) as client:
        assert client.get("/").status_code == 200
        assert "Solar Weather Station" in client.get("/").text
        response = client.post("/api/v1/measurements", json=payload())
        assert response.status_code == 201
        assert response.json()["status"] == "stored"
        latest = client.get("/api/v1/measurements/latest", params={"station": "ws-test-001"})
        assert latest.status_code == 200
        assert latest.json()["environment"]["temperature_c"] == 24.1
        assert latest.json()["wind"]["speed_mps"] == 3.6
        history = client.get("/api/v1/measurements", params={"station": "ws-test-001", "limit": 10})
        assert history.status_code == 200
        assert len(history.json()) == 1
        assert history.json()[0]["wind"]["speed_mps"] == 3.6
    assert database_path.exists()
    with sqlite3.connect(database_path) as connection:
        assert connection.execute("SELECT COUNT(*) FROM measurements").fetchone()[0] == 1


def test_malformed_post_is_rejected(tmp_path):
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.post("/api/v1/measurements", json={"station_id": "incomplete"}).status_code == 422
        invalid = payload()
        invalid["uptime_ms"] = -1
        assert client.post("/api/v1/measurements", json=invalid).status_code == 422


def test_unavailable_values_are_stored_as_null(tmp_path):
    unavailable = payload()
    unavailable["environment"] = {key: None for key in unavailable["environment"]}
    unavailable["particulate"] = {key: None for key in unavailable["particulate"]}
    unavailable["wind"] = {"speed_mps": None, "status": "TIMEOUT", "last_modbus_result": 0xE2}
    for sensor in unavailable["health"].values():
        sensor["valid"] = False
        sensor["stale"] = True
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.post("/api/v1/measurements", json=unavailable).status_code == 201
        latest = client.get("/api/v1/measurements/latest", params={"station": "ws-test-001"})
        assert latest.json()["environment"]["temperature_c"] is None
        assert latest.json()["gnss"]["latitude"] is None
        assert latest.json()["gnss"]["longitude"] is None
        assert latest.json()["wind"] == {
            "speed_mps": None,
            "status": "TIMEOUT",
            "last_modbus_result": 0xE2,
        }


def test_zero_wind_speed_is_a_valid_measurement(tmp_path):
    calm = payload()
    calm["wind"]["speed_mps"] = 0.0
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.post("/api/v1/measurements", json=calm).status_code == 201
        latest = client.get("/api/v1/measurements/latest", params={"station": "ws-test-001"})
        assert latest.json()["wind"]["speed_mps"] == 0.0
        assert latest.json()["health"]["wind_speed"]["valid"] is True


def test_v03_payload_without_wind_remains_compatible(tmp_path):
    legacy = payload()
    legacy.pop("wind")
    legacy["health"].pop("wind_speed")
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.post("/api/v1/measurements", json=legacy).status_code == 201
        latest = client.get("/api/v1/measurements/latest", params={"station": "ws-test-001"}).json()
        assert latest["wind"]["speed_mps"] is None
        assert latest["wind"]["status"] == "NOT CONNECTED"
        assert latest["health"]["wind_speed"]["valid"] is False


def test_valid_gnss_record_round_trips(tmp_path):
    valid = payload()
    valid["gnss"] = {
        "state": "FIX VALID",
        "communication_ok": True,
        "fix_valid": True,
        "utc": "2026-08-19T09:03:42Z",
        "latitude": 22.2,
        "longitude": 114.1,
        "altitude_m": 65.7,
        "satellites": 21,
        "speed_kmph": 0.1,
        "course_deg": 184.2,
        "mode": "GPS + BeiDou + GLONASS",
        "last_successful_fix_ms": 120000,
    }
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.post("/api/v1/measurements", json=valid).status_code == 201
        stored = client.get(
            "/api/v1/measurements/latest", params={"station": "ws-test-001"}
        ).json()["gnss"]
        assert stored["fix_valid"] is True
        assert stored["latitude"] == 22.2
        assert stored["longitude"] == 114.1
        assert stored["satellites"] == 21
        assert stored["mode"] == "GPS + BeiDou + GLONASS"


def test_existing_v02_database_is_extended_without_deleting_records(tmp_path):
    database_path = tmp_path / "legacy.db"
    legacy_health = {
        name: {"initialized": True, "valid": True, "stale": False,
               "consecutive_failures": 0, "total_failures": 0}
        for name in ("sht4x", "bmp180", "bh1750", "ltr390", "pms7003")
    }
    with sqlite3.connect(database_path) as connection:
        connection.execute(
            """
            CREATE TABLE measurements (
                id INTEGER PRIMARY KEY AUTOINCREMENT, station_id TEXT NOT NULL,
                server_timestamp TEXT NOT NULL, device_timestamp TEXT,
                firmware_version TEXT NOT NULL, uptime_ms INTEGER NOT NULL,
                temperature_c REAL, humidity_percent REAL, pressure_hpa REAL,
                light_lux REAL, uv_index REAL, pm1_ugm3 REAL, pm25_ugm3 REAL,
                pm10_ugm3 REAL, sht4x_valid INTEGER NOT NULL,
                bmp180_valid INTEGER NOT NULL, bh1750_valid INTEGER NOT NULL,
                ltr390_valid INTEGER NOT NULL, pms7003_valid INTEGER NOT NULL,
                health_json TEXT NOT NULL
            )
            """
        )
        connection.execute(
            """
            INSERT INTO measurements VALUES (
                NULL, 'legacy-station', '2026-08-18T00:00:00Z', NULL,
                '0.2.0', 1000, 24.0, 60.0, 1000.0, 100.0, 1.0,
                1.0, 2.0, 3.0, 1, 1, 1, 1, 1, ?
            )
            """,
            (json.dumps(legacy_health),),
        )

    with TestClient(create_app(database_path)) as client:
        latest = client.get(
            "/api/v1/measurements/latest", params={"station": "legacy-station"}
        )
        assert latest.status_code == 200
        assert latest.json()["firmware_version"] == "0.2.0"
        assert latest.json()["gnss"]["latitude"] is None
        assert latest.json()["wind"]["speed_mps"] is None

    with sqlite3.connect(database_path) as connection:
        columns = {row[1] for row in connection.execute("PRAGMA table_info(measurements)")}
        assert {"latitude", "longitude", "altitude", "satellites",
                "gnss_fix_valid", "gnss_mode", "wind_speed_mps",
                "wind_status", "wind_speed_valid"} <= columns
        assert connection.execute("SELECT COUNT(*) FROM measurements").fetchone()[0] == 1


def test_latest_missing_station_returns_404(tmp_path):
    with TestClient(create_app(tmp_path / "test.db")) as client:
        assert client.get("/api/v1/measurements/latest", params={"station": "missing"}).status_code == 404


def test_dashboard_contains_wind_panel_and_trend(tmp_path):
    with TestClient(create_app(tmp_path / "test.db")) as client:
        dashboard = client.get("/")
        assert dashboard.status_code == 200
        assert "<legend>Wind</legend>" in dashboard.text
        script = client.get("/static/dashboard.js")
        assert script.status_code == 200
        assert "Wind Speed" in script.text
        assert "speed_mps" in script.text


def test_dashboard_javascript_syntax():
    node = shutil.which("node")
    if node is None:
        pytest.skip("Node.js is not installed")
    script = Path(__file__).parents[1] / "app" / "static" / "dashboard.js"
    result = subprocess.run([node, "--check", str(script)], capture_output=True, text=True)
    assert result.returncode == 0, result.stderr
