# Historical MQTT Proposal (Deferred)

This file is retained as earlier design history. **Core v0.2 does not use MQTT.** The implemented prototype uses direct HTTP POST as documented in `docs/core-v0.2.md`. MQTT may be reconsidered later without changing sensor drivers or `WeatherData`.

## Topic Namespace

```text
weather-station/{station_id}
```

Example station ID:

```text
ws-esp32s3-001
```

## Publish Topics

| Topic | QoS | Retain | Purpose |
| --- | ---: | --- | --- |
| `weather-station/{station_id}/telemetry/current` | 1 | No | Full current measurement |
| `weather-station/{station_id}/telemetry/air` | 1 | No | PMS7003 particulate data |
| `weather-station/{station_id}/telemetry/wind` | 1 | No | Wind speed and direction |
| `weather-station/{station_id}/telemetry/rain` | 1 | No | Rain rate and accumulation |
| `weather-station/{station_id}/status` | 1 | Yes | Online, firmware, IP, uptime |
| `weather-station/{station_id}/diagnostics` | 1 | No | Sensor health and error counts |
| `weather-station/{station_id}/ota/status` | 1 | No | OTA state and result |

## Subscribe Topics

| Topic | Purpose |
| --- | --- |
| `weather-station/{station_id}/config/set` | Update runtime config |
| `weather-station/{station_id}/commands/restart` | Controlled reboot |
| `weather-station/{station_id}/commands/sensor/wake` | Wake power-managed sensors |
| `weather-station/{station_id}/commands/sensor/sleep` | Sleep power-managed sensors |

## Current Telemetry Payload

```json
{
  "schema": "weather.current.v1",
  "station_id": "ws-esp32s3-001",
  "timestamp": 1717800000000,
  "location": {
    "latitude": 22.2,
    "longitude": 114.1,
    "altitude_m": 35.2
  },
  "environment": {
    "temperature_c": 28.4,
    "humidity_pct": 74.2,
    "pressure_hpa": 1008.6,
    "light_lux": 12500.0,
    "uv_index": 5.2
  },
  "air_quality": {
    "pm1_0_ugm3": 4.0,
    "pm2_5_ugm3": 8.0,
    "pm10_ugm3": 14.0,
    "aqi_category": "good"
  },
  "wind": {
    "speed_ms": 3.1,
    "direction_deg": 142.0
  },
  "rain": {
    "recent_mm": 0.2,
    "daily_mm": 1.4,
    "monthly_mm": 42.8
  },
  "power": {
    "battery_voltage_v": 3.92,
    "solar_voltage_v": 5.78,
    "battery_pct_estimate": 76
  },
  "network": {
    "rssi_dbm": -61
  }
}
```

## Status Payload

```json
{
  "schema": "weather.status.v1",
  "station_id": "ws-esp32s3-001",
  "timestamp": 1717800000000,
  "firmware_version": "0.1.0",
  "uptime_s": 86400,
  "wifi_connected": true,
  "ip": "192.168.1.42",
  "mqtt_connected": true,
  "ntp_synced": true,
  "free_heap_bytes": 182000,
  "storage_free_bytes": 1048576
}
```

## Diagnostics Payload

```json
{
  "schema": "weather.diagnostics.v1",
  "station_id": "ws-esp32s3-001",
  "timestamp": 1717800000000,
  "sensors": [
    {
      "name": "SHT40",
      "state": "ready",
      "last_read_ms": 1717800000000,
      "error_count": 0,
      "last_error": ""
    }
  ]
}
```
