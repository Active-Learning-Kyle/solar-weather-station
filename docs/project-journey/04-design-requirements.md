# 04 - Design Requirements

Requirements turn needs into statements that can be tested. The targets below are migrated from Project Foundation v0.1. They are proposed release criteria, not completed results.

| ID | Requirement / acceptance target | Source | Verification | Status |
|---|---|---|---|---|
| SYS-001 | All locked baseline sensors shall produce stable readings for a continuous 24-hour bench run without bus lockup. | Foundation 4.3 | Integrated bench run with versioned log | Not started; sensor set not locked |
| COM-001 | Wind devices shall operate reliably on one RS-485 bus with documented model, power, serial settings, function/register map, scale, units and unique persistent slave IDs. | Foundation 4.3, 8.2, 11 | T-010, T-011 and T-012 | Partial progress reported; repository evidence missing |
| GNSS-001 | TEL0157 shall demonstrate controller communication and a valid outdoor UTC/position fix; no-fix and communication failure shall be distinguishable. | Foundation 4.3, 8.4 | T-020 and T-021 | Communication reported; outdoor fix evidence missing |
| PWR-001 | The integrated station shall operate through the Solar Power Manager (D) and protected battery path and automatically recover after power interruption. | Foundation 4.3, 8.8 | T-040 and recovery test | Not verified |
| PWR-002 | Complete-system current shall be measured in active, network-transmit, sensor-poll, GNSS-acquisition and sleep states. | Foundation 12, 14.2 | T-041 measurement table | Not started |
| PWR-003 | The first outdoor prototype should be sized for at least three days without useful solar input. | Foundation 12.2 | Energy model plus T-042 battery-only endurance | Planning target; not a runtime claim |
| ENV-001 | The released enclosure shall complete 20 assembly cycles without latch damage or loss of fit. | Foundation Appendix C | T-050 | Not started |
| ENV-002 | A defined unpowered spray/rain test shall show no water reaching protected electronics. | Foundation 14.3 and Appendix C | T-051 | Not started; no certified IP claim |
| FLD-001 | The station shall log outdoors for at least 72 hours with no unexplained resets, bus lockups, severe sensor anomalies, loose wiring, enclosure leak or corrupted data. | Foundation 4.3, 14.4 | T-070 field dataset and report | Not started |
| DAT-001 | Each measurement record shall use defined field names and units and include timestamp, validity/diagnostic state, station/firmware revision and GNSS-fix state. | Foundation 7 and 10 | Schema validation and sample dataset | Draft only |
| REP-001 | A second team shall assemble and flash the validated build using only released repository files and BOM. | Foundation 4.3 | Independent clean-build/rebuild trial | Not started |
| DOC-001 | README, exact BOM, wiring/pin map, Modbus IDs/registers, CAD, firmware build steps, calibration notes, test evidence, licences and known limitations shall be present and consistent. | Foundation 17-19 | Release checklist review | In progress |

## Stakeholder-derived provisional field-readiness requirements

The following requirements come from Gate A interview batches 1–2. They are review inputs, not evidence that the current system passes. Numeric data-quality, power and comparison thresholds remain open until the rest of Gate A, TA workflow validation and site approval are complete.

| ID | Provisional requirement / acceptance target | Source | Verification | Status |
|---|---|---|---|---|
| SAF-001 | A supervised field run shall not begin or continue with battery distress/short-circuit risk, wet exposed live connections, water reaching energised electronics, unstable mounting/fall risk, uncontrolled public access, abnormal heat/smell/smoke, or weather outside the approved test envelope. | VAL-001 Gate A Q3 | Pre-deployment and in-run stop-control checklist; T-072 | Provisional; site/safety approver confirmation required |
| DEC-001 | The 72-hour report shall support an explicit `go`, `conditional go` or `no-go` recommendation. A conditional go shall name required subsystem changes and repeat evidence. | VAL-001 Gate A Q2 | Independent instructor review of the field report; T-071 | Stakeholder confirmed; decision display/tabletop test pending |
| DEC-002 | Teaching-demo readiness and supervised short field-test readiness shall be reported separately from long-term unattended-deployment readiness. | VAL-001 Gate A Q2 and Q7 | Claim/scope review in T-071 | Stakeholder confirmed; evidence/report implementation pending |
| DAT-002 | Missing or implausible data shall be visible and diagnosable. Occasional missing records need not stop a run, but a sustained outage or untrustworthy output that prevents a useful decision shall trigger retrieval and diagnosis. | VAL-001 Gate A Q1 and Q3 | Gap/anomaly injection and decision review; T-060, T-071 | Qualitative; duration/completeness threshold pending |
| OPS-001 | Before deployment, the team shall name the site/location approver, instructor decision owner, student operator(s), TA supervisor, daily checker, fault contact and safe-removal owner. Any observer may stop an immediate safety hazard; non-immediate continuation decisions escalate to the instructor. | VAL-001 Gate A Q6 | Role-confirmed checklist and TA/site walkthrough; T-072 | Participant role model recorded; institutional/site authority and Gate B/C pending |
| FLD-002 | During the first 72-hour run, the system shall automatically record primary sensor readings, timestamps, battery voltage, missing intervals, restarts, local-logging state and significant communication failures. A human observation shall check plausibility, power trend, ingress/condensation, mounting/cables and weather risk at least daily. | VAL-001 Gate A Q4–5 | Log-schema review and daily observation record; T-073 | Provisional; exact completeness/fault thresholds pending |
| FLD-003 | The evidence package shall contain a pre-deployment check, during-run observations, post-retrieval physical/data inspection and a final `continue / continue with modification / return to bench` decision with named next actions. | VAL-001 Gate A Q5 | Three-stage field-readiness record; T-072, T-073 and T-074 | Provisional; checklist drafted for TA/site review |
| FLD-004 | A successful 72-hour run shall support progression only to a named next test stage. It shall not be reported as unattended, seasonal or industrial reliability; long-term drift; complete energy sizing; formal IP protection; or extreme-weather validation. | VAL-001 Gate A Q7 | Scope/claim review; T-071 and T-076 | Stakeholder confirmed; test evidence not started |
| REF-001 | Primary measurements shall use an independent comparison where accessible: preferably a co-located reliable/calibrated commercial station, otherwise reliable handheld spot checks, then nearby-station trend context. Repeated differences beyond the relevant manufacturer specification shall be investigated; instability remaining after justified calibration shall trigger replacement or a narrower claim. | VAL-001 Gate A Q8 | Reference/loan record and variable-specific comparison protocol; T-075 | Strategy confirmed; instrument access and tolerances pending |
| STR-001 | The project shall prefer buy/borrow when dependable traceable weather data is the objective, and student build/adaptation when engineering learning is the objective. For this exemplar, a reference instrument plus modular prototype is the working strategy until Gate E re-scoring. | VAL-001 Gate A Q9 | Gate E decision record, cost/access evidence and sensitivity review; T-076 | Stakeholder rule confirmed; matrix/procurement evidence pending |
| SUS-001 | Current public/teaching claims shall be limited to educational exploration of environmental monitoring, solar/low-power sensing and engineering/sustainability trade-offs. Carbon reduction, carbon neutrality, climate-solution, ESG-performance, commercial-grade and important-decision-data claims require separate baseline and validation evidence. | VAL-001 Gate A Q10 | README/report claim review; T-076 | Stakeholder claim boundary confirmed |

## Explicit first-release exclusions

- Certified meteorological-grade accuracy
- Formal IP-rating certification
- Commercial product certification/compliance
- Long-term unattended-operation claims before seasonal testing
- Mandatory LoRa receiver architecture before the core station is stable

Avoid words such as "low cost," "accurate," "robust," or "easy" unless they are accompanied by a measurable threshold, comparison and test.
