# First Deliverable: Architecture Review Pack (Historical)

> **Historical design record:** This document contains early proposed structure and capabilities, not the current implementation. For verified status use the [README](../README.md) and [milestone records](milestones/). MQTT, forecasting, rain, power telemetry, GNSS, wind, SD logging, OTA, and several proposed folders below are not implemented in the v0.2 production prototype.

## 1. Complete Project Folder Structure

```text
Weather Station Project/
├── README.md
├── backend/
│   ├── app/
│   │   ├── api/
│   │   ├── db/
│   │   ├── ingest/
│   │   ├── ml/
│   │   └── services/
│   ├── tests/
│   └── requirements.txt
├── data/
│   ├── exports/
│   ├── samples/
│   └── weather.sqlite
├── docs/
│   ├── first-deliverable.md
│   ├── mqtt-and-json.md
│   ├── pin-allocation.md
│   └── task-architecture.md
├── firmware/
│   ├── include/
│   │   ├── app_config.h
│   │   ├── weather_data.h
│   │   ├── sensor_status.h
│   │   └── pins.h
│   ├── lib/
│   │   ├── sensors/
│   │   ├── communication/
│   │   ├── logging/
│   │   ├── statistics/
│   │   └── web/
│   ├── src/
│   │   ├── main.cpp
│   │   └── tasks/
│   ├── test/
│   └── platformio.ini
├── frontend/
│   ├── static/
│   │   ├── css/
│   │   └── js/
│   └── templates/
└── hardware/
    ├── bom.md
    ├── wiring.md
    └── power-system.md
```

Implementation note: the physical workspace currently contains the major folders and documentation scaffold. Nested module files should be added after architecture review.

## 2. ESP32-S3 Pin Allocation

Primary pin table is in [pin-allocation.md](pin-allocation.md).

Design assumptions:

- One shared I2C bus for SHT40, BMP180, BH1750, and LTR390.
- Separate UARTs for PMS7003, NEO-M8N GPS, and RS485 Modbus when available.
- RS485 wind speed and direction sensors share one Modbus RTU bus with distinct slave IDs.
- Rain gauge uses an interrupt-capable GPIO with internal or external pull-up.
- 12V wind sensors require a separate boost converter or 12V rail controlled from the ESP32 through a MOSFET/load switch.

## 3. FreeRTOS Task Architecture

The proposed task model is in [task-architecture.md](task-architecture.md).

High-level tasks:

| Task | Period | Priority | Core | Responsibilities |
| --- | ---: | ---: | ---: | --- |
| SensorManagerTask | 30 s base loop | 3 | 1 | Read environmental sensors, coordinate PMS/GPS/wind polling, validate readings |
| WindPollTask | 10 s | 4 | 1 | Poll RS485 wind speed and direction sensors |
| RainGauge ISR + RainTask | Event + 10 s | ISR/3 | 1 | Count pulses, debounce, calculate rainfall rate and accumulation |
| StatisticsTask | 60 s | 2 | 1 | Hourly/daily averages, min/max, rainfall totals |
| CommunicationTask | 10 s / event | 3 | 0 | WiFi, MQTT, REST, NTP sync, reconnect logic |
| DataLoggerTask | 60 s | 2 | 1 | Store CSV/JSON to SD or LittleFS |
| WebServerTask | Event-driven | 2 | 0 | Serve dashboard and API endpoints |
| OtaTask | Event-driven | 2 | 0 | Handle OTA update flow |
| SystemHealthTask | 30 s | 1 | 0 | Heap, uptime, WiFi RSSI, sensor diagnostics |

## 4. Sensor Driver Abstraction Layer

Use a common interface so tasks do not depend directly on individual sensor libraries.

```cpp
enum class SensorState
{
    NotInitialized,
    Ready,
    Warning,
    Error,
    Sleeping
};

struct SensorDiagnostic
{
    const char* name;
    SensorState state;
    uint32_t lastReadMs;
    uint32_t errorCount;
    const char* lastError;
};

class ISensor
{
public:
    virtual ~ISensor() = default;
    virtual bool begin() = 0;
    virtual bool read(WeatherData& data) = 0;
    virtual SensorDiagnostic diagnostic() const = 0;
};
```

Recommended concrete classes:

| Class | Source File | Interface | Notes |
| --- | --- | --- | --- |
| Sht40Sensor | `src/sensors/Sht40Sensor.*` | I2C | Temperature and humidity |
| Bmp180Sensor | `src/sensors/Bmp180Sensor.*` | I2C | Pressure and sensor temperature |
| Bh1750Sensor | `lib/sensors/Bh1750Sensor.*` | I2C | Lux |
| Ltr390Sensor | `lib/sensors/Ltr390Sensor.*` | I2C | UV index and raw UV |
| Pms7003Sensor | `lib/sensors/Pms7003Sensor.*` | UART | Sleep/wake support |
| GpsSensor | `lib/sensors/GpsSensor.*` | UART | Latitude, longitude, UTC, altitude |
| ModbusWindSensor | `lib/sensors/ModbusWindSensor.*` | RS485 | Wind speed and direction via slave IDs |
| RainGauge | `lib/sensors/RainGauge.*` | GPIO interrupt | Pulse counting and accumulation |

## 5. PlatformIO Configuration

Current config is in [firmware/platformio.ini](../firmware/platformio.ini).

Target environment:

- Platform: Espressif 32
- Board: ESP32-S3 DevKitC-1 class board
- Framework: Arduino
- Filesystem: LittleFS initially, SD card optional
- Monitor speed: 115200
- OTA: enabled later through `ArduinoOTA` or authenticated HTTP update endpoint

## 6. MQTT Topic Structure

The earlier MQTT/schema proposal is in [mqtt-and-json.md](mqtt-and-json.md).

Base topic:

```text
weather-station/{station_id}
```

Topics:

```text
weather-station/{station_id}/telemetry/current
weather-station/{station_id}/telemetry/air
weather-station/{station_id}/telemetry/wind
weather-station/{station_id}/telemetry/rain
weather-station/{station_id}/status
weather-station/{station_id}/diagnostics
weather-station/{station_id}/config/get
weather-station/{station_id}/config/set
weather-station/{station_id}/ota/status
```

## 7. JSON Payload Schema

Canonical current weather payload:

```json
{
  "station_id": "ws-esp32s3-001",
  "timestamp": 1717800000000,
  "temperature_c": 28.4,
  "humidity_pct": 74.2,
  "pressure_hpa": 1008.6,
  "light_lux": 12500.0,
  "uv_index": 5.2,
  "pm1_0_ugm3": 4.0,
  "pm2_5_ugm3": 8.0,
  "pm10_ugm3": 14.0,
  "wind_speed_ms": 3.1,
  "wind_direction_deg": 142.0,
  "rainfall_mm": 0.2,
  "latitude": 22.2,
  "longitude": 114.1,
  "battery_voltage_v": 3.92,
  "solar_voltage_v": 5.78,
  "rssi_dbm": -61
}
```

## 8. Web Dashboard Architecture

The ESP32 dashboard should be useful but lightweight. A richer analytics dashboard can run on the backend.

ESP32-served dashboard:

- `/` serves current-condition dashboard.
- `/api/current` returns latest `WeatherData` JSON.
- `/api/history?hours=24` returns decimated history suitable for charts.
- `/api/status` returns firmware, WiFi, heap, storage, and sensor health.
- `/update` exposes authenticated OTA update page or API.

Frontend components:

| Component | Data Source | Notes |
| --- | --- | --- |
| Live cards | `/api/current` | Temperature, humidity, pressure, UV, PM2.5, wind, rain |
| 24-hour charts | `/api/history?hours=24` | Chart.js line charts |
| Wind rose | `/api/history?hours=24&type=wind` | Direction bins |
| AQI indicator | `/api/current` | Derived from PM2.5 |
| System status | `/api/status` | Sensor diagnostics and power |

Backend dashboard:

- Flask or FastAPI ingests MQTT/HTTP data.
- SQLite stores raw readings and hourly rollups.
- scikit-learn trains simple linear regression models off-device.
- Backend exposes prediction endpoints for temperature, humidity, and pressure trend.

## Review Decisions Needed

1. Confirm the exact ESP32-S3 development board model.
2. Confirm RS485 wind sensor Modbus register maps and slave IDs.
3. Confirm rain gauge bucket size in mm per tip.
4. Confirm whether SD card hardware is included or LittleFS is the first storage target.
5. Confirm whether MQTT broker is local, cloud-hosted, or running on Raspberry Pi.
6. Confirm whether the backend should be Flask or FastAPI.
