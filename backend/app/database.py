import json
import sqlite3
from datetime import datetime, timezone
from pathlib import Path

from .models import Measurement


SCHEMA = """
CREATE TABLE IF NOT EXISTS measurements (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    station_id TEXT NOT NULL,
    server_timestamp TEXT NOT NULL,
    device_timestamp TEXT,
    firmware_version TEXT NOT NULL,
    uptime_ms INTEGER NOT NULL,
    temperature_c REAL,
    humidity_percent REAL,
    pressure_hpa REAL,
    light_lux REAL,
    uv_index REAL,
    pm1_ugm3 REAL,
    pm25_ugm3 REAL,
    pm10_ugm3 REAL,
    wind_speed_mps REAL,
    wind_status TEXT,
    wind_last_modbus_result INTEGER,
    wind_speed_valid INTEGER,
    gnss_state TEXT,
    gnss_communication_ok INTEGER,
    gnss_fix_valid INTEGER,
    gnss_utc TEXT,
    latitude REAL,
    longitude REAL,
    altitude REAL,
    satellites INTEGER,
    gnss_speed_kmph REAL,
    gnss_course_deg REAL,
    gnss_mode TEXT,
    gnss_last_successful_fix_ms INTEGER,
    sht4x_valid INTEGER NOT NULL,
    bmp180_valid INTEGER NOT NULL,
    bh1750_valid INTEGER NOT NULL,
    ltr390_valid INTEGER NOT NULL,
    pms7003_valid INTEGER NOT NULL,
    health_json TEXT NOT NULL
);
CREATE INDEX IF NOT EXISTS idx_measurements_station_time
ON measurements(station_id, server_timestamp DESC);
"""

GNSS_MIGRATION_COLUMNS = {
    "gnss_state": "TEXT",
    "gnss_communication_ok": "INTEGER",
    "gnss_fix_valid": "INTEGER",
    "gnss_utc": "TEXT",
    "latitude": "REAL",
    "longitude": "REAL",
    "altitude": "REAL",
    "satellites": "INTEGER",
    "gnss_speed_kmph": "REAL",
    "gnss_course_deg": "REAL",
    "gnss_mode": "TEXT",
    "gnss_last_successful_fix_ms": "INTEGER",
}

WIND_MIGRATION_COLUMNS = {
    "wind_speed_mps": "REAL",
    "wind_status": "TEXT",
    "wind_last_modbus_result": "INTEGER",
    "wind_speed_valid": "INTEGER",
}


class Database:
    def __init__(self, path: str | Path):
        self.path = Path(path)

    def connect(self) -> sqlite3.Connection:
        connection = sqlite3.connect(self.path, timeout=10)
        connection.row_factory = sqlite3.Row
        return connection

    def initialize(self) -> None:
        self.path.parent.mkdir(parents=True, exist_ok=True)
        with self.connect() as connection:
            connection.executescript(SCHEMA)
            existing_columns = {
                row["name"]
                for row in connection.execute("PRAGMA table_info(measurements)")
            }
            for name, column_type in GNSS_MIGRATION_COLUMNS.items():
                if name not in existing_columns:
                    connection.execute(
                        f"ALTER TABLE measurements ADD COLUMN {name} {column_type}"
                    )
            for name, column_type in WIND_MIGRATION_COLUMNS.items():
                if name not in existing_columns:
                    connection.execute(
                        f"ALTER TABLE measurements ADD COLUMN {name} {column_type}"
                    )

    def insert(self, measurement: Measurement) -> dict:
        server_timestamp = datetime.now(timezone.utc).isoformat().replace("+00:00", "Z")
        device_timestamp = to_utc_text(measurement.device_timestamp) if measurement.device_timestamp else None
        environment = measurement.environment
        particulate = measurement.particulate
        wind = measurement.wind
        gnss = measurement.gnss
        health = measurement.health
        values = (
            measurement.station_id, server_timestamp, device_timestamp,
            measurement.firmware_version, measurement.uptime_ms,
            environment.temperature_c, environment.humidity_percent,
            environment.pressure_hpa, environment.light_lux, environment.uv_index,
            particulate.pm1_ugm3, particulate.pm25_ugm3, particulate.pm10_ugm3,
            wind.speed_mps, wind.status, wind.last_modbus_result,
            health.wind_speed.valid,
            gnss.state, gnss.communication_ok, gnss.fix_valid,
            to_utc_text(gnss.utc) if gnss.utc else None,
            gnss.latitude, gnss.longitude, gnss.altitude_m, gnss.satellites,
            gnss.speed_kmph, gnss.course_deg, gnss.mode,
            gnss.last_successful_fix_ms,
            health.sht4x.valid, health.bmp180.valid, health.bh1750.valid,
            health.ltr390.valid, health.pms7003.valid,
            json.dumps(health.model_dump(), separators=(",", ":")),
        )
        with self.connect() as connection:
            cursor = connection.execute(
                """
                INSERT INTO measurements (
                    station_id, server_timestamp, device_timestamp, firmware_version, uptime_ms,
                    temperature_c, humidity_percent, pressure_hpa, light_lux, uv_index,
                    pm1_ugm3, pm25_ugm3, pm10_ugm3,
                    wind_speed_mps, wind_status, wind_last_modbus_result, wind_speed_valid,
                    gnss_state, gnss_communication_ok, gnss_fix_valid, gnss_utc,
                    latitude, longitude, altitude, satellites,
                    gnss_speed_kmph, gnss_course_deg, gnss_mode,
                    gnss_last_successful_fix_ms,
                    sht4x_valid, bmp180_valid, bh1750_valid, ltr390_valid, pms7003_valid,
                    health_json
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                """,
                values,
            )
            record_id = cursor.lastrowid
        return {"id": record_id, "server_timestamp": server_timestamp}

    def latest(self, station: str | None) -> dict | None:
        query = "SELECT * FROM measurements"
        parameters: list[object] = []
        if station:
            query += " WHERE station_id = ?"
            parameters.append(station)
        query += " ORDER BY server_timestamp DESC, id DESC LIMIT 1"
        with self.connect() as connection:
            row = connection.execute(query, parameters).fetchone()
        return row_to_measurement(row) if row else None

    def history(
        self,
        station: str | None,
        start: datetime | None,
        end: datetime | None,
        limit: int,
    ) -> list[dict]:
        clauses: list[str] = []
        parameters: list[object] = []
        if station:
            clauses.append("station_id = ?")
            parameters.append(station)
        if start:
            clauses.append("server_timestamp >= ?")
            parameters.append(to_utc_text(start))
        if end:
            clauses.append("server_timestamp <= ?")
            parameters.append(to_utc_text(end))
        query = "SELECT * FROM measurements"
        if clauses:
            query += " WHERE " + " AND ".join(clauses)
        query += " ORDER BY server_timestamp DESC, id DESC LIMIT ?"
        parameters.append(limit)
        with self.connect() as connection:
            rows = connection.execute(query, parameters).fetchall()
        return [row_to_measurement(row) for row in rows]


def to_utc_text(value: datetime) -> str:
    if value.tzinfo is None:
        value = value.replace(tzinfo=timezone.utc)
    return value.astimezone(timezone.utc).isoformat().replace("+00:00", "Z")


def row_to_measurement(row: sqlite3.Row) -> dict:
    health = json.loads(row["health_json"])
    health.setdefault("wind_speed", {
        "initialized": False,
        "valid": bool(row["wind_speed_valid"]),
        "stale": True,
        "consecutive_failures": 0,
        "total_failures": 0,
    })
    return {
        "id": row["id"],
        "schema_version": "weather.measurement.v1",
        "station_id": row["station_id"],
        "firmware_version": row["firmware_version"],
        "uptime_ms": row["uptime_ms"],
        "server_timestamp": row["server_timestamp"],
        "device_timestamp": row["device_timestamp"],
        "environment": {
            "temperature_c": row["temperature_c"],
            "humidity_percent": row["humidity_percent"],
            "pressure_hpa": row["pressure_hpa"],
            "light_lux": row["light_lux"],
            "uv_index": row["uv_index"],
        },
        "particulate": {
            "pm1_ugm3": row["pm1_ugm3"],
            "pm25_ugm3": row["pm25_ugm3"],
            "pm10_ugm3": row["pm10_ugm3"],
        },
        "wind": {
            "speed_mps": row["wind_speed_mps"],
            "status": row["wind_status"] or "NOT CONNECTED",
            "last_modbus_result": row["wind_last_modbus_result"],
        },
        "gnss": {
            "state": row["gnss_state"] or "NOT CONNECTED",
            "communication_ok": bool(row["gnss_communication_ok"]),
            "fix_valid": bool(row["gnss_fix_valid"]),
            "utc": row["gnss_utc"],
            "latitude": row["latitude"],
            "longitude": row["longitude"],
            "altitude_m": row["altitude"],
            "satellites": row["satellites"],
            "speed_kmph": row["gnss_speed_kmph"],
            "course_deg": row["gnss_course_deg"],
            "mode": row["gnss_mode"],
            "last_successful_fix_ms": row["gnss_last_successful_fix_ms"],
        },
        "health": health,
    }
