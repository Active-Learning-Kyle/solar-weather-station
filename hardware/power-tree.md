# v0.2 Power Tree

**Evidence level:** design baseline plus synthetic budget; no physical verification.

```mermaid
flowchart LR
    SP[10 W solar-panel planning class] -->|6–24 V input| PM[Waveshare Solar Power Manager D]
    USB[USB-C maintenance input] --> PM
    BAT[Protected 3.7 V 10 Ah battery class] --> PM
    PM -->|5 V regulated| F1[Replaceable fuse / current protection]
    F1 --> MCU[ESP32-S3 DevKitC-1]
    F1 --> SW[Switched field-sensor rail]
    SW --> DC[Required field-sensor voltage conversion]
    DC --> WIND[RS-485 wind sensors]
    MCU -->|3.3 V| I2C[SHT45 + BMP390 + LTR390 + GNSS]
    MCU --> SD[microSD logger]
```

## Controls still required

| Item | v0.2 design rule | Real evidence needed |
|---|---|---|
| Battery | protected reputable pack; restraint; no public access | exact model, datasheet, inspection and temperature/current evidence |
| Fuse/protection | locate near source; rate after peak-current measurement | schematic, part number and fault test |
| Field rail | high-side switching; default off at boot/fault | warm-up and inrush measurement; recovery test |
| Voltage conversion | match exact wind-sensor supply requirement | converter efficiency and thermal test |
| Ground/RS-485 | document common-mode, shield, surge, bias and termination strategy | bench and cable-length evidence |
| Solar | removable connector, polarity protection, strain relief | site irradiance/charge log and weather-safe integration |

Do not connect an unreviewed lithium battery, panel or outdoor cable assembly from this diagram alone.

