# 03 — Reference Projects

Reference projects help the team learn architecture, interfaces, build practices, and failure modes. They are not permission to copy without attribution.

## Current reference record

No third-party implementation file has been copied into this repository version. The entries below describe learning lineage, not ownership of the referenced work.

| Reference | Why selected | What has been reproduced | What was learned | Possible independent adaptation | Licence/attribution status |
|---|---|---|---|---|---|
| [Open Green Energy Solar Powered WiFi Weather Station V4.0](https://hackaday.io/project/187061-solar-powered-wifi-weather-station-v40) | Primary architecture lineage named in Project Foundation v0.1 | No source file; architecture and subsystem categories were studied | Solar power, ESP32, distributed sensing, LoRa and weatherproof packaging form a coherent system problem | Replace controller and interfaces where evidence supports the change; make validation and teaching traceability first-class | Licence must be verified per asset before any reuse |
| [James Hughes transmitter firmware](https://github.com/jhughes1010/weather_v4_lora) and [receiver firmware](https://github.com/jhughes1010/weather_v4_lora_receiver) | Stable firmware repositories linked from the V4.0 lineage | None | Transmitter/receiver separation and MQTT hand-off are useful architectural references | Keep the current implementation independent unless GPL-3.0 reuse is deliberately accepted | GPL-3.0 repositories; exact commit required before reuse |
| [teamsuperpanda Weather-Station](https://github.com/teamsuperpanda/Weather-Station) | ESPHome/Home Assistant adaptation of the same project lineage | None | Deep sleep, home-automation integration and adaptation history expose useful trade-offs | Treat only as a noncommercial learning reference | PolyForm Noncommercial 1.0.0; archived 7 June 2026 |
| [Open Weather Station](https://github.com/panchazo/open-weather-station) | Field-oriented open system with build and maintenance experience | None | Reliability, repeated assembly and serviceability matter as much as sensor count | Adopt the evidence discipline and maintenance mindset, not unverified implementation details | Apache-2.0 repository; exact commit required before reuse |
| [ESP32-WeatherStation](https://github.com/SeBassTian23/ESP32-WeatherStation) | Compact ESP32 reference covering local storage, solar operation and environmental sensing | None | SD buffering, deep sleep and optical treatment of UV sensing deserve explicit design decisions | Compare storage and low-power patterns after whole-system measurements exist | MIT repository; dependencies require separate review |

## Reuse rule

Before copying or adapting any external file, record the exact repository, immutable commit, path, licence, copyright notice and local destination in `THIRD_PARTY.md`. A link to a project homepage alone is not sufficient provenance.

For every reused file, update `THIRD_PARTY.md` with its exact origin and licence.
