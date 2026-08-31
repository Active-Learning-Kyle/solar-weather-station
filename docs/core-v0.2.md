# Core v0.2 networking and remote data

**Status:** Implemented and tested as a local-network prototype. For reproduction evidence and milestone scope, see [v0.2 — Connected IoT Prototype](milestones/v0.2-connected-iot.md).

Core v0.2 adds an optional network consumer after the verified v0.1 `WeatherData` path. It does not change the SHT4x, BMP180, BH1750, LTR390, or PMS7003 drivers.

## Firmware behavior

`NetworkManager::tick()` uses `DISABLED`, `CONNECTING`, `CONNECTED`, `DISCONNECTED`, and `RETRY_WAIT` states. `WiFi.begin()` starts an asynchronous attempt. The scheduler never waits in a connection or NTP loop. A connection attempt times out after 15 seconds and is retried after 30 seconds. NTP is requested after connection and checked without blocking; failure leaves `device_timestamp` null.

`HttpDataUploader` owns a one-element overwrite queue and a FreeRTOS worker. The scheduler copies the current snapshot to the queue every 60 seconds. The worker serializes and posts it with a 3-second connect timeout and 5-second HTTP timeout. It records successful uploads, failed uploads, consecutive failures, last successful upload uptime, and the last response code. There is no immediate retry loop: recovery occurs at the next upload interval.

The one-element queue deliberately represents “latest current conditions,” not an offline spool. Data missed while the backend is down is not backfilled by the ESP32; future successful snapshots resume normal recording.

## JSON schema

Unavailable or stale readings are `null`, so a real zero remains distinct from a failed sensor.

```json
{
  "schema_version": "weather.measurement.v1",
  "station_id": "ws-esp32s3-001",
  "firmware_version": "0.2.0",
  "uptime_ms": 123456,
  "device_timestamp": null,
  "environment": {
    "temperature_c": 24.1,
    "humidity_percent": 66.3,
    "pressure_hpa": 994.2,
    "light_lux": 250.4,
    "uv_index": 1.2
  },
  "particulate": {
    "pm1_ugm3": 3,
    "pm25_ugm3": 7,
    "pm10_ugm3": 10
  },
  "health": {
    "sht4x": {
      "initialized": true,
      "valid": true,
      "stale": false,
      "consecutive_failures": 0,
      "total_failures": 0
    },
    "bmp180": { "initialized": true, "valid": true, "stale": false, "consecutive_failures": 0, "total_failures": 0 },
    "bh1750": { "initialized": true, "valid": true, "stale": false, "consecutive_failures": 0, "total_failures": 0 },
    "ltr390": { "initialized": true, "valid": true, "stale": false, "consecutive_failures": 0, "total_failures": 0 },
    "pms7003": { "initialized": true, "valid": true, "stale": false, "consecutive_failures": 0, "total_failures": 0 }
  }
}
```

When NTP has synchronized, `device_timestamp` is UTC ISO 8601 such as `2026-08-19T10:30:00Z`. The backend always adds its own `server_timestamp`.

## Failure cases

- Wi-Fi unavailable at boot: sensor initialization/reads proceed; Wi-Fi enters timed retry cycles; no reboot occurs.
- Wi-Fi lost: measurements and serial snapshots continue; reconnect happens in `tick()`.
- Backend unavailable or an HTTP timeout occurs: the worker records one failure and waits for the next scheduled snapshot.
- Backend returns non-2xx: the response code and failure counters update; acquisition continues.
- NTP unavailable: uptime and backend receive timestamps remain usable.

## Storage and extension

SQLite stores identifiers, timestamps, firmware/uptime, all eight current measurements, five sensor-valid flags, and full health JSON. Adding nullable columns later for wind, rain, GNSS, battery, and solar does not require changing the current sensor drivers. Prediction is intentionally absent; a future backend module can consume stored history without changing ingestion.
