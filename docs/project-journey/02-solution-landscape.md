# 02 - Existing-Solution Landscape

**Study status:** first evidence-backed pass completed on 18 August 2026. Issue #3 remains open because user interviews, deployment context, updated quotations, and a scored concept-selection matrix are still required.

## Question being investigated

If the goal is only to obtain local weather data, buying a complete system may be better than designing one. A custom build is justified only if it creates additional value through modular interfaces, transparent data and calibration, repairability, open engineering files, or education.

## Provisional decision context

The first decision is now framed as: **which approach best gives the ENGG2202 teaching team a reliable reference plus a transparent, reproducible exemplar for judging short outdoor deployment readiness near the Innovation Wing One candidate site?** The exact mounting point, site permission and stakeholder workflow are still hypotheses, so the matrix below is a decision aid to validate, not a final procurement approval.

## Comparison of representative solutions

Prices are official USD list prices observed on 18 August 2026 where available; they exclude shipping, mounting, gateways, optional sensors, taxes, and institutional procurement costs.

| Solution | Category and intended use | Measurements / architecture | Power and data | Published cost | Openness | What it teaches us / gap for this project |
|---|---|---|---|---:|---|---|
| [Tempest Weather Station](https://shop.tempest.earth/products/tempest) | Turnkey home / smart-garden station | Integrated temperature, humidity, pressure, ultrasonic wind, haptic rain, lightning, UV and solar radiation; no moving parts | Solar with onboard battery; wireless hub and managed app/service | USD 349 | Proprietary hardware/service, with integrations | Very fast deployment and low maintenance. If our only objective is local data, this is hard to beat. It does not provide a transparent, modular ESP32/RS-485 engineering platform for students to rebuild and modify. |
| [Davis Vantage Pro2, SKU 6252](https://www.davisinstruments.com/products/wireless-vantage-pro2-weather-station-with-standard-radiation-shield-and-weatherlink-console) | Prosumer/professional monitoring | Temperature, humidity, pressure, wind and rain; optional solar/UV; 2.5 s updates and NIST-traceable sensors stated by Davis | Solar sensor suite with backup battery; proprietary wireless link to WeatherLink console/cloud | USD 1,035 | Proprietary | Strong reference for siting, replaceability, mature documentation and data quality. Cost and closed subsystem design limit its value as a build-from-source teaching exemplar. |
| [SenseCAP ONE S700](https://www.seeedstudio.com/SenseCAPONE-S700-7in1-Compact-Weather-Sensor-p-4879.html) | Industrial/agriculture/smart-city compact sensor | Temperature, humidity, pressure, light, optical rain, ultrasonic wind speed/direction | MODBUS RS-485 or SDI-12; separate logger/power system required | USD 1,799 sensor only | Proprietary sensor with documented interfaces | Directly validates RS-485/SDI-12 as field interfaces and offers compact deployment. Price is far above the project target and the integrated head hides most student design work. |
| [Campbell Scientific ClimaVue 50 G2](https://www.campbellsci.com/products/climavue50-g2) | Research/environmental networks | Temperature, pressure, RH, solar radiation, wind, dual precipitation sensing, lightning, tilt and precipitation EC | SDI-12; manufacturer states <1 mA average at 12 V | Quote/sign-in required | Proprietary | Benchmark for low power, siting, leveling, maintenance and explicit specifications. It is a sensor, not an open end-to-end station, and is not intended as a low-cost student build. |
| [Open Green Energy Solar Powered WiFi Weather Station V4.0](https://hackaday.io/project/187061-solar-powered-wifi-weather-station-v40) | Maker/open-hardware reference for remote sites | ESP32 sender, broad sensor set, custom PCB and Stevenson-screen enclosure; LoRa receiver uploads/display data | Solar/18650; LoRa sender-receiver; MQTT/cloud options | BOM published; current total not verified | Hardware files/BOM published; linked transmitter and receiver firmware are GPL-3.0 | Closest lineage and strongest starting point for solar, enclosure, power switching and documentation. The two-node architecture, older sensor choices, incomplete instruction/release packaging, and licensing boundaries require adaptation rather than copying. |
| [Open Weather Station (panchazo)](https://github.com/panchazo/open-weather-station) | Field-tested DIY weather station | Arduino reads wind, rain, temperature, pressure, humidity and light; Android phone handles storage, display and upload | Bluetooth to Android; Wi-Fi/cellular through phone; optional solar guidance | Historic author estimate USD 300-500 including phone/sensors/housing | Apache-2.0 repository | Excellent example of documenting field reliability, maintenance, assembly and failure recovery. Phone dependency, Arduino-era architecture and different power/data goals make it a reference rather than the baseline design. |
| [ESP32-WeatherStation (SeBassTian23)](https://github.com/SeBassTian23/ESP32-WeatherStation) | Open ESP32 environmental station | BME680, SI1145 and particulate sensing; local SD backup plus Wi-Fi/REST; wind/rain not baseline | Battery and solar; deep-sleep between 5-minute samples | No complete current BOM total | MIT | Useful evidence for local-first buffering, separating metrology from power heat, UV-window risk and measuring full energy behaviour. Sensor calibration and long-term evidence remain limited. |
| [LCAWS research prototype](https://arxiv.org/abs/2102.04574) | Low-cost automatic station for disaster monitoring | Commercial-off-the-shelf sensors and open-source IoT technologies with calibration against a professional station | Research deployment architecture | Paper frames cost reduction; refresh BOM from full paper before procurement | Research/open-source approach | Most important methodological lesson: low-cost claims need co-location, calibration and long-duration comparison. The paper reports a 30-day uninterrupted comparison with no statistically significant differences after calibration; our 72-hour test is only an initial endurance test, not equivalent validation. |

## Licensing/reference caution

- [`jhughes1010/weather_v4_lora`](https://github.com/jhughes1010/weather_v4_lora) and its [receiver](https://github.com/jhughes1010/weather_v4_lora_receiver) are GPL-3.0.
- [`teamsuperpanda/Weather-Station`](https://github.com/teamsuperpanda/Weather-Station) is an ESPHome adaptation, uses PolyForm Noncommercial 1.0.0, and was archived on 7 June 2026. It may inform architecture but should not be described as OSI-style open-source or used as this project's licensing model.

## Evidence-backed gap statement

There is no demonstrated need to build another station merely to obtain temperature, wind, rain, and pressure. Turnkey systems already provide those functions at several price and performance levels.

The defensible gap for this project is narrower:

> A reproducible, education-first, solar-powered microclimate station that exposes the engineering interfaces and evidence - ESP32-S3 firmware, RS-485/Modbus field instruments, GNSS context, power budget, serviceable enclosure, local-first data, calibration, tests, BOM, CAD and design decisions - so that another team can understand, rebuild, validate and modify the system.

This direction deliberately trades turnkey convenience and certified performance for transparency, modularity, learning value and repairability. It should not claim superiority over commercial instruments on measurement accuracy until comparative data exists.

## Implications for concept selection

1. **Buy rather than build** if the stakeholder only needs dependable local data and has no requirement for open files, custom sensors, teaching, or repair.
2. **Keep RS-485/Modbus** because it supports replaceable field sensors and connects the project to industrial practice; document exact models, registers and electrical protection.
3. **Use commercial systems as benchmarks**, not enemies. Compare siting, missing-data behaviour, maintenance, data access, energy and calibration.
4. **Retain local storage before network transmission** so connectivity failure does not automatically become data loss.
5. **Treat the 72-hour run as endurance/integration evidence**, followed by longer co-location and calibration if measurement quality is part of the claim.
6. **Control scope:** rain, particulate matter, soil sensing and LoRa should not all enter v0.2 unless the target use case requires them.

## Provisional weighted concept-selection matrix

Scores use 1 (poor) to 5 (strong). Weights reflect the proposed teaching/test use rather than a general weather-data purchase. The editable calculation is retained in [`concept-selection-matrix.csv`](concept-selection-matrix.csv).

| Criterion | Weight | A: turnkey consumer station | B: industrial sensor + custom logger | C: reproduce Open Green Energy V4 | D: independent modular exemplar | E: reference instrument + modular exemplar |
|---|---:|---:|---:|---:|---:|---:|
| Learning visibility and traceability | 20% | 2 | 4 | 5 | 5 | 5 |
| Open reproducibility | 15% | 1 | 3 | 4 | 5 | 5 |
| Fitness for the 72-hour teaching/readiness decision | 15% | 4 | 5 | 3 | 4 | 5 |
| Deployment speed and baseline reliability | 10% | 5 | 4 | 2 | 2 | 4 |
| Outdoor/power suitability | 10% | 4 | 5 | 3 | 3 | 4 |
| Modularity and repairability | 10% | 2 | 4 | 4 | 5 | 5 |
| Lifecycle cost and procurement | 10% | 4 | 1 | 4 | 3 | 2 |
| Safety and maintenance burden | 10% | 4 | 4 | 3 | 3 | 4 |
| **Weighted result (/100)** | **100%** | **61** | **76** | **73** | **79** | **88** |

### Provisional selection

**Concept E - use a bought, borrowed or shared reference instrument alongside an independently documented modular exemplar - is the current preferred strategy.** It avoids pretending a student-built station is already a measurement reference while preserving the interfaces, failures, power budget, code, CAD, tests and decision trail needed for ENGG2202 learning.

This is a staged strategy, not permission to purchase a particular product. First seek an existing HKU instrument or short loan. Only procure after the stakeholder, site, comparison variables, data-access needs and quotation are confirmed.

## Work still needed to close Issue #3

- Validate the provisional instructor/TA stakeholder and field-readiness decision through interviews and one site observation.
- Obtain Hong Kong/institutional quotations and availability for shortlisted commercial and component options.
- Select a comparison/reference instrument and define a co-location protocol.
- Record exact access dates and immutable versions/commits for all repositories used in the final decision.
- Re-score the matrix with the stakeholder and record disagreements/sensitivity before concept lock.
