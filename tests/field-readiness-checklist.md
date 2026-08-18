# 72-Hour Field-Readiness Record

**Status:** Gate A-informed template; TA, site, reference-access and responsible safety approval still required

**Related requirements:** SAF-001, DEC-001, DEC-002, DAT-002, OPS-001, FLD-002, FLD-003, FLD-004, REF-001 and SUS-001

**Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)

Use one copy for one configuration and deployment attempt. A checked box records an observation; it does not by itself prove long-term reliability or approve the site.

Use the [field operations pack](field-operations-pack/README.md) for concise on-site checks and escalation. Preserve this longer record for reviewed evidence and the final decision.

## Test identity and responsibility

- **Configuration / firmware / hardware revisions:**
- **Test purpose and decision to be made:**
- **Candidate site and approved test boundary:**
- **Planned start / retrieval:**
- **Site/location approver:**
- **Instructor decision owner:**
- **Student operator(s):**
- **TA supervisor / checklist reviewer:**
- **Daily checker and backup:**
- **Fault contact / safe-removal owner:**
- **Approved weather envelope / forecast check:**
- **Reference instrument / contextual comparison / specification:**
- **Variable-specific project tolerance or investigation trigger:**

Project ownership does not grant safety approval. Any person who identifies an immediate safety hazard may stop and isolate the test; restarting requires the named responsible decision owner.

## A. Before deployment

### Purpose, roles and stop controls

- [ ] The test purpose, three decision outcomes and evidence limits are understood.
- [ ] Site/location permission and public-space constraints are recorded.
- [ ] Student, TA, instructor, fault-contact and removal roles are named.
- [ ] Immediate stop conditions and the safe isolation/removal method are reviewed.

### Electrical, sensing and data readiness

- [ ] Battery/protection/supply show no distress, damage, abnormal heat or short-circuit risk.
- [ ] Primary sensors produce plausible values and visible validity/diagnostic state.
- [ ] Timestamps, battery voltage, missing-data state, restart state and local-logging state are recorded.
- [ ] Network loss does not prevent local logging; reconnection/recovery behaviour is checked.
- [ ] Controlled restart returns the system to the intended logging state.
- [ ] Reference availability/method, metadata and comparison timing are recorded; limitations are stated.

### Physical and site readiness

- [ ] Enclosure, cable glands, connectors and protected wiring show no visible ingress path or damage.
- [ ] Mounting is secure against the approved load/weather envelope and does not create fall/trip hazards.
- [ ] Public contact, tampering and emergency access/removal are controlled.
- [ ] Forecast and current conditions are within the approved test envelope.

### Start decision

- [ ] **Go** — begin the run under the stated controls.
- [ ] **Conditional go** — complete the named change/check before starting.
- [ ] **No-go** — return to bench or revise the site/test plan.

- **Conditions / reason / required evidence:**
- **Student and TA check completed by:**
- **Instructor start decision / date:**
- **Site approval reference:**

## B. During the run

### Automatic evidence required for the first run

- primary sensor readings and diagnostic/validity state;
- timestamps and missing intervals;
- battery voltage/basic supply state;
- restarts and recovery events;
- local-logging state; and
- significant communication failures.

Basic solar input, internal temperature and detailed interface statistics are helpful or required when they affect the specific decision. Long-term reliability statistics, battery-degradation modelling, packet-level analysis and fixed-site GNSS accuracy are outside the first-run minimum unless explicitly made part of the test.

### Daily observation

| Date/time | Observer | Online/logging? | Data plausible / gaps? | Battery trend | Ingress/condensation | Mount/cables/public condition | Weather/risk change | Action / Issue link |
|---|---|---|---|---|---|---|---|---|
| | | | | | | | | |

For an immediate safety hazard—battery distress, wet energised electronics, abnormal heat/smoke, unstable mounting, uncontrolled public risk or weather beyond the approved envelope—stop first and escalate. For a non-immediate data/technical fault, record evidence and escalate the continuation decision to the instructor.

## C. Retrieval and post-test inspection

- [ ] The system is safely de-energised before opening or handling exposed connections.
- [ ] Battery final condition and voltage are recorded.
- [ ] Enclosure interior is checked for water, condensation and corrosion.
- [ ] Connectors, cables and glands are checked for loosening, damage or change.
- [ ] Mounting is checked for movement, loosening or deformation.
- [ ] Sensor surfaces are checked for contamination or obstruction.
- [ ] Electrical, battery or severe-ingress hazards are referred to competent staff rather than handled unsupervised by students.

### Data summary

- **Expected / received records and completeness:**
- **Missing periods:**
- **Restart / reset count and known causes:**
- **Communication failures:**
- **Recovery attempts / successful recoveries:**
- **Sensor anomalies / contamination context:**
- **Observed environmental causes versus suspected design causes:**
- **Reference observations, differences and uncertainty:**
- **Difference beyond specification / investigation / calibration or replacement decision:**

## D. Decision and next action

Select one:

- [ ] **Continue / go:** proceed to the named next supervised test.
- [ ] **Continue with modification / conditional go:** change the named sensor, power, data, interface, enclosure or mounting item and repeat specified evidence.
- [ ] **Return to bench / no-go:** do not redeploy until the named readiness or safety condition is resolved.

- **Decision evidence:**
- **Required change and owner:**
- **Repeat test / acceptance evidence:**
- **Teaching-demo readiness:** ready / conditional / not ready, with reason
- **Supervised short field-test readiness:** ready / conditional / not ready, with reason
- **Unattended long-term deployment readiness:** not claimed unless supported by separate evidence
- **Green Technology claim used:** educational environmental monitoring / solar-low-power sensing / engineering-sustainability trade-off / other evidenced wording
- **Claims deliberately not made:** carbon reduction / carbon neutral / climate solution / ESG performance / commercial grade / important-decision data / other
- **Instructor decision / date:**
- **Open Issue(s) / Pull Request(s):**
