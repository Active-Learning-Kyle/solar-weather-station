# Bill of Materials and Hardware Status

This BOM separates the verified v0.1–v0.3 bench prototype, the Core v0.4 wind-speed integration and deferred field hardware. Confirm exact board/module revisions, connector families, mounting hardware, prices and suppliers before treating it as a purchase-ready BOM.

## Current integrated prototype

| Item | Qty | Status | Notes |
| --- | ---: | --- | --- |
| ESP32-S3 development board | 1 | Integrated | PlatformIO target is `esp32-s3-devkitc-1`; confirm the physical board revision |
| SHT4x breakout | 1 | Hardware verified | Exact SHT40/SHT41 fitted variant not independently established; I²C `0x44` |
| BMP180 breakout | 1 | Hardware verified | I²C `0x77`; this corrects the earlier draft BOM's BMP390 entry |
| BH1750 breakout | 1 | Hardware verified | I²C `0x23` or `0x5C` |
| LTR390 breakout | 1 | Hardware verified | I²C `0x53`; UV index is an estimate in current firmware |
| PMS7003 | 1 | Hardware verified | 5 V particulate sensor, UART 9600 baud, SET control |
| Perfboard/interface connector assembly | 1 | Integrated prototype | Point-to-point prototype documented in v0.1 images |
| Printed Weather Station Body, Power Module and Connecting Base | 1 set | Printed and fit checked | Editable Fusion 360 sources are included; weatherproofing and outdoor durability are not verified |
| Data-capable USB cable and suitable bench supply | 1 each | Required for development | Supply must handle ESP32 Wi-Fi and PMS peaks |

## Additional and deferred hardware

| Item | Qty | Status | Notes |
| --- | ---: | --- | --- |
| DFRobot Gravity TEL0157 / Quectel L76K GNSS module with active antenna | 1 | Hardware verified in v0.3 | Official range 3.3–5.5 V; project uses 3V3, UART selector position, UART1 at 9600 baud |
| RS485 wind speed sensor | 1 | Diagnostic hardware verified; production software integrated | 12 V Modbus RTU; combined Core v0.4 hardware verification remains pending |
| RS485 wind direction sensor | 1 | Diagnostic available | 12 V Modbus RTU; production integration planned for v0.4 |
| 3.3 V-compatible RS485 transceiver | 1 | Diagnostic hardware | MAX3485-class; do not use 5 V logic at ESP32 pins |
| Tipping-bucket rain gauge | 1 | Planned | Bucket calibration and debounce not verified |
| Protected 1S3P 18650 pack/holder/BMS | 1 | Planned | Cell selection and protection require safety review |
| Waveshare Solar Power Manager (D) | 1 | Planned | Earlier power-system choice; autonomous operation not verified |
| 6 V 5 W solar panel | 1 | Preliminary | Starting estimate only; energy balance not measured |
| 12 V boost converter | 1 | Planned | For wind sensors; efficiency/current not verified |
| Logic-level MOSFET/load switch | 1 | Planned | Optional switched wind rail |
| Battery/solar voltage dividers and protection | 2 channels | Planned | ADC scaling and calibration not verified |
| Outdoor enclosure, glands, vents, radiation shield | 1 set | Planned | Must address ingress, condensation, airflow, heating, and UV exposure |

See [pin allocation](../docs/pin-allocation.md), [wiring](wiring.md), [power-system notes](power-system.md) and the [mechanical CAD catalog](cad/README.md). The repository includes editable Fusion 360 enclosure sources but does not yet include a supplier-and-price-locked procurement BOM, PCB fabrication files, exported STL files or an audited measured power budget.
