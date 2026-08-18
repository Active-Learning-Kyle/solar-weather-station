# Stakeholder / Site Validation Record

## VAL-001 — Gate A instructor decision interview complete

### Session metadata

- **Date / mode / duration:** 18 August 2026 / asynchronous written response / questions 1–10
- **Participant role:** ENGG2202 B1/B2 instructor and provisional primary deployment-decision owner
- **Facilitator / note taker:** OpenAI Codex, with participant review required
- **Consent boundary:** written notes and paraphrase only; no audio, video, photos or unnecessary personal data
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)
- **Completion status:** Gate A participant interview complete; external role, site, reference-access and measured evidence remain separate gates

### Hypothesis shown to participant

- **Primary decision owner:** ENGG2202 B1/B2 instructor responsible for deciding whether a supervised field test may proceed
- **Candidate site/context:** accessible HKU teaching-site hypothesis; not discussed or validated in this batch
- **Decision the evidence should support:** whether the prototype may progress from bench work to a supervised 72-hour outdoor integration run
- **Candidate actions:** go / conditional go / no-go; separately classify teaching-demo readiness versus unattended-deployment readiness

### Evidence record

| Question / task | Participant evidence | Evidence type | Engineering implication | Follow-up owner |
|---|---|---|---|---|
| Recall a prototype field-readiness decision and missing evidence | A successful bench demonstration was insufficient. The participant needed sustained-operation, data-quality, power-margin, heat, ingress, mounting, recovery and fault-response evidence under less-controlled conditions. | Participant experience and decision preference; not yet project test evidence | Field readiness must be supported by time-series and abnormal-condition evidence, not one successful reading/demo. | Project team converts needs into tests; instructor reviews thresholds |
| Identify the action enabled by 72-hour evidence | The desired result is an explicit `go`, `conditional go` or `no-go` decision. Conditional go must name the subsystem change and repeat test. Teaching-demo readiness must remain distinct from long-term unattended deployment. | Participant decision statement | The report must present a decision recommendation, required corrective action and scope of the claim; 72 hours cannot prove long-term unattended operation. | Confirmed in the completed Gate A interview |
| Identify immediate do-not-deploy / stop-test conditions | Non-negotiable concerns include battery distress or short-circuit risk; wet exposed live connections; water reaching energised electronics; unstable mounting/fall risk; unprotected public access; abnormal heat, smell or smoke; weather beyond the approved test envelope; and uncontrolled repeated resets. Long data outage or clearly untrustworthy sensing also ends a run when continued operation cannot produce decision-useful evidence. | Participant safety/decision statement | These become provisional stop controls and pre-deployment checks. Occasional missing records are a diagnostic issue, not automatically a stop condition. | Project team drafts checklist; site gatekeeper and responsible safety approver must confirm controls |
| Rank observations for the first 72-hour run | Essential evidence is primary-sensor plausibility/anomalies, battery voltage/basic supply state, ingress/condensation/connector condition, gaps/restarts/recovery and functioning local logging. Solar input/energy detail, detailed interface-error statistics and internal temperature are useful or become essential when they are the test focus. Long-term reliability statistics, battery degradation modelling, packet-level analysis and fixed-site GNSS accuracy are not first-run priorities. | Participant evidence-priority decision | Data collection should be decision-led. The first run must not become an unbounded telemetry exercise. | Project team maps essential evidence to logging/checklist fields; instructor confirms final test scope |
| Distribute evidence before, during and after the run | Before: supply, sensor plausibility, local logging/outage behaviour, restart, enclosure/cables/mounting/public risk, test purpose, stop conditions and owners. During: automatic core logging plus at least daily human observation. After: inspect enclosure/connectors/battery/mounting/sensor contamination; quantify completeness, resets, outages and recovery; issue a continue/modify/bench decision and next action. | Participant workflow requirement | A final CSV alone is insufficient. The evidence package needs a signed/role-confirmed pre-check, observation record, retrieval inspection and decision record. | Students prepare records; TA verifies execution; instructor approves start and final decision |
| Allocate approval, operation, stop and removal responsibilities | Venue/site staff and instructor approve the location; instructor makes the deployment-readiness decision; students install, log and inspect under TA supervision; any observer may stop immediately for a clear safety hazard; instructor decides continuation for non-immediate technical/data faults; students remove under supervision, while competent staff/instructor handle electrical, severe ingress or battery incidents. | Participant governance and safety decision | Project ownership must be separated from safety approval. The workflow needs named people, escalation and safe-removal conditions before deployment. | Instructor and site gatekeeper confirm institutional authority; TA validates operational feasibility |
| Define what a 72-hour run can and cannot prove | The participant accepted 72 hours as a first field-validation horizon. It may support progression to a next test by exposing short-term continuity, sensor anomalies, power behaviour, recovery, local logging and obvious physical faults. It cannot establish unattended/seasonal/industrial reliability, long-term drift, complete energy sizing, formal IP protection or resilience to Hong Kong extremes. | Participant claim-boundary decision | A successful run changes the action to “proceed to the next stage,” never “validation complete.” | Project team carries the limitation into reports and release claims |
| Select an acceptable reference and comparison rule | Priority is a calibrated/reliable commercial station co-located nearby; second is reliable handheld spot checks before/during/after; third is trend comparison with a nearby trusted station. Without equipment, use range, cross-sensor, trend, jump/stuck/outlier checks. Investigate repeated differences beyond manufacturer specification; calibrate stable offset where justified and replace a sensor that remains unstable after calibration. | Participant comparison strategy; exact instrument and tolerance not yet selected | Independent comparison is essential, but nearby-station values are contextual trends rather than strict calibration truth because siting/microclimate differ. | Project team checks HKU loan access, specifications and variable-specific tolerance; instructor approves protocol |
| Decide when to buy/borrow rather than build | Buy or borrow when dependable/traceable local data is the objective, especially for formal research, safety-related decisions, long-duration monitoring or when no one can maintain a student system. Build when sensing, IoT, power, enclosure, integration, field testing and trade-off learning are themselves objectives. A commercial reference plus student prototype best serves both needs. | Participant strategy decision | Concept E is supported for this educational purpose, while turnkey purchase remains preferred for a data-service-only purpose. | Gate E re-scores alternatives and checks real loan/procurement evidence |
| Bound Green Technology and ESG claims | Appropriate language covers educational exploration of local environmental monitoring, solar/low-power sensing, renewable-energy/consumption trade-offs, IoT engineering and sustainability-related field learning. Current evidence does not justify carbon-reduction, carbon-neutrality, climate-solution, ESG-performance, commercial-grade, important-decision data or “solar therefore sustainable” claims. | Participant sustainability-claim decision | Claims must follow demonstrated system evidence and a defined baseline; “educational prototype” is the correct current identity, not “ESG solution.” | Project team uses claim review in reports/README; future impact claims require separate baseline and evidence |

### First-run evidence priority

| Priority | Evidence |
|---|---|
| Essential | primary sensor readings/plausibility/anomalies; timestamps and missing intervals; battery-voltage/basic supply state; restarts and recovery; local-logging status; significant communication failure; enclosure ingress/condensation, connectors and mounting condition |
| Helpful or conditional | basic solar input; detailed energy balance; detailed RS-485/network/GNSS error statistics; internal enclosure temperature; upgrade to essential when the subsystem is the purpose of the run |
| Not required in the first run | long-term reliability statistics; complete battery-degradation model; packet-level analysis of every error; GNSS-accuracy analysis for a fixed, manually confirmed location |

### Reference/comparison hierarchy confirmed for planning

1. co-located calibrated or otherwise reliable commercial weather station;
2. reliable handheld instrument spot checks before, during and after the run;
3. nearby trusted station for trend/context only, with siting and microclimate differences stated; or
4. if no independent instrument is available, range, cross-sensor, trend, jump, stuck-value and outlier checks—clearly labelled as plausibility rather than calibration.

A repeated difference beyond the relevant manufacturer specification triggers investigation. A stable, explainable offset may be calibrated; random or unstable disagreement that remains after a justified calibration attempt triggers sensor replacement or a narrower measurement claim. Variable-specific project tolerances remain to be approved.

### Decision and threshold record

| Area | Essential evidence stated in Gate A | Candidate threshold / stop condition | Status | Further validation |
|---|---|---|---|---|
| Site permission and safety | stable mounting, protected public boundary, approved weather envelope | stop for unstable/falling equipment, uncontrolled public access or weather outside the approved envelope | Provisional participant statement | site gatekeeper and site walk |
| Data continuity and recovery | primary readings, timestamps, gaps, restarts, significant communication faults and local-logging/recovery state | occasional missing points require diagnosis; stop when a long outage or untrustworthy data makes the run non-decision-useful | Essential evidence confirmed; numeric threshold open | define duration/completeness threshold in tabletop test |
| Power margin | sustained supply, remaining margin, abnormal heating and interruption recovery | stop for battery heat/swelling/leakage, short-circuit risk, smoke/smell or uncontrolled reset cycle | Provisional stop condition | instrumentation, battery controls and numeric margin still required |
| Sensor/reference comparison | independent reference where accessible plus specification, range, trend, drift/jump/stuck/outlier evidence | investigate a repeated difference beyond manufacturer specification; replace/narrow claim when instability remains after justified calibration | Comparison rule confirmed; instrument/tolerances open | identify loan/reference, co-location method and variable-specific tolerance |
| Interface diagnostics | significant communication failure, local logging and recovery; detailed error statistics only when decision-relevant | unknown repeated resets or loss of control blocks deployment | First-run priority confirmed | recoverable-fault threshold remains open |
| Enclosure condition | pre-check, at least daily observation and post-retrieval inspection for ingress, condensation, connector/cable/mounting change | stop for water reaching energised electronics or exposed wet live connections | Evidence timing confirmed | site-specific exposure and inspection method remain open |
| Maintenance and response | named student, TA, instructor and site roles; daily observation; fault escalation and safe removal | any observer stops an immediate safety hazard; instructor decides continuation for non-immediate technical/data faults | Role model stated by participant | institutional/site authority and TA workflow require confirmation |

### Gate A outcome

- **Primary stakeholder:** confirmed as the instructor for the supervised prototype field-readiness decision; formal site and institutional safety authority remain separate.
- **Site/context:** unchanged and unvalidated; the instructor interview provided no site-approval evidence.
- **Decision statement:** the 72-hour evidence must support `go / conditional go / no-go`, mapped to `continue / continue with modification / return to bench`; a successful result permits only the next test stage.
- **Decision possible now:** define the intended decision, evidence priorities, first-run claim boundary, provisional stop controls, role model, reference hierarchy and buy/build rule; do not yet authorise a site deployment.
- **Information still missing:** formal role/site authority; TA workflow feasibility; site permission; actual reference/loan availability; variable-specific tolerances; numeric data/power thresholds; tabletop decision agreement; measured test evidence; current quotations and Gate E matrix sensitivity.
- **Solution-matrix impact:** Gate A supports Concept E for the educational objective and turnkey buy/borrow for a data-service-only objective. Safety, recoverability, diagnostic visibility, reference access and learning value require stakeholder re-scoring during Gate E; weights are not changed yet.

### Review notes

- The participant contradicted any assumption that one successful outdoor/bench demonstration establishes field readiness.
- The stop controls are stakeholder requirements, not proof that the current hardware satisfies them.
- Gate A is complete, but it does not close Issue #3: Gates B–E and procurement/reference evidence remain open.

---

## VAL-002 — Gate B TA workflow interview

### Session metadata

- **Date / mode:** 18 August 2026 / asynchronous written response
- **Participant evidence status:** teaching-assistant participant; role confirmed by the instructor after the written response; name and unnecessary personal data not recorded
- **Facilitator / note taker:** OpenAI Codex structured the participant's written answers in the instructor conversation
- **Consent boundary:** written notes and paraphrase only; no audio, video, photos or unnecessary personal data
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)
- **Gate status:** TA workflow interview completed; the separate operational dry run remains required before deployment

### Workflow evidence

| Question / task | TA evidence | Implication | Remaining validation |
|---|---|---|---|
| Can the checklist be executed? | Yes if it is short, uses observable `yes / no / not applicable` checks and states direct stop actions. A single form requiring unaided judgement across sensing, batteries, waterproofing, networks and structures would invite unverified “all yes” completion. | Separate the full evidence record from a concise three-stage operator checklist and anomaly/action guide. | Independent TA completes a dry run without author coaching. |
| How much time is realistic? | Estimated bench check 15–20 min; site installation 20–30 min; initial data confirmation 10–15 min; daily site check 10–15 min; daily dashboard review 5–10 min; removal 15–20 min; post-retrieval check 20–30 min. The first installation should reserve 45–60 min. | Plan workload explicitly and measure actual duration during the first pilot before scaling to many teams. | Record actual start/end times and TA interventions. |
| Can a TA interpret data and anomalies? | A TA can identify missing output, obviously implausible readings, gaps, falling battery voltage, reboots, long network outage, missing local logs, ingress and loose mounting. Drift limits, RS-485 replacement thresholds, solar-charge profiles and root-cause attribution require an expected-range/normal-behaviour guide. | The pack needs normal / investigate / stop categories and project-specific thresholds sourced from locked hardware and the approved test. | Lock sensor models, battery threshold, weather envelope and recoverable-fault definitions. |
| Are student/TA responsibilities realistic? | Students install, follow checks, record, inspect, report, analyse and propose changes. TA verifies/supervises, identifies obvious hazards and anomaly category, checks escalation and records major issues. Instructor owns deployment approval, safety criteria and significant continuation decisions. | TA verification must not replace student engineering ownership. | Independent TA confirms workload and authority in practice. |
| Is the escalation path clear? | Student records and informs TA; TA classifies technical versus safety issue. Ordinary technical issues are investigated and escalated if test quality changes. Immediate safety risks are stopped/isolated first, then reported. Site-related problems route through the instructor/designated contact to venue staff. | State explicitly: any student or TA may stop an immediate safety hazard without waiting for instructor permission. | Confirm out-of-hours contacts, site access and restart authority. |
| What is missing operationally? | One-page checklist; anomaly guide; stop criteria; expected sensor/normal-behaviour ranges; battery and weather limits; shutdown/restart steps; instructor/site contacts; dashboard/log/local-logger permissions; site/out-of-hours access; multimeter, hand tools, spares, mounting/sealing materials and reference instrument. | Deployment readiness includes people, access and tools—not only hardware function. | Complete the contacts/access/tools record and run a readiness review. |

### Estimated workload to test in the first pilot

| Activity | Planning estimate | Actual duration | TA intervention / lesson |
|---|---:|---:|---|
| Pre-deployment bench check | 15–20 min | | |
| Site installation | 20–30 min | | |
| Initial data confirmation | 10–15 min | | |
| Daily site check | 10–15 min | | |
| Daily dashboard/log review | 5–10 min | | |
| Removal | 15–20 min | | |
| Post-retrieval inspection | 20–30 min | | |

### Gate B interview outcome

- A real TA confirmed that the proposed role split is operationally plausible when the on-site material is short, observable and explicit about stop authority.
- The existing full field-readiness record is useful as an evidence package, not as the only on-site checklist.
- Quick operator, anomaly/escalation and contacts/access/tools sheets are required before a supervised deployment dry run.
- The Gate B interview is complete. T-077, T-078, Gates C–E and Issue #3 remain open; no field executability or deployment readiness is claimed yet.

---

## VAL-003 — Gate C instructor pre-walk requirements

### Session metadata

- **Date / mode:** 18 August 2026 / asynchronous written response
- **Participant role:** course instructor and deployment-decision owner; not the site gatekeeper
- **Facilitator / note taker:** OpenAI Codex structured the participant's written answers
- **Consent boundary:** written notes and paraphrase only; site photos, names, access details and exact location require separate permission and data minimisation
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)
- **Gate status:** pre-walk requirements complete; Gate C remains open until the responsible site staff confirms the permission route and candidate-site record

### Pre-walk evidence

| Area | Instructor evidence / requirement | What the site gatekeeper must confirm |
|---|---|---|
| Candidate types | Candidate A is a more open outdoor point for fuller exposure; Candidate B is a more controlled semi-open point with less public contact for the first 72-hour run. No exact point is selected. | Exact points, ownership boundary, permitted use and preferred first-test candidate. |
| Authority and permission | Instructor approval covers technical/teaching readiness but is insufficient for use of an HKU location. Innovation Wing technical staff is the first contact; Faculty, building management, Estates or safety review may also apply. Written confirmation is preferred over verbal permission alone. | Managing unit, final approver, escalation path, required form/email/record and any higher approval. |
| Duration, footprint and access | The first run is temporary and continuous for 72 hours, with a small footprint, no main-route obstruction, no permanent modification and rapid safe removal. Normal, after-hours and emergency access are unknown. | Maximum duration/footprint, boundary/signage, access hours, escort/key/registration, after-hours entrant and emergency removal authority/response. |
| Mounting and wind load | Prefer a freestanding tripod/weighted base, then added ballast; use a clamp only where explicitly approved. No drilling or unapproved structural attachment. Review centre of gravity, cables, fall zone and the solar panel as a wind-load surface. | Permitted mounting method/surface, height/load limits, ballast/clamp restrictions, fall zone and building-structure constraints. |
| Public and information security | Prefer a point people cannot readily touch. Protect batteries, live electronics, power wiring, unstable/moving or hot parts; remove trip, sharp-edge, pinch, tamper and theft risks. Do not publish exact coordinates, access routes or security-sensitive details by default. | Required boundary/signage/enclosure/security, acceptable public separation and what site/location information may be retained or published. |
| Environmental usefulness and bias | Require some direct sun for solar-cycle evidence and usable sky view for GNSS. Document shadow, building/tree obstruction, wind turbulence, natural versus drainage/irrigation/cleaning water and local heat/exhaust/reflective surfaces. This is not a claim of formal meteorological siting. | Observed exposure/bias, restricted zones and whether each candidate can support the named first-test questions. |
| Network and monitoring | Stable Wi-Fi is desirable but not a deployment prerequisite when timestamps and local logging continue. Personal hotspot/cellular use is not assumed. Remote status supports but does not replace daily physical inspection. | Permitted network options/policy, coverage test, access method and how an outage affects safe operation/retrieval. |
| Weather, inspection and response | Students make the daily basic check; TA verifies records; instructor decides non-immediate continuation. Hong Kong Observatory forecasts/warnings inform planning. No invented numeric cut-off is claimed before structural/site review. Students must not assume night access. | Site-specific weather stop/retrieval rules, inspection times, after-hours contact, remote isolation option and maximum safe retrieval response. |
| Evidence and reference | Retain permitted candidate photos, sketch, footprint/orientation, mounting/fall zone, circulation, shadow/sky/wind/water/heat observations, network result, hazards, install/removal route and staff restrictions. Ask whether a commercial station or handheld reference can be borrowed. | Photo/sketch permission, sensitive-information limits, approved record, reference-instrument availability and owner. |

### Gate C preparation outcome

- The intended deployment boundary is now clear enough to conduct a structured site walk.
- Site ownership, exact approver, exact point, footprint, access, mounting permission, weather response and reference availability remain unknown—not silently assumed.
- Official HKU pages confirm the Innovation Wing Office (`innowing@hku.hk`) as the initial enquiry route, Faculty of Engineering management context and restricted/member access. They do not confirm ownership or approval of an adjacent outdoor point.
- The [Gate C site-validation pack](../../tests/site-validation-pack/README.md) is the execution record for the site gatekeeper and walk.
- Gate C and Issue #3 remain open. No site approval or deployment readiness is claimed.

---

## Reusable blank session template

Copy this section for each session. Record role-based evidence without unnecessary personal data.

## Session metadata

- **Record ID:** VAL-
- **Date / mode / duration:**
- **Participant role:** instructor / TA / site gatekeeper / learner / reference-instrument owner
- **Facilitator / note taker:**
- **Consent boundary:** notes / direct quotes / audio-video / photos / no recording
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)

## Current hypothesis shown to participant

- **Primary decision owner:**
- **Candidate site/context:**
- **Decision the evidence should support:**
- **Four candidate actions:** proceed / revise / return to bench / use reference only

## Evidence record

| Question / task | Participant evidence or observed action | Fact / participant view / team inference | Implication | Follow-up owner |
|---|---|---|---|---|
| | | | | |

## Decision and thresholds

| Area | Essential evidence | Candidate threshold / stop condition | Confirmed, changed or rejected? | Source / owner |
|---|---|---|---|---|
| Site permission and safety | | | | |
| Data continuity and recovery | | | | |
| Power margin | | | | |
| Sensor/reference comparison | | | | |
| Interface diagnostics | | | | |
| Enclosure condition | | | | |
| Maintenance and response | | | | |

## Outcome

- **Confirmed/changed primary stakeholder:**
- **Confirmed/changed site/context:**
- **Confirmed/changed decision statement:**
- **Selected action from the evidence provided:**
- **Information still missing:**
- **Change required in problem statement:**
- **Change required in solution-landscape criteria/weights:**
- **New/updated Issue(s):**

## Reflection

- What did the team expect that the participant contradicted?
- What remains preference rather than evidence?
- What decision can now be made that could not be made before?
