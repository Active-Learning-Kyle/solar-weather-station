# Third-Party Dependencies

The repository contains original project source and documentation under the MIT License. Package managers download the dependencies below from their upstream projects. Those dependencies keep their own copyright and licence terms; the project MIT License does not replace them.

## Firmware libraries

| Dependency | Purpose | Upstream |
| --- | --- | --- |
| Adafruit SHT4x Library | Temperature and humidity | <https://github.com/adafruit/Adafruit_SHT4X> |
| Adafruit BMP085 Library | BMP180 pressure interface | <https://github.com/adafruit/Adafruit-BMP085-Library> |
| BH1750 | Ambient-light sensing | <https://github.com/claws/BH1750> |
| Adafruit LTR390 Library | UV and ambient-light sensing | <https://github.com/adafruit/Adafruit_LTR390> |
| TinyGPSPlus | NMEA parsing | <https://github.com/mikalhart/TinyGPSPlus> |
| DFRobot_GNSS | TEL0157/L76K interface | <https://github.com/DFRobot/DFRobot_GNSS> |
| ArduinoJson | JSON serialization | <https://github.com/bblanchon/ArduinoJson> |
| ModbusMaster | Modbus RTU communication | <https://github.com/4-20ma/ModbusMaster> |
| Espressif Arduino core and PlatformIO platform | ESP32-S3 framework and build tooling | <https://github.com/espressif/arduino-esp32> |

Exact resolved versions are recorded by PlatformIO under the local build environment. Before a tagged release, record or lock versions needed for reproducibility and review each upstream licence.

## Backend dependencies

| Dependency | Purpose | Upstream |
| --- | --- | --- |
| FastAPI | API and static application | <https://github.com/fastapi/fastapi> |
| Uvicorn | ASGI development server | <https://github.com/encode/uvicorn> |
| Pydantic | Measurement validation | <https://github.com/pydantic/pydantic> |
| HTTPX | API test client | <https://github.com/encode/httpx> |
| pytest | Automated tests | <https://github.com/pytest-dev/pytest> |

## Communication assets

The README uses the official SDG 7, 9 and 13 web icons from the [United Nations Sustainable Development communications materials](https://www.un.org/sustainabledevelopment/news/communications-material/). The icons retain their own terms and must be used in accordance with the UN SDG logo, colour wheel and icon guidelines. Their inclusion does not imply United Nations endorsement.

Project photographs and generated explanatory visuals are documented separately in [`docs/images/readme/README.md`](docs/images/readme/README.md).

## Contribution rule

Do not paste external code, CAD, media or datasets into the repository without recording the source, exact version, licence and required attribution. A public URL alone is not permission to reuse the material.
