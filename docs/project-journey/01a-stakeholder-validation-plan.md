# Issue #3 — Stakeholder, Site and Decision Validation Plan

**Status:** validation package prepared; stakeholder/site claims remain provisional  
**Issue:** [#3 Complete the existing-solution landscape study](https://github.com/heqihao522828-crypto/solar-weather-station/issues/3)  
**Purpose:** validate the decision context before re-scoring or locking the buy/adapt/build strategy

## Hypothesis to test—not a confirmed answer

> The primary deployment-decision stakeholder is the ENGG2202 B1/B2 instructor responsible for safe, repeatable outdoor project work. The immediate decision is whether a modular environmental-monitoring prototype is ready for a supervised 72-hour outdoor integration run at an accessible HKU teaching site, and which sensor, power, data and enclosure configuration should proceed.

This hypothesis is useful because it names one decision owner and one near-term decision. It must be changed if interviews show that another person owns the decision, the site serves a different purpose, or local weather data does not materially change the action.

## Stakeholder roles to distinguish

| Role | Current hypothesis | Decision / evidence relationship | Validation needed |
|---|---|---|---|
| Primary decision owner | ENGG2202 B1/B2 instructor | authorises, revises or rejects the supervised field-readiness test and its configuration | 30-minute decision interview |
| Operational user | TA(s) supporting the build/test | prepares equipment, observes faults, interprets logs and escalates problems | 20-minute workflow interview |
| Site gatekeeper | responsible Innovation Wing / HKU facilities or space staff | approves exact location, access, mounting, duration, security and removal | on-site walk and written/recorded permission path |
| Learner/user of evidence | ENGG2202 students | uses the live record to understand problem-to-release engineering | usability observation during a course checkpoint |
| Comparison-resource owner | HKU unit/lab/person responsible for a loan/shared reference instrument | controls access, data export, calibration status and loan conditions | availability/loan enquiry |

Students are important users of the exemplar, but teaching usefulness cannot substitute for deployment permission, safety responsibility or a real field decision.

## Decision outcomes the evidence must support

The stakeholder must be able to choose one of four actions:

1. **Proceed:** authorise the planned supervised 72-hour integration run with a named configuration and controls.
2. **Revise:** change sensor, power, data, mounting or enclosure configuration, then repeat a named bench test.
3. **Return to bench:** do not deploy because a readiness/safety condition is unresolved.
4. **Use a reference only:** buy, borrow or share a suitable instrument when the need is dependable local data rather than open engineering learning.

If the collected data cannot distinguish these actions, it is not decision-useful for this phase.

## Data-to-decision map to validate

| Evidence family | Candidate observations | Decision it may change | Stakeholder must confirm |
|---|---|---|---|
| Safety and site control | mounting security, cable/strain relief, battery protection, public interaction, weather limits, access/removal plan | proceed, revise or stop | non-negotiable stop conditions and responsible approver |
| Data continuity | expected/received records, timestamps, missing intervals, resets, storage recovery | data architecture readiness | acceptable completeness and recovery behaviour |
| Power behaviour | battery voltage/state estimate, load profile, brownouts/resets, solar input context | power configuration and run duration | minimum margin and stop threshold |
| Sensor/reference plausibility | range checks, co-located differences, drift, stuck values, metadata/configuration | keep, calibrate, replace or narrow the claim | acceptable comparison method and tolerance |
| Interface diagnostics | Modbus/RS-485 errors, GNSS/time state, logging/network faults | interface protection, retry and local-first strategy | which faults are recoverable vs deployment-blocking |
| Enclosure/serviceability | ingress indicators, condensation, heat, connector condition, inspection time | enclosure revision and maintenance plan | acceptable condition and inspection frequency |
| Environmental context | temperature, humidity, pressure, wind and approved additional variables | interpret system behaviour during the run | variables required for engineering context, not an official weather service |

No numeric threshold in this table is approved yet. The interviews must define or reject candidate thresholds before the test matrix is locked.

## Validation Gate A — Instructor decision interview

**Duration:** 30 minutes  
**Output:** completed `stakeholder-validation-record.md`, confirmed/changed decision statement and ranked evidence needs

Ask:

1. Recall the last time you judged whether a student prototype was ready to leave the bench. What decision did you make and what evidence was missing?
2. For this exemplar, what exact action should be possible after reviewing the 72-hour evidence?
3. What conditions would cause an immediate `do not deploy` or `stop test` decision?
4. Which sensor, power, interface, enclosure and data observations are essential, useful or unnecessary?
5. What evidence must exist before deployment, during the run and after retrieval?
6. Who is allowed to authorise the site, operate the system, respond to failure and remove the equipment?
7. Is a 72-hour run the right first decision horizon? What can it not prove?
8. What comparison/reference instrument is acceptable, and what difference would trigger calibration/replacement?
9. If the only need is reliable local weather data, under what conditions should the course borrow or buy rather than build?
10. Which Green Technology/ESG claims are appropriate at this stage, and which would be misleading?

## Validation Gate B — TA workflow interview

**Duration:** 20 minutes per TA or one group session  
**Output:** operational workflow, maintenance owner, alert/escalation path and repository usability findings

Ask the TA to walk through preparation, installation, daily inspection, data review, fault response, removal and handover. Record where instructions, tools, access, time or expertise are missing. Ask the TA to make a mock `proceed/revise/bench` decision from a small sample of logs and note what cannot be interpreted.

## Validation Gate C — Candidate-site walk

Do not describe a location as approved until the responsible staff member confirms the permission path.

Record:

- exact approver and written/recorded permission route;
- temporary test boundary and maximum duration;
- access hours, supervision and emergency/removal contact;
- mounting surface, load, height, fall/object and public-contact risks;
- sun/shade, wind obstruction/turbulence, rain/irrigation and heat sources;
- cable, trip, battery, electrical and fabrication/tool restrictions;
- network availability and whether network is needed at all;
- theft/tampering/security and whether exact location should remain non-public;
- maintenance/inspection route and weather-triggered stop conditions;
- location and availability of a comparison instrument; and
- photos/sketches that may be retained without exposing sensitive information.

## Validation Gate D — Tabletop decision test

Prepare a one-page synthetic or clearly labelled example dataset containing:

- one missing-data interval;
- one reset or power-margin warning;
- one sensor/reference disagreement;
- one normal period; and
- one enclosure inspection observation.

Ask the instructor and TA independently to select `proceed`, `revise`, `return to bench` or `reference only`, state the evidence used and identify missing information. Disagreement is useful evidence: it reveals ambiguous thresholds, roles or displays.

Do not present synthetic data as a real weather-station result.

## Validation Gate E — Matrix re-score workshop

Only after Gates A–D:

1. confirm the decision and stakeholder in `01-problem.md`;
2. revise the criteria and weights in `concept-selection-matrix.csv` before seeing totals;
3. score alternatives independently, then discuss disagreements;
4. test sensitivity by changing the two most disputed weights;
5. confirm buy, borrow, adapt or build direction and revisit trigger;
6. obtain current Hong Kong/institutional quotations and loan availability; and
7. link the selected comparison/co-location method.

## Evidence required to close Issue #3

- [ ] Primary decision owner interviewed and decision statement confirmed or replaced.
- [ ] At least one TA workflow interview completed.
- [ ] Site gatekeeper and permission route identified; candidate-site walk completed.
- [ ] Decision outcomes, stop conditions and evidence needs agreed.
- [ ] Reference/loan options and data-access needs checked.
- [ ] Tabletop decision test completed and disagreements recorded.
- [ ] Matrix criteria/weights re-scored with stakeholder input and sensitivity reviewed.
- [ ] Hong Kong/institutional cost and availability evidence added.
- [ ] `01-problem.md`, `02-solution-landscape.md` and the Issue comment updated with findings.

Until these items are complete, Concept E remains a provisional strategy rather than a locked purchase or design decision.

## Evidence and privacy rules

- Record role, date, decision and evidence; avoid unnecessary personal data.
- Obtain consent before audio/video recording or direct quotation.
- Keep exact security-sensitive site information out of a future public release.
- Link controlled evidence rather than copying confidential institutional material.
- Separate participant statements, observed facts and team interpretation.
- Treat stakeholder preference as input, not automatic technical proof.
