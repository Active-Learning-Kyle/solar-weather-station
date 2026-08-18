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
