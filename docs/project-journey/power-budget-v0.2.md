# Power Budget v0.2 — Teaching Preview

> **SYNTHETIC / NOT MEASURED.** This document demonstrates the completed engineering calculation and evidence structure for Issue #5. Replace every current value with instrumented complete-system measurements before claiming battery life or solar autonomy.

## Selected planning configuration

- 10-minute sampling interval;
- ESP32-S3-DevKitC-1-N8R8 controller baseline;
- environmental sensing, switched RS-485 wind polling, periodic GNSS, local microSD record and batched Wi-Fi upload;
- Waveshare Solar Power Manager (D), 3.7 V 10 Ah protected battery planning class and 10 W nominal solar panel planning class.

## Synthetic load calculation

The versioned [synthetic mode profile](../../tests/synthetic-v0.2/power-profile.csv) totals **28.972 mWh per 10-minute interval** at the 5 V load. This gives:

| Quantity | Teaching-preview calculation |
|---|---:|
| Average load power before power-manager loss | 173.8 mW |
| Load energy per day | 4.17 Wh/day |
| Manager quiescent allowance | 0.19 Wh/day (8 mA max at the 5 V-side planning equivalent) |
| Load plus conversion allowance | **4.83 Wh/day** |
| 3-day no-solar requirement | **14.49 Wh usable** |
| 10 Ah × 3.7 V battery nominal energy | 37.0 Wh |
| Planning usable energy (80% depth × 90% conversion) | **26.64 Wh** |
| Modelled no-solar autonomy | **5.5 days** |

The battery class therefore passes the three-day *model target* with approximately 1.84× usable-energy margin. It has not passed T-041 or T-042 because none of these current values is measured.

## Solar recovery model

For a conservative teaching example, assume 10 W nominal panel, 2.5 peak-sun-hours/day and 65% whole-path derating:

`10 W × 2.5 h × 0.65 = 16.25 Wh/day`

That is about 3.36× the synthetic 4.83 Wh/day demand. This does not prove performance at the candidate HKU site: shade, orientation, heat, charge-controller behaviour, dirt, panel rating and weather must be measured.

## Design consequences

- Wind instruments must be power-switched or their real continuous draw included; warm-up time and Modbus stability need a bench test.
- Development-board overhead is acceptable for v0.2 learning but should be reconsidered for a low-power carrier-board release.
- Battery voltage, charge state, brownout/reset reason and solar-input context belong in every field record.
- The battery pack requires reputable protection, fuse/over-current strategy, mechanical restraint and competent review.

## Real measurement procedure

Measure at the complete 5 V system input with a logging power analyser or suitable shunt/instrument. Record sleep/idle, each sensor poll, SD write, Wi-Fi association/transmit, GNSS acquisition, RS-485 start-up/poll, startup, network-failure and recovery. Use at least 30 cycles per state, publish mean/peak/duration, then regenerate this budget and run T-042.

## Primary source boundary

Waveshare documents Solar Power Manager (D) as supporting 6–24 V solar input, a 3.7 V battery, 5 V/3 A regulated output, multiple protections and maximum quiescent current below 8 mA. These official board specifications support the architecture; they do not validate our wiring, battery, panel or load model. Source checked 19 August 2026: [Waveshare Solar Power Manager (D)](https://www.waveshare.com/Solar-Power-Manager-D.htm).

