# FreeRTOS Task Architecture (Early Proposal)

> **Status:** Historical/planned design, not the v0.3 runtime architecture. The current implementation uses the `main.cpp` scheduler plus dedicated HTTP-upload and GNSS workers. See the [README architecture](../README.md#architecture) and [v0.3 milestone](milestones/v0.3-gnss-integration.md).

## Data Flow

```text
Sensor drivers
    ↓
SensorManagerTask / WindPollTask / RainTask
    ↓
WeatherData queue + latest reading mutex
    ↓
StatisticsTask ──→ hourly/daily aggregates
    ↓
DataLoggerTask ──→ CSV/JSON storage
    ↓
CommunicationTask ──→ MQTT + REST sync
    ↓
Dashboard API ──→ browser UI
```

## Shared Data Objects

```cpp
struct WeatherData
{
    float temperature;
    float humidity;
    float pressure;
    float lightLux;
    float uvIndex;
    float pm1_0;
    float pm2_5;
    float pm10;
    float windSpeed;
    float windDirection;
    float rainfall;
    double latitude;
    double longitude;
    uint64_t timestamp;
};
```

Recommended synchronization:

| Shared Resource | Protection |
| --- | --- |
| Latest `WeatherData` | Mutex |
| Log queue | FreeRTOS queue |
| MQTT publish queue | FreeRTOS queue |
| Rain pulse counter | ISR-safe atomic or critical section |
| Sensor diagnostics | Mutex or immutable snapshot queue |
| Configuration | Preferences with mutex |

## Task Details

| Task | Trigger | Output |
| --- | --- | --- |
| SensorManagerTask | 30 s periodic timer | Latest weather snapshot, publish/log queue entries |
| WindPollTask | 10 s periodic timer | Wind speed/direction fields |
| RainTask | 10 s periodic timer plus ISR count | Rain rate, daily/monthly accumulation |
| StatisticsTask | 60 s periodic timer | Hourly and daily rollups |
| DataLoggerTask | Queue-driven | CSV/JSON files |
| CommunicationTask | Queue-driven plus reconnect timer | MQTT publishes and NTP updates |
| WebServerTask | HTTP events | Dashboard/API responses |
| OtaTask | HTTP/OTA events | Firmware update |
| SystemHealthTask | 30 s periodic timer | Diagnostics and status payload |

## Timing Rules

- Use `vTaskDelayUntil()` for periodic tasks.
- Avoid blocking delays in sensor drivers.
- PMS7003 may need wake and stabilization timing; model this with a small state machine.
- RS485 polling should include timeouts and retries without blocking the full sensor manager.
- Network reconnects should use exponential backoff.

## Failure Handling

| Failure | Behavior |
| --- | --- |
| Sensor read timeout | Keep previous valid value, flag diagnostic warning |
| Sensor repeated failure | Mark sensor error, continue system operation |
| WiFi disconnected | Buffer readings locally, reconnect with backoff |
| MQTT unavailable | Continue REST/dashboard, queue or drop by policy |
| Storage full | Rotate logs or delete oldest day |
| Invalid NTP time | Use monotonic timestamp and mark time unsynced |

