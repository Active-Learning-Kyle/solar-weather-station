# Stakeholder / Site Validation Record

## VAL-001 — Gate A instructor interview, batch 1 of 3

### Session metadata

- **Date / mode / duration:** 18 August 2026 / asynchronous written response / questions 1–3
- **Participant role:** ENGG2202 B1/B2 instructor and provisional primary deployment-decision owner
- **Facilitator / note taker:** OpenAI Codex, with participant review required
- **Consent boundary:** written notes and paraphrase only; no audio, video, photos or unnecessary personal data
- **Related Issue:** [#3](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)
- **Completion status:** partial; Gate A questions 4–10 remain unanswered

### Hypothesis shown to participant

- **Primary decision owner:** ENGG2202 B1/B2 instructor responsible for deciding whether a supervised field test may proceed
- **Candidate site/context:** accessible HKU teaching-site hypothesis; not discussed or validated in this batch
- **Decision the evidence should support:** whether the prototype may progress from bench work to a supervised 72-hour outdoor integration run
- **Candidate actions:** go / conditional go / no-go; separately classify teaching-demo readiness versus unattended-deployment readiness

### Evidence record

| Question / task | Participant evidence | Evidence type | Engineering implication | Follow-up owner |
|---|---|---|---|---|
| Recall a prototype field-readiness decision and missing evidence | A successful bench demonstration was insufficient. The participant needed sustained-operation, data-quality, power-margin, heat, ingress, mounting, recovery and fault-response evidence under less-controlled conditions. | Participant experience and decision preference; not yet project test evidence | Field readiness must be supported by time-series and abnormal-condition evidence, not one successful reading/demo. | Project team converts needs into tests; instructor reviews thresholds |
| Identify the action enabled by 72-hour evidence | The desired result is an explicit `go`, `conditional go` or `no-go` decision. Conditional go must name the subsystem change and repeat test. Teaching-demo readiness must remain distinct from long-term unattended deployment. | Participant decision statement | The report must present a decision recommendation, required corrective action and scope of the claim; 72 hours cannot prove long-term unattended operation. | Instructor confirms final wording after questions 4–10 |
| Identify immediate do-not-deploy / stop-test conditions | Non-negotiable concerns include battery distress or short-circuit risk; wet exposed live connections; water reaching energised electronics; unstable mounting/fall risk; unprotected public access; abnormal heat, smell or smoke; weather beyond the approved test envelope; and uncontrolled repeated resets. Long data outage or clearly untrustworthy sensing also ends a run when continued operation cannot produce decision-useful evidence. | Participant safety/decision statement | These become provisional stop controls and pre-deployment checks. Occasional missing records are a diagnostic issue, not automatically a stop condition. | Project team drafts checklist; site gatekeeper and responsible safety approver must confirm controls |

### Partial decision and threshold record

| Area | Essential evidence stated in batch 1 | Candidate threshold / stop condition | Status | Further validation |
|---|---|---|---|---|
| Site permission and safety | stable mounting, protected public boundary, approved weather envelope | stop for unstable/falling equipment, uncontrolled public access or weather outside the approved envelope | Provisional participant statement | site gatekeeper and site walk |
| Data continuity and recovery | continuous logs, visible gaps, restart/recovery behaviour | occasional missing points require diagnosis; stop when a long outage or untrustworthy data makes the run non-decision-useful | Qualitative only | define duration/completeness threshold in questions 4–5 and tabletop test |
| Power margin | sustained supply, remaining margin, abnormal heating and interruption recovery | stop for battery heat/swelling/leakage, short-circuit risk, smoke/smell or uncontrolled reset cycle | Provisional stop condition | instrumentation, battery controls and numeric margin still required |
| Sensor/reference comparison | plausible trends, drift/anomaly detection | stop/retrieve when outputs are clearly untrustworthy and continued running cannot answer the decision | Qualitative only | acceptable reference and tolerance remain unanswered |
| Interface diagnostics | sensor/network interruption, local logging and recovery evidence | unknown repeated resets or loss of control blocks deployment | Provisional stop condition | recoverable-fault definition remains unanswered |
| Enclosure condition | water exclusion from energised electronics and safe protected wiring | stop for water reaching energised electronics or exposed wet live connections | Provisional stop condition | test method and inspection frequency remain unanswered |
| Maintenance and response | students can recognise the fault, explain the risk and state the next action | no test without a known response/removal path for abnormal behaviour | Team inference from participant statement | TA workflow and site escalation path |

### Partial outcome

- **Primary stakeholder:** provisionally supported as the instructor for the supervised test decision; formal site/safety authority remains separate and unvalidated.
- **Site/context:** unchanged and unvalidated; this batch provided no site evidence.
- **Decision statement:** changed from a general readiness judgement to an explicit `go / conditional go / no-go` decision, with teaching-demo readiness reported separately from unattended-deployment readiness.
- **Decision possible now:** define the form of the future decision and provisional stop controls; do not yet authorise deployment.
- **Information still missing:** evidence ranking, before/during/after evidence, role authority, 72-hour limitations, comparison instrument/tolerance, buy-or-borrow trigger, and acceptable Green Technology/ESG claims (questions 4–10); TA workflow; site permission; numeric thresholds; measured test evidence.
- **Solution-matrix impact:** safety, recoverability, diagnostic visibility and decision usefulness require review during Gate E; weights are not changed yet.

### Review notes

- The participant contradicted any assumption that one successful outdoor/bench demonstration establishes field readiness.
- The stop controls are stakeholder requirements, not proof that the current hardware satisfies them.
- This partial interview does not close Gate A or Issue #3.

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
