# Gate 04: Learn

Gate 04 began by studying working open-source weather stations rather than treating the project as if no one had solved similar problems before.

## Open projects studied

| Reference | What was learned | What this project does differently |
| --- | --- | --- |
| [SeBassTian23/ESP32-WeatherStation](https://github.com/SeBassTian23/ESP32-WeatherStation) | Solar-powered ESP32 sensing can include particulate matter and UV-related measurements, but power demand and calibration limits remain important. | Keep every sensor's validity visible and treat UV and air-quality outputs as bounded measurements rather than automatic environmental claims. |
| [cerevisis/ESP32-Weather-Station](https://github.com/cerevisis/ESP32-Weather-Station) | A weather station can expose live readings, history, configuration and diagnostics through a web interface. | Use a small local FastAPI and SQLite path so ingestion rules, stored history and failure states can be tested independently. |
| [maxmacstn/HA-SolarWeatherStation](https://github.com/maxmacstn/HA-SolarWeatherStation) | Deep sleep, battery-aware operation and separated enclosures are practical strategies for autonomous outdoor sensing. | Keep the sensing and power modules editable and defer any autonomy claim until the complete energy balance has been measured. |

These projects are precedents, not hidden ingredients. Their licences continue to govern their work. The implementation in this repository was developed and documented separately, with the reference ideas and resulting design decisions made explicit.

## Rebuild, understand, then adapt

Each working version was kept small enough to reproduce and understand one established capability before changing it for this project's local-evidence goal. Later milestones preserve the earlier diagnostics and failure behaviour.

## Core v0.1: integrated sensing

**Question:** Can four I²C devices and the PMS7003 operate together without one failure stopping the rest?

**Learned:** A shared snapshot and per-sensor health model are more useful than printing isolated values. Range, staleness and failure counters make unavailable data visible.

**Evidence:** [v0.1 milestone](../milestones/v0.1-core-sensors.md), diagnostic environments and bench images.

## Core v0.2: connected data path

**Question:** Can a local service receive, validate, store and display station snapshots without making sensing depend on the network?

**Learned:** Networking needs independent reconnect timing and bounded uploads. Typed API validation and nullable data make failures inspectable. Database migrations must preserve existing records.

**Evidence:** [v0.2 milestone](../milestones/v0.2-connected-iot.md), backend tests and dashboard screenshot.

## Core v0.3: GNSS integration

**Question:** Can the receiver report communication, no-fix and valid-fix states without blocking the rest of the station?

**Learned:** Communication and position validity are different states. The installed library required a documented hemisphere workaround based on checksum-valid NMEA fields. Precise coordinates need a publication rule.

**Evidence:** [v0.3 milestone](../milestones/v0.3-gnss-integration.md), GNSS diagnostics and privacy-safe images.

## Core v0.4: wind-speed integration

**Question:** Can verified RS485 wind speed enter the complete data path while timeouts remain isolated?

**Learned:** Native USB CDC frees UART0 for production RS485. A calm `0.0 m/s` reading must remain valid, while a timeout must become unavailable. The schema and database can extend additively without breaking v0.3 payloads.

**Evidence:** [v0.4 milestone](../milestones/v0.4-wind-speed-integration.md), backend compatibility tests and the preserved standalone diagnostic.

## Current working version

The repository contains a complete software path for Core v0.4. The next action is not another feature. It is the combined hardware verification procedure in [`core-v0.4.md`](../core-v0.4.md).
