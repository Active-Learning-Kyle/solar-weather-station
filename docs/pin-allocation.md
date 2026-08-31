# ESP32-S3 Pin Allocation

This table uses conservative ESP32-S3 DevKit-style pins. Confirm against the exact board schematic before wiring.

## Main Bus Assignments

| Function | ESP32-S3 Pin | Direction | Notes |
| --- | ---: | --- | --- |
| I2C SDA | GPIO8 | Bidirectional | SHT4x, BMP180, BH1750, LTR390 |
| I2C SCL | GPIO9 | Output | 100 kHz initially, 400 kHz after validation |
| PMS7003 UART RX | GPIO16 | Input | ESP32 receives from PMS TX |
| PMS7003 UART TX | GPIO17 | Output | ESP32 transmits to PMS RX |
| PMS7003 SET/Sleep | GPIO18 | Output | Optional sleep control |
| GPS UART RX | GPIO15 | Input | ESP32 receives from GPS TX |
| GPS UART TX | GPIO14 | Output | ESP32 transmits to GPS RX |
| RS485 UART RX | GPIO6 | Input | ESP32 receives from RS485 transceiver RO |
| RS485 UART TX | GPIO7 | Output | ESP32 transmits to RS485 transceiver DI |
| RS485 DE/RE | GPIO5 | Output | Direction control, shared DE and /RE |
| Rain gauge pulse | GPIO4 | Input interrupt | Use pull-up and debounce |
| SD CS | GPIO10 | Output | Optional SPI SD card |
| SPI SCK | GPIO12 | Output | Optional SD |
| SPI MISO | GPIO13 | Input | Optional SD |
| SPI MOSI | GPIO11 | Output | Optional SD |
| Wind 12V enable | GPIO21 | Output | Drives MOSFET/load switch, not sensor directly |
| Status LED | GPIO2 | Output | Optional board LED if available |
| Battery ADC | GPIO1 | Analog input | Through resistor divider |
| Solar ADC | GPIO3 | Analog input | Through resistor divider |

## I2C Address Plan

| Device | Typical Address | Notes |
| --- | ---: | --- |
| SHT4x | `0x44` | Temperature/humidity; exact SHT40/SHT41 variant not asserted |
| BMP180 | `0x77` | Pressure and sensor temperature |
| BH1750 | `0x23` or `0x5C` | Light |
| LTR390 | `0x53` | UV and ALS |

## UART Plan

| UART | Device | Baud | Notes |
| --- | --- | ---: | --- |
| Native USB CDC (`Serial`) | USB monitor | 115200 | Core v0.4 production debug console; consumes no hardware UART |
| UART2 | PMS7003 | 9600 | The only non-console UART active in Core v0.1 |
| UART1 | TEL0157/L76K GNSS | 9600 | Active in Core v0.3; GPIO15 RX, GPIO14 TX |
| UART0 | Wind speed RS485 | 4800 8N1 | Core v0.4 production; GPIO6 RX, GPIO7 TX, GPIO5 DE/RE |
| UART2 | Wind direction RS485 | 4800 8N1 | Isolated `diag_wind_direction` environment |
| UART1 | Wind speed RS485 | 4800 8N1 | Preserved `diag_wind_speed` standalone allocation |

The diagnostic UART reuse is safe because only one PlatformIO environment runs at a time. Core v0.4 resolves simultaneous production use by routing the debug console over the ESP32-S3 native USB CDC interface and assigning UART0 to RS485. The standalone diagnostic remains UART1 and does not run alongside GNSS.

## Power Notes

| Subsystem | Voltage | Control |
| --- | ---: | --- |
| ESP32-S3 | 5V input or 3.3V regulated | From Waveshare 5V system supply |
| I2C sensors | 3.3V | Always on or switched 3.3V rail |
| PMS7003 | 5V | Sleep pin recommended |
| TEL0157/L76K GNSS | 3.3-5.5 V supported; use 3V3 in this project | UART selector position; active in Core v0.3 |
| RS485 wind sensors | 12V | Boost converter plus load switch |
| RS485 transceiver | 3.3V | Logic-level compatible transceiver required |
