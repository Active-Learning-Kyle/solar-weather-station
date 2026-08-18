# Stakeholder / Site Validation Record

## VAL-001 — Gate A instructor interview, batch 2 of 3

### Session metadata

- **Date / mode / duration:** 18 August 2026 / asynchronous written response / questions 1–6
- **Participant role:** ENGG2202 B1/B2 instructor and provisional primary deployment-decision owner
- **Facilitator / note taker:** OpenAI Codex, with participant review required
- **Consent boundary:** written notes and paraphrase only; no audio, video, photos or unnecessary personal data
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)
- **Completion status:** partial; Gate A questions 7–10 remain unanswered

### Hypothesis shown to participant

- **Primary decision owner:** ENGG2202 B1/B2 instructor responsible for deciding whether a supervised field test may proceed
- **Candidate site/context:** accessible HKU teaching-site hypothesis; not discussed or validated in this batch
- **Decision the evidence should support:** whether the prototype may progress from bench work to a supervised 72-hour outdoor integration run
- **Candidate actions:** go / conditional go / no-go; separately classify teaching-demo readiness versus unattended-deployment readiness

### Evidence record

| Question / task | Participant evidence | Evidence type | Engineering implication | Follow-up owner |
|---|---|---|---|---|
| Recall a prototype field-readiness decision and missing evidence | A successful bench demonstration was insufficient. The participant needed sustained-operation, data-quality, power-margin, heat, ingress, mounting, recovery and fault-response evidence under less-controlled conditions. | Participant experience and decision preference; not yet project test evidence | Field readiness must be supported by time-series and abnormal-condition evidence, not one successful reading/demo. | Project team converts needs into tests; instructor reviews thresholds |
| Identify the action enabled by 72-hour evidence | The desired result is an explicit `go`, `conditional go` or `no-go` decision. Conditional go must name the subsystem change and repeat test. Teaching-demo readiness must remain distinct from long-term unattended deployment. | Participant decision statement | The report must present a decision recommendation, required corrective action and scope of the claim; 72 hours cannot prove long-term unattended operation. | Instructor confirms final wording after questions 7–10 |
| Identify immediate do-not-deploy / stop-test conditions | Non-negotiable concerns include battery distress or short-circuit risk; wet exposed live connections; water reaching energised electronics; unstable mounting/fall risk; unprotected public access; abnormal heat, smell or smoke; weather beyond the approved test envelope; and uncontrolled repeated resets. Long data outage or clearly untrustworthy sensing also ends a run when continued operation cannot produce decision-useful evidence. | Participant safety/decision statement | These become provisional stop controls and pre-deployment checks. Occasional missing records are a diagnostic issue, not automatically a stop condition. | Project team drafts checklist; site gatekeeper and responsible safety approver must confirm controls |
| Rank observations for the first 72-hour run | Essential evidence is primary-sensor plausibility/anomalies, battery voltage/basic supply state, ingress/condensation/connector condition, gaps/restarts/recovery and functioning local logging. Solar input/energy detail, detailed interface-error statistics and internal temperature are useful or become essential when they are the test focus. Long-term reliability statistics, battery degradation modelling, packet-level analysis and fixed-site GNSS accuracy are not first-run priorities. | Participant evidence-priority decision | Data collection should be decision-led. The first run must not become an unbounded telemetry exercise. | Project team maps essential evidence to logging/checklist fields; instructor confirms final test scope |
| Distribute evidence before, during and after the run | Before: supply, sensor plausibility, local logging/outage behaviour, restart, enclosure/cables/mounting/public risk, test purpose, stop conditions and owners. During: automatic core logging plus at least daily human observation. After: inspect enclosure/connectors/battery/mounting/sensor contamination; quantify completeness, resets, outages and recovery; issue a continue/modify/bench decision and next action. | Participant workflow requirement | A final CSV alone is insufficient. The evidence package needs a signed/role-confirmed pre-check, observation record, retrieval inspection and decision record. | Students prepare records; TA verifies execution; instructor approves start and final decision |
| Allocate approval, operation, stop and removal responsibilities | Venue/site staff and instructor approve the location; instructor makes the deployment-readiness decision; students install, log and inspect under TA supervision; any observer may stop immediately for a clear safety hazard; instructor decides continuation for non-immediate technical/data faults; students remove under supervision, while competent staff/instructor handle electrical, severe ingress or battery incidents. | Participant governance and safety decision | Project ownership must be separated from safety approval. The workflow needs named people, escalation and safe-removal conditions before deployment. | Instructor and site gatekeeper confirm institutional authority; TA validates operational feasibility |

### First-run evidence priority

| Priority | Evidence |
|---|---|
| Essential | primary sensor readings/plausibility/anomalies; timestamps and missing intervals; battery-voltage/basic supply state; restarts and recovery; local-logging status; significant communication failure; enclosure ingress/condensation, connectors and mounting condition |
| Helpful or conditional | basic solar input; detailed energy balance; detailed RS-485/network/GNSS error statistics; internal enclosure temperature; upgrade to essential when the subsystem is the purpose of the run |
| Not required in the first run | long-term reliability statistics; complete battery-degradation model; packet-level analysis of every error; GNSS-accuracy analysis for a fixed, manually confirmed location |

### Partial decision and threshold record

| Area | Essential evidence stated in batch 1 | Candidate threshold / stop condition | Status | Further validation |
|---|---|---|---|---|
| Site permission and safety | stable mounting, protected public boundary, approved weather envelope | stop for unstable/falling equipment, uncontrolled public access or weather outside the approved envelope | Provisional participant statement | site gatekeeper and site walk |
| Data continuity and recovery | primary readings, timestamps, gaps, restarts, significant communication faults and local-logging/recovery state | occasional missing points require diagnosis; stop when a long outage or untrustworthy data makes the run non-decision-useful | Essential evidence confirmed; numeric threshold open | define duration/completeness threshold in tabletop test |
| Power margin | sustained supply, remaining margin, abnormal heating and interruption recovery | stop for battery heat/swelling/leakage, short-circuit risk, smoke/smell or uncontrolled reset cycle | Provisional stop condition | instrumentation, battery controls and numeric margin still required |
| Sensor/reference comparison | plausible trends, drift/anomaly detection | stop/retrieve when outputs are clearly untrustworthy and continued running cannot answer the decision | Qualitative only | acceptable reference and tolerance remain unanswered |
| Interface diagnostics | significant communication failure, local logging and recovery; detailed error statistics only when decision-relevant | unknown repeated resets or loss of control blocks deployment | First-run priority confirmed | recoverable-fault threshold remains open |
| Enclosure condition | pre-check, at least daily observation and post-retrieval inspection for ingress, condensation, connector/cable/mounting change | stop for water reaching energised electronics or exposed wet live connections | Evidence timing confirmed | site-specific exposure and inspection method remain open |
| Maintenance and response | named student, TA, instructor and site roles; daily observation; fault escalation and safe removal | any observer stops an immediate safety hazard; instructor decides continuation for non-immediate technical/data faults | Role model stated by participant | institutional/site authority and TA workflow require confirmation |

### Partial outcome

- **Primary stakeholder:** provisionally supported as the instructor for the supervised test decision; formal site/safety authority remains separate and unvalidated.
- **Site/context:** unchanged and unvalidated; this batch provided no site evidence.
- **Decision statement:** changed from a general readiness judgement to an explicit `go / conditional go / no-go` decision, with teaching-demo readiness reported separately from unattended-deployment readiness.
- **Decision possible now:** define the form of the future decision and provisional stop controls; do not yet authorise deployment.
- **Information still missing:** 72-hour limitations, comparison instrument/tolerance, buy-or-borrow trigger and acceptable Green Technology/ESG claims (questions 7–10); formal role/site authority; TA workflow feasibility; site permission; numeric thresholds; measured test evidence.
- **Solution-matrix impact:** safety, recoverability, diagnostic visibility and decision usefulness require review during Gate E; weights are not changed yet.

### Review notes

- The participant contradicted any assumption that one successful outdoor/bench demonstration establishes field readiness.
- The stop controls are stakeholder requirements, not proof that the current hardware satisfies them.
- This partial interview does not close Gate A or Issue #3; questions 7–10 remain.

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
