# Core v0.4 — Wind Speed Integration

**Status:** Production integration implemented and compile/test verified. The standalone `diag_wind_speed` configuration is hardware verified; complete-station hardware verification remains to be performed.

Core v0.4 integrates wind speed only and preserves wind direction as deferred diagnostic work.

## Architecture and UART allocation

```text
Wind-speed sensor -> RS485 transceiver -> RS485Manager -> WeatherData
                  -> JSON -> HTTP -> FastAPI -> SQLite -> dashboard/trends
```

| Function | Production interface |
| --- | --- |
| Debug console | Native USB CDC `Serial`, 115200 baud |
| PMS7003 | UART2, GPIO16 RX / GPIO17 TX, 9600 8N1 |
| TEL0157/L76K GNSS | UART1, GPIO15 RX / GPIO14 TX, 9600 baud |
| RS485 wind speed | UART0, GPIO6 RX / GPIO7 TX, GPIO5 DE/RE, 4800 8N1 |

`weather_station` enables native USB CDC so UART0 can serve RS485 without corrupting Serial Monitor output. `diag_wind_speed` remains on its verified UART1 allocation because GNSS is not initialized in that isolated environment.

## Fixed Modbus configuration

- slave ID `1`;
- function `0x03` (Read Holding Registers);
- register `0x0000`;
- register count `1`;
- scale `raw / 10.0`;
- authoritative unit `m/s`;
- two-second production polling interval in a dedicated `rs485-wind` worker task.

Before transmission, `RS485Manager` drives DE/RE HIGH. Its post-transmission callback flushes the UART, then returns DE/RE LOW so the transceiver normally remains in receive mode.

## Data, health, and failures

`WeatherData` carries `windSpeed`, `windSpeedLastModbusResult`, and `windSpeedHealth`. Health records initialized state, current validity, stale state, total and consecutive failures, and last successful read uptime. The last successful numeric reading is retained internally, but it is serialized only while the current reading is valid and fresh.

This distinction is intentional:

```text
successful raw 0 -> 0.0 m/s (valid)
Modbus timeout   -> null / unavailable (invalid)
```

A failed read changes only wind validity and counters. Blocking Modbus work stays in the dedicated RS485 worker; `main.cpp` copies a short locked snapshot. A timeout therefore does not reboot the ESP32 or hold up I²C, PMS, GNSS coordination, networking, upload scheduling, storage, or dashboard operation. The next scheduled transaction automatically attempts recovery.

## JSON, backend, and storage

The additive `weather.measurement.v1` payload extension is:

```json
{
  "wind": {
    "speed_mps": 3.6,
    "status": "OK",
    "last_modbus_result": 0
  },
  "health": {
    "wind_speed": {
      "initialized": true,
      "valid": true,
      "stale": false,
      "consecutive_failures": 0,
      "total_failures": 0
    }
  }
}
```

Unavailable speed is `null`; status can be `OK`, `CHECK`, `TIMEOUT`, `STALE`, or `NOT CONNECTED`. FastAPI defaults a missing wind object and missing wind health to an unavailable state, retaining compatibility with v0.1–v0.3 payloads.

SQLite startup adds only missing nullable `wind_speed_mps`, `wind_status`, `wind_last_modbus_result`, and `wind_speed_valid` columns with `ALTER TABLE`. It never deletes or recreates `weather.db`; old records return `NULL` speed and `NOT CONNECTED` status.

## Display

The Serial snapshot includes a Wind group plus wind health/Modbus state. The Windows-98-style dashboard adds a compact Wind fieldset, a Wind Speed entry in Sensor Status, and a `Wind Speed (m/s)` line chart using the existing 1-hour, 24-hour, and 7-day trend path.

Wind direction is not serialized, stored, displayed, or plotted. No placeholder `0°` value or compass is present.

## Hardware verification procedure

1. Connect all existing station hardware.
2. Power the 12 V wind-speed sensor correctly.
3. Flash `weather_station`.
4. Confirm environmental, PMS7003, and GNSS functions remain active.
5. Confirm wind speed reads approximately zero/low while stationary.
6. Spin the anemometer or apply airflow.
7. Confirm the Serial wind-speed value increases.
8. Confirm the dashboard updates after the next upload.
9. Confirm SQLite and the latest API contain the wind value.
10. Stop the sensor and confirm it returns toward zero.
11. Briefly disconnect RS485 A/B.
12. Confirm wind becomes unavailable/TIMEOUT without affecting other sensors.
13. Reconnect A/B.
14. Confirm wind communication recovers automatically without rebooting.

## Deferred work

- wind direction (standalone diagnostic preserved);
- rain;
- battery telemetry;
- solar telemetry;
- final power optimization and long-duration field reliability.
