# Core v0.3 — GNSS Integration

**Status:** Complete / hardware verified. See the [v0.3 milestone record](milestones/v0.3-gnss-integration.md) for staged diagnostic evidence, integrated verification, public image sanitization, and reproduction guidance.

Core v0.3 integrates the verified DFRobot Gravity TEL0157 / Quectel L76K into the production `weather_station` firmware while preserving the Core v0.2 sensor, network, backend, storage, dashboard, and diagnostic paths.

## Production architecture

The official `DFRobot_GNSS` library owns UART1 at 9600 baud. All library probes and reads run in the dedicated priority-1 `gnss-worker` FreeRTOS task. The Arduino scheduler calls `GPSManager::update()`, which only copies a short critical-section-protected snapshot into `WeatherData`. A slow or absent GNSS receiver therefore cannot block environmental sensing, PMS reads, Wi-Fi maintenance, HTTP scheduling, or Serial snapshots.

GNSS is polled every 10 seconds. If no device was detected at boot, a bounded library probe is retried every 60 seconds. Once communication succeeds, power and GPS + BeiDou + GLONASS mode are configured once. A lost fix or later loss of NMEA input does not trigger receiver reset or reconfiguration.

| State | Meaning | Position in JSON |
| --- | --- | --- |
| `NOT CONNECTED` | No current NMEA communication | `null` |
| `COMMUNICATION OK - NO FIX` | Receiver is responding but has never supplied a valid current fix | `null` |
| `FIX VALID` | Current fix passes all validation and is no more than 30 seconds old | Signed values |
| `FIX STALE` | NMEA communication continues, but a previously valid fix is no longer current | `null` |

The last successful values and fix uptime remain in `WeatherData` for diagnostics, but coordinates are serialized only for `FIX VALID`. This keeps a real coordinate of `0.0` distinct from an unavailable coordinate.

## Fix and hemisphere validation

A production fix requires:

- a new checksum-valid, fix-bearing GGA, RMC, or GLL sentence during the current read;
- at least one satellite used;
- valid UTC and calendar fields;
- finite decimal latitude and longitude within ±90°/±180° magnitudes; and
- N/S and E/W recovered from checksum-validated NMEA.

The DFRobot decimal `latitudeDegree` and `lonitudeDegree` getters provide magnitudes. Production code deliberately does not inspect `latDirection` or `lonDirection`, because those bytes are malformed on the verified module/library combination. `S` and `W` negate the decimal magnitudes; `N` and `E` leave them positive. The standalone `diag_gnss` behavior and its raw/NMEA inspection remain preserved.

## JSON extension

The existing `weather.measurement.v1` envelope is extended additively:

```json
{
  "gnss": {
    "state": "FIX VALID",
    "communication_ok": true,
    "fix_valid": true,
    "utc": "2026-01-01T12:00:00Z",
    "latitude": 22.2,
    "longitude": 114.1,
    "altitude_m": 10.0,
    "satellites": 8,
    "speed_kmph": 0.0,
    "course_deg": 0.0,
    "mode": "GPS + BeiDou + GLONASS",
    "last_successful_fix_ms": 120000
  }
}
```

The values above are illustrative schema examples. Coordinates are intentionally coarse and are not the test position or a station configuration.

Latitude, longitude, altitude, speed, and course are `null` unless the fix is current. UTC is the last valid GNSS fix UTC and does not replace NTP: `device_timestamp` continues to use NTP when available.

## Backend and migration

FastAPI accepts and returns the nested `gnss` object. It defaults missing GNSS objects to an unavailable state so Core v0.2 senders remain accepted. SQLite stores GNSS state, communication/fix flags, UTC, latitude, longitude, altitude, satellites, speed, course, mode, and last-successful-fix uptime.

Startup first creates a new table when needed, then inspects `PRAGMA table_info(measurements)` and adds only missing nullable GNSS columns with `ALTER TABLE`. It never drops `measurements` or deletes `weather.db`; existing rows return nullable GNSS values.

The Windows-98-style dashboard adds a compact Location / GNSS group with fix state, satellites, signed coordinates rendered with hemisphere labels, altitude, and UTC. No map, tracking, geofence, external map API, or location-history view is included.

## Hardware verification procedure

1. Remove power. Set the TEL0157 selector to UART and attach the active antenna firmly to the IPEX1 socket.
2. Wire TEL0157 VCC to 3V3, GND to common GND, TX (`D/T`) to ESP32 GPIO15/UART1 RX, and RX (`C/R`) to GPIO14/UART1 TX. Keep PMS7003 on UART2 GPIO16/17.
3. Build and flash `diag_gnss`. Outdoors with a clear sky view, use `status` and `raw`; confirm communication, checksum-valid NMEA, GPS + BeiDou + GLONASS mode, valid UTC/date, N/S and E/W, signed decimal coordinates, and satellites used. Allow several minutes for a cold fix.
4. Flash `weather_station`. Confirm all five pre-existing sensor families still report, Wi-Fi/NTP continue, HTTP returns 201, and Serial progresses through `COMMUNICATION OK - NO FIX` to `FIX VALID` without scheduler pauses.
5. Confirm `/api/v1/measurements/latest` and the dashboard show the expected signed position, satellite count, altitude, and GNSS UTC. Check the new SQLite columns without deleting the existing database.
6. Obscure or disconnect only the antenna while leaving UART connected. Confirm `FIX STALE`, null uploaded coordinates, continued environmental/PMS acquisition, and continued uploads.
7. Disconnect the GNSS module. Confirm `NOT CONNECTED`, null position, and uninterrupted sensing/network/dashboard operation. Reconnect it and confirm periodic reads recover communication without rebooting the station.
8. Restore sky view and confirm `FIX VALID` returns. Power-cycle once for a cold-start test and once shortly afterward for a warm-start test; record time-to-fix and compare the displayed coordinates against a trusted reference.

## Known limitations

- GNSS integration is a stationary current-location display, not tracking.
- Position privacy must be considered before exposing the backend beyond a trusted LAN.
- Fix quality is currently based on fix-bearing NMEA, satellites, time, and coordinate bounds; HDOP is not stored or used as a threshold.
- The 10-second poll, 30-second stale/communication windows, and 60-second initial-probe retry are compile-time settings.
- GNSS UTC is additional telemetry only; NTP remains the device timestamp source.
- Core v0.3 does not integrate wind, rain, battery, solar, maps, geofencing, or route/history visualization.
