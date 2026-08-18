# ADR-004 — Environmental Sensor Set for v0.2

**Date:** 19 August 2026

**Status:** accepted for the teaching-preview baseline; exact breakout suppliers and real calibration remain to verify

**Issue:** [#4 Select and lock the environmental sensor set](https://github.com/heqihao522828-crypto/solar-weather-station/issues/4)

## Context

The project needs temperature, relative humidity, pressure and a UV-related learning channel. A single inexpensive “all-in-one” part is attractive, but it hides replacement and calibration trade-offs. Outdoor measurements also depend on radiation shielding, airflow, contamination and optical exposure—not only the sensor datasheet.

## Decision

Use three I²C devices in the v0.2 teaching baseline:

| Function | Selected part | Baseline role | Claim boundary |
|---|---|---|---|
| Temperature / relative humidity | Sensirion SHT45 on a replaceable breakout or protected probe | primary T/RH channel | official typical component specification only; system accuracy requires shield and reference comparison |
| Barometric pressure | Bosch BMP390 breakout | primary pressure channel | weather/context measurement; site and enclosure effects still apply |
| UVA trend | Lite-On LTR-390UV-01 breakout | experimental UVA-count channel | report raw/normalised UVA response; do not call it calibrated UV Index without a comparison model |

The official SHT45 product page lists typical ±1.0 %RH and ±0.1 °C accuracy, I²C and 1.08–3.6 V supply. Bosch lists the BMP390 as a 24-bit I²C/SPI pressure sensor with 300–1250 hPa full-accuracy range and typical ±0.50 hPa absolute accuracy. Lite-On describes the LTR-390UV-01 as an I²C UVA/ambient-light sensor operating from 1.7–3.6 V. These are component specifications, not proof of this assembled station.

## Alternatives rejected for this baseline

- **BME280-only:** simpler and widely supported, but lower learning visibility and no independent humidity/pressure replacement path.
- **SHT31 + BMP280:** viable fallback, but the selected pair offers a stronger current specification baseline.
- **SI1145 UV:** rejected because it estimates UV from visible/IR response rather than directly sensing the UVA band.
- **GUVA analogue device:** useful for analogue-learning exercises, but adds ADC/reference/analogue-layout variables that are not the v0.2 priority.

## Integration controls

- Place SHT45 in a ventilated radiation shield, separated from controller/power heat.
- Expose BMP390 to ambient pressure through a protected breathable path; do not seal it in a pressure-tight box.
- Give LTR390 an unobstructed UV-compatible optical window; do not assume ordinary enclosure plastic is UV transparent.
- Record sensor serial/batch where available, I²C address, library/driver version, calibration metadata and replacement history.
- Treat official datasheet accuracy as an investigation trigger, not an automatic field acceptance band.

## Verification

1. 24-hour bench continuity and stuck-value/outlier checks.
2. Co-located temperature/RH/pressure comparison with a documented reference.
3. Controlled shade/sun response and repeatability check for LTR390.
4. Shield heat-bias comparison against an unpowered reference position.
5. Real purchase/availability review before ordering.

## Revisit triggers

Re-open the decision if a selected breakout becomes unavailable, reference comparison is unstable beyond the project tolerance, the optical path cannot be controlled, or the project requires calibrated solar irradiance/UV Index rather than an educational UVA trend.

## Primary sources checked

- [Sensirion SHT45 product page](https://sensirion.com/products/catalog/SHT45), checked 19 August 2026.
- [Bosch BMP390 product page](https://www.bosch-sensortec.com/en/products/environmental-sensors/pressure-sensors/pressure-sensors-bmp390.html), checked 19 August 2026.
- [Lite-On LTR-390UV-01 datasheet](https://optoelectronics.liteon.com/upload/download/DS86-2015-0004/LTR-390UV-01_Final_%20DS_V1.7.PDF), checked 19 August 2026.

