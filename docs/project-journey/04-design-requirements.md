# 04 — Design Requirements

Requirements turn needs into statements that can be tested.

| ID | Requirement | Rationale/source | Verification method | Status |
|---|---|---|---|---|
| SYS-01 | The station shall collect a defined set of local weather measurements. | Project objective | Subsystem and integration tests | Draft: sensor set not locked |
| PWR-01 | The station shall operate from the defined solar-and-battery architecture for a measurable autonomy period. | Outdoor use | Energy budget plus endurance test | Acceptance value pending |
| ENV-01 | Outdoor components shall tolerate the defined deployment environment. | Safety/reliability | Inspection and environmental test | Environment class pending |
| DAT-01 | Measurements shall include timestamp, units, and sensor identity. | Traceability | Schema validation | Draft |
| REP-01 | A new team shall be able to reproduce the validated build from released files. | Open-source objective | Independent build trial | Not started |

Avoid words such as “low cost,” “accurate,” “robust,” or “easy” unless they are accompanied by a measurable threshold and test.

