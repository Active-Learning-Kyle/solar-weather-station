# Core Integrated Prototype v0.1

Core v0.1 initializes the shared I2C bus, scans it once, initializes each environmental driver independently, starts PMS7003 UART, and uses `millis()` scheduling. Environmental reads run every 5 seconds, PMS acquisition every 10 seconds with a bounded 1.5-second timeout, and a structured snapshot prints every 10 seconds.

`WeatherData` is the single measurement model. Each active subsystem has `SensorHealth` containing initialization state, latest-value validity, staleness, last successful read time, consecutive failures, and total failures. Consumers must check health before using a numeric field; genuine zero remains valid while unavailable data prints as `unavailable`.

Disconnected I2C devices do not abort startup and their initialization is retried on later environmental cycles. PMS checksum/length/header validation remains in the existing parser. GNSS, RS485, rain, power telemetry, and Wi-Fi are not initialized by the core application.

Expected startup I2C addresses are SHT4x `0x44`, BMP180 `0x77`, BH1750 `0x23` or `0x5C`, and LTR390 `0x53`. The code names the family SHT4x because the exact SHT40/SHT41 fitted variant has not been independently established; the existing Adafruit SHT4x driver is retained.

v0.2 subsequently implemented this boundary: it consumes a `WeatherData` snapshot after health/validation, serializes invalid or stale fields as JSON `null`, and keeps networking out of sensor drivers. See the [v0.1 milestone record](milestones/v0.1-core-sensors.md) for the engineering history and [v0.2 implementation notes](core-v0.2.md) for the connected path.
