# 01 — Problem Identification

## Why two stakeholder layers are required

The project has an educational role and an engineering role. Treating them as the same would allow "it is useful for teaching" to replace real problem identification.

| Layer | Primary stakeholder | Need | Decision/action supported | Validation status |
|---|---|---|---|---|
| ENGG2202 exemplar | Course instructor/TA team and student project teams | A live, inspectable example of the full problem-to-release journey | Decide what evidence and project quality should be visible at each course checkpoint | Supported by the course design; usability with TAs/students still requires pilot feedback |
| Weather-station deployment | ENGG2202 instructor responsible for the supervised prototype field-readiness decision | A transparent field reference and test platform at an accessible HKU site | Decide `go / conditional go / no-go` for a supervised 72-hour first field validation, including required configuration changes and repeat evidence | Gate A instructor interview complete; site/institutional authority, TA workflow and measured evidence remain unvalidated |

## Decision context confirmed; site remains provisional

- **Candidate place:** a controlled outdoor test point adjacent to [Tam Wing Fan Innovation Wing One](https://www.hku.hk/press/news_detail_21321.html), G/F and LG/F of the Hui Oi Chow Science Building on HKU Main Campus. Its prototyping facilities and engineering-learning purpose make it a relevant operational base. This is not an approved mounting location: the exact point, permission, access, exposure, network, security and maintenance conditions require an on-site decision with Innovation Wing staff.
- **Duration:** initial bench qualification followed by a supervised 72-hour first field validation. Success permits progression to a next test stage; it is not unattended/seasonal/industrial reliability, formal IP, complete energy-sizing or extreme-weather evidence.
- **Users:** the instructor/TA team operates the reference process; students inspect the evidence and may compare their own prototypes.
- **Data/diagnostics:** temperature, humidity, pressure, wind, UV/environmental sensing, time/location context, power state, missing-data state, resets and bus faults as the approved configuration allows.
- **Decision boundary:** the evidence supports engineering readiness, configuration and teaching decisions. It must not be used as an official weather service, sole basis for safety-critical decisions, or proof of long-term deployment readiness.

## Gate A-confirmed decision problem

> The ENGG2202 teaching team needs a reproducible way to evaluate whether an environmental-monitoring prototype and its sensor, power and enclosure configuration are ready for a short outdoor deployment at an accessible HKU teaching site, because regional weather data and a polished demonstration alone do not expose local conditions, integration failures, power behaviour or the evidence students need to learn from the decision.

## Evidence still needed before deployment is authorised

The executable interview, site-walk and decision-test workflow is in [Issue #3 — Stakeholder, Site and Decision Validation Plan](01a-stakeholder-validation-plan.md). Use the [validation record](stakeholder-validation-record.md) for each session.

1. Ask at least one independent TA to review or dry-run the VAL-002 field workflow; record actual timing, access, interpretation and escalation friction.
2. Walk the Innovation Wing One candidate area with the responsible staff member and record permission, access, mounting, exposure, network, security, maintenance and safety constraints.
3. Ask a small student/TA group to use the exemplar links during one checkpoint and identify what they can and cannot understand.
4. Define what outcome would change the decision: deploy, revise configuration, return to bench testing or buy/borrow a reference instrument.
5. Identify the maintainer and response when data, power or enclosure evidence fails.

## ENGG2202 learning purpose

Students should see how one hypothesis changed after a real stakeholder interview: the instructor decision owner and decision purpose are now supported, while the site, authority, thresholds and system performance remain open. The repository exposes this mixed evidence state instead of allowing the preferred ESP32-S3 design to become the problem definition.
