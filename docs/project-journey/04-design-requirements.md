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

The following requirements come from Gate A interview batch 1. They are review inputs, not evidence that the current system passes. Numeric data-quality, power and comparison thresholds remain open until the rest of Gate A, TA workflow validation and site approval are complete.

| ID | Provisional requirement / acceptance target | Source | Verification | Status |
|---|---|---|---|---|
| SAF-001 | A supervised field run shall not begin or continue with battery distress/short-circuit risk, wet exposed live connections, water reaching energised electronics, unstable mounting/fall risk, uncontrolled public access, abnormal heat/smell/smoke, or weather outside the approved test envelope. | VAL-001 Gate A Q3 | Pre-deployment and in-run stop-control checklist; T-072 | Provisional; site/safety approver confirmation required |
| DEC-001 | The 72-hour report shall support an explicit `go`, `conditional go` or `no-go` recommendation. A conditional go shall name required subsystem changes and repeat evidence. | VAL-001 Gate A Q2 | Independent instructor review of the field report; T-071 | Provisional; decision display/tabletop test pending |
| DEC-002 | Teaching-demo readiness and supervised short field-test readiness shall be reported separately from long-term unattended-deployment readiness. | VAL-001 Gate A Q2 | Claim/scope review in T-071 | Provisional; Gate A questions 7 and 10 pending |
| DAT-002 | Missing or implausible data shall be visible and diagnosable. Occasional missing records need not stop a run, but a sustained outage or untrustworthy output that prevents a useful decision shall trigger retrieval and diagnosis. | VAL-001 Gate A Q1 and Q3 | Gap/anomaly injection and decision review; T-060, T-071 | Qualitative; duration/completeness threshold pending |
| OPS-001 | Before deployment, the team shall document how faults are recognised, who responds, when the run stops and how the equipment is safely removed. | Team inference from VAL-001 Gate A Q1 and Q3 | TA walkthrough and site escalation review | Provisional; Gate B/C pending |

## Explicit first-release exclusions

- Certified meteorological-grade accuracy
- Formal IP-rating certification
- Commercial product certification/compliance
- Long-term unattended-operation claims before seasonal testing
- Mandatory LoRa receiver architecture before the core station is stable

Avoid words such as "low cost," "accurate," "robust," or "easy" unless they are accompanied by a measurable threshold, comparison and test.
