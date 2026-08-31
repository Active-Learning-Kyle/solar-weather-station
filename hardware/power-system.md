# Power System Notes

> **Status:** preliminary design direction. The battery configuration, charger, panel and 12 V conversion path have not completed a measured complete-system power or endurance test.

## Battery

Three 18650 cells in 1S3P:

```text
Nominal voltage: 3.7V
Capacity: about 10200mAh
```

## Solar Charging

Waveshare Solar Power Manager (D):

- USB-C input
- Solar input
- 5V system output
- Power path management
- Simultaneous charge and discharge

## Solar Panel

Planning starting point:

```text
6V 5W
```

## Power Budget Items To Measure

| Load | Voltage | Notes |
| --- | ---: | --- |
| ESP32-S3 active WiFi | 5V input | Major peak current source |
| I2C sensors | 3.3V | Low current |
| PMS7003 | 5V | Use sleep mode |
| GPS | 3.3V/5V | Module-dependent |
| RS485 wind sensors | 12V | Needs boost conversion |
| RS485 transceiver | 3.3V | Low current |

## Evidence required before autonomous operation

1. Record active, idle and peak current for the complete integrated station.
2. Measure each controllable subsystem state rather than relying on datasheet typical values.
3. Include regulator, boost-converter and charging losses.
4. Run a protected battery-only endurance test with recovery and stop conditions.
5. Measure solar input under the intended placement and operating schedule.
6. Compare daily usable energy with the measured load and an explicit reserve margin.
7. Record battery protection, fusing, temperature limits and enclosure ventilation.

Until these checks are complete, the station is a bench-powered prototype and the presence of a solar panel is not evidence of autonomous or sustainable operation.

