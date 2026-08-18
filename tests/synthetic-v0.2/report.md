# Synthetic v0.2 — 72-hour Integration Report

> **SYNTHETIC TEACHING PREVIEW — NOT A FIELD TEST.** No station was deployed, no HKU site was approved and no reference instrument produced these values.

![Synthetic 72-hour summary](preview-summary.svg)

## Test definition

| Item | Preview value |
|---|---|
| Window | 20 August 2026 09:00 to 23 August 2026 08:50 HKT |
| Interval | 10 minutes |
| Expected records | 432 |
| Configuration | HW-v0.2-preview / FW-v0.2-preview / BOM v0.2 preview |
| Site | fictional controlled semi-open Candidate B |
| Reference | fictional co-located T/RH reference channels |
| Purpose | show whether corrected v0.2 evidence could proceed to a longer supervised co-location test |

## Acceptance criteria defined for the simulation

| Criterion | Preview threshold | Result | Outcome |
|---|---:|---:|---|
| Local completeness | 100% | 432/432 = 100% | pass in simulation |
| Remote receipt/backfill | ≥99% live and all local gaps recoverable | 430/432 = 99.54%; 2 backfilled | pass in simulation |
| Unexplained restart | 0 | 0 | pass in simulation |
| Battery floor | >3.70 V | 3.87 V minimum | pass in simulation |
| Temperature/reference difference | mean absolute ≤0.5 °C; maximum ≤1.0 °C | mean 0.179 °C; maximum 0.220 °C | pass in simulation |
| RH/reference difference | mean absolute ≤3 %RH; maximum ≤5 %RH | mean 1.189 %RH; maximum 1.500 %RH | pass in simulation |
| Enclosure/mounting | no water/condensation/unsafe movement | fictional daily/retrieval checks report none | pass in simulation only |

The project thresholds above are teaching choices, not manufacturer guarantees or stakeholder-approved real acceptance limits.

## Findings

- The local-first record preserves all 432 samples.
- Two consecutive remote intervals are unavailable live but are marked and backfilled from the local log.
- Five scheduled samples show `gnss_fix=0`; sensor communication and timestamp continuity remain distinguishable from a valid fix.
- Battery model cycles between 3.87 V and 4.08 V without a fictional brownout or reboot.
- Temperature and RH differences are stable rather than random; they remain inside the preview limits.
- UVA values are raw synthetic counts. They do not establish calibrated UV Index or irradiance.
- Daily and post-retrieval observations contain no fictional immediate-stop condition.

## Decision

**`PROCEED TO THE NEXT SUPERVISED TEST` in the simulation.** Retain the v0.2 architecture and proceed to a longer authorised co-location/calibration run after the physical build passes bench, power, enclosure, site and operator gates.

This is narrower than “validated weather station.” The preview does not establish physical operation, sensor accuracy, energy autonomy, formal weatherproofing, public deployment, seasonal reliability, Green Technology impact or suitability for important decisions.

## Real evidence required to replace this report

1. approved site and access record;
2. real hardware photographs/serials and signed inspection;
3. measured current profile and battery/solar log;
4. raw local and remote records from the real firmware;
5. reference-instrument identity/calibration metadata and comparison method;
6. real daily observations and post-retrieval inspection; and
7. instructor decision with any follow-up Issue.

