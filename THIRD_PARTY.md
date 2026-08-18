# Third-Party Materials and Reference Lineage

This file records external projects, code, designs, datasets, images, and documentation that informed or entered the project. Learning from a design idea is different from copying protected implementation files. Record both, but be precise about which occurred.

No third-party code, PCB, CAD, photograph or documentation file has been imported into this repository version.

| Project/material | Primary source | Status/licence observed 18 Aug 2026 | Influence | Files reused or modified | Required action |
|---|---|---|---|---|---|
| Open Green Energy Solar Powered WiFi Weather Station V4.0 | https://hackaday.io/project/187061-solar-powered-wifi-weather-station-v40 | Project page describes an open-source station and publishes BOM/Gerber/schematic assets; verify licences per asset | Primary architecture lineage: solar power, ESP32, sensor switching, LoRa, enclosure and broad sensor set | None | Record immutable asset versions before any reuse; do not assume one licence covers every asset |
| James Hughes transmitter firmware | https://github.com/jhughes1010/weather_v4_lora | GPL-3.0; public repository | Stable transmitter firmware linked from V4.0 | None | If copied/adapted, preserve notices and comply with GPL-3.0 |
| James Hughes receiver firmware | https://github.com/jhughes1010/weather_v4_lora_receiver | GPL-3.0; public repository | Stable receiver/MQTT architecture linked from V4.0 | None | If copied/adapted, preserve notices and comply with GPL-3.0 |
| teamsuperpanda ESPHome adaptation | https://github.com/teamsuperpanda/Weather-Station | PolyForm Noncommercial 1.0.0; archived 7 Jun 2026 | ESPHome/Home Assistant adaptation and deep-sleep reference | None | Treat as noncommercial reference, not the project's open-source licensing model |
| Open Weather Station | https://github.com/panchazo/open-weather-station | Apache-2.0 repository | Field reliability, repeatable assembly, maintenance, Android gateway and documentation reference | None | Cite if concepts or implementation details materially influence a decision |
| SeBassTian23 ESP32-WeatherStation | https://github.com/SeBassTian23/ESP32-WeatherStation | MIT repository | Local SD buffering, solar/deep-sleep, metrology separation and UV-window lessons | None | Cite if code/design is later reused; verify dependency licences separately |
| DFRobot TEL0157 documentation | https://wiki.dfrobot.com/tel0157/ | Vendor documentation | GNSS interface and specifications | None | Record exact module revision and retain link; redistribute vendor files only if permitted |
| Waveshare Solar Power Manager (D) documentation | https://www.waveshare.com/wiki/Solar_Power_Manager_%28D%29 | Vendor documentation | Solar/battery/load architecture | None | Record exact board revision and measured behaviour |
| DFRobot SEN0162 / GUVA-S12SD documentation | https://wiki.dfrobot.com/sen0162/ | Vendor documentation | Candidate true-UV photodiode module | None | Validate ADC, optical path and calibration before selection |
| Adafruit SI1145 documentation | https://www.adafruit.com/product/1777 | Legacy/no-longer-stocked product reference | Explains inferred UV and legacy V4.0 choice | None | Do not select as default new-build sensor without a reason |
| Espressif ESP32-S3 documentation | https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/sleep_modes.html | Official documentation | Low-power design reference | None | Measure the full development board/system; do not substitute SoC datasheet current for system evidence |
| Analog Devices MAX485 documentation | https://www.analog.com/en/products/max485.html | Official documentation; 5 V transceiver | Explains limitations of the diagnostic interface | None | Select/document a 3.3 V or isolated alternative for final design |

Before public release, add exact commits/tags or dated archive links for every source that materially influences an implementation.
