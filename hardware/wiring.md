# Wiring Overview

The core v0.1 wiring below reflects the current code. Confirm the exact ESP32-S3 board and every breakout's voltage/pin labels before wiring; deferred subsystems remain preliminary.

Start from the [pin allocation](../docs/pin-allocation.md). Labeled prototype views are in the [v0.1 milestone record](../docs/milestones/v0.1-core-sensors.md#9-images-and-evidence).

## Verified v0.1 connections

| Subsystem | ESP32-S3 connection | Notes |
| --- | --- | --- |
| Shared I²C | SDA GPIO8, SCL GPIO9 | 100 kHz; SHT4x, BMP180, BH1750, LTR390 |
| PMS7003 UART | RX GPIO16, TX GPIO17 | Cross TX/RX; 9600 baud |
| PMS7003 SET | GPIO18 | Sleep/wake control |

The Core v0.4 production `weather_station` firmware initializes GNSS and RS485 wind speed in addition to the v0.2 hardware. Wind direction, rain, battery, solar, and SD remain deferred.

## TEL0157 GNSS production and diagnostic wiring

The `diag_gnss` PlatformIO environment targets the DFRobot Gravity TEL0157
(Quectel L76K) in **UART** mode. Move the module's interface selector to
**UART with power removed**, then wire the crossed data lines as follows:

| TEL0157 connection | ESP32-S3 connection | Purpose |
| --- | --- | --- |
| VCC (`+`) | 3V3 | The official module range is 3.3-5.5 V; 3.3 V is used here |
| GND (`-`) | GND | Common signal and power ground |
| TX (`D/T`) | GPIO15 (ESP32 RX, UART1) | GNSS TX -> ESP32 RX |
| RX (`C/R`) | GPIO14 (ESP32 TX, UART1) | GNSS RX -> ESP32 TX |

The included active antenna must be firmly connected to the IPEX1 socket.
Test outdoors or with a clear view of the sky and allow several minutes for a
cold fix. A red module indicator means no fix; green means a fix is acquired.
The diagnostic does not reboot or reconfigure a communicating receiver merely
because it is still waiting for satellites.

### TEL0157 UART direction-field workaround

Real-hardware testing with `DFRobot_GNSS` 1.0.0 returned valid latitude and
longitude magnitudes but invalid `latDirection`/`lonDirection` bytes. The
library's C++ register constants and getter logic differ from its Python
implementation: the C++ direction-register names are reversed, and the C++
getters discard the sixth byte from each six-byte coordinate block before
performing a separate direction read. The project does not patch generated
`.pio/libdeps` files. Instead, the official structured getters remain the
primary data source, while `GnssNmeaHemisphere` extracts only checksum-valid
N/S and E/W fields from official `getAllGnss()` GGA, RMC, or GLL output. A
verified outdoor diagnostics confirmed these NMEA signs for Core v0.3 production
integration. The `diag_gnss` raw and direction-byte output remains available.

## Wiring Rules

- Keep I2C wires short and use pull-ups to 3.3V only.
- Do not connect 5V logic directly to ESP32-S3 GPIO.
- Use a 3.3V-compatible RS485 transceiver.
- Wire RS485 transceiver RO to ESP32-S3 GPIO6, DI to GPIO7, and shared DE/RE control to GPIO5.
- Power 12V wind sensors from a separate boost converter or 12V supply rail.
- Use resistor dividers for battery and solar voltage ADC measurement.
- Add transient protection for outdoor cables where possible.

## RS485 wind-speed production wiring

| Connection | ESP32-S3 / station connection |
| --- | --- |
| Transceiver RO | GPIO6 (UART0 RX in production) |
| Transceiver DI | GPIO7 (UART0 TX in production) |
| Transceiver DE + /RE | GPIO5; LOW receive idle, HIGH transmit |
| Sensor A/B | Transceiver A/B |
| Sensor supply | Correct external 12 V rail |
| Grounds | ESP32, transceiver, and sensor supply common ground |

The fixed sensor protocol is Modbus RTU, 4800 baud, 8N1, slave 1, function `0x03`, holding register `0x0000`, one register, scaled as `raw / 10.0 m/s`. Do not substitute a zero value for a timeout.

## Reproduction sequence

1. With power removed, check every supply and signal against the breakout labels and board schematic.
2. Bring up the shared bus with `diag_i2c`; do not add PMS7003 until all expected addresses appear.
3. Test the PMS7003 separately with `diag_pms`.
4. Install GNSS, flash `diag_gnss`, and independently verify UART, NMEA/checksums, UTC/date, position validity, hemispheres, satellites, altitude, and a fix.
5. Flash `weather_station` only after the sensor, PMS7003, and GNSS interfaces pass in isolation.
6. Use strain relief and recheck continuity after fitting the prototype frame.

The photographed frame is evidence of prototype fit only. It is not verified as weatherproof, UV-resistant, condensation-safe, or an adequate solar-radiation shield.
