# ENGG2202 Instructor Exemplar

## Purpose

This repository demonstrates one Green Technology engineering journey, not a model answer for students to copy. It is intended to help the instructor and teaching assistants run the complete workflow before scaling the course.

The course-wide framework now lives in [ENGG2202 - Green Technology](https://github.com/heqihao522828-crypto/ENGG2202-Green-Technology). This repository remains one live exemplar linked stage-by-stage from that course hub.

The two repositories have different sources of truth and a shared review contract. See the [course–exemplar synchronisation record](COURSE-SYNC.md) before changing project status, teaching-stage links or course-facing claims.

## Formal course context

The repository alignment below is based on the retained 10-page HKU course template in `teaching/source-documents/`:

- ENGG2202 Engineering Challenges II, 6 credits, offered across both semesters
- Prerequisite: ENGG1101 Engineering Challenges I or ENGG1320 Engineers in the Modern World
- 144 total learning hours: 24 weekly-meeting hours, 48 project-work hours, 24 self-study/reading hours and 48 assessment hours
- Multidisciplinary teams of 5-6 students working on open-ended, real-world engineering challenges
- Active learning through brainstorming, real-world exploration, prototyping/testing/iteration, reflection/feedback and collaborative peer learning

## Learning pathway and CLO alignment

| Engineering activity | Repository evidence | Formal CLO alignment |
|---|---|---|
| Identify and formulate a meaningful problem | `01-problem.md`, stakeholder evidence, Issues | CLO1 problem-solving; CLO4 societal/environmental responsibility |
| Study existing solutions and contemporary practice | `02-solution-landscape.md` | CLO1 problem-solving; CLO5 contemporary issues and lifelong learning |
| Reproduce and learn from references responsibly | `03-reference-projects.md`, `THIRD_PARTY.md` | CLO2 technical implementation; CLO4 ethical professionalism |
| Define measurable success and constraints | `04-design-requirements.md` | CLO1 problem formulation; CLO4 safety, sustainability and broader impact |
| Select concepts using evidence and trade-offs | `05-design-decisions.md` | CLO1 solution development; CLO2 design within realistic constraints |
| Plan cost, sourcing and risk | `bom/`, `06-budget.md` | CLO1/CLO2 engineering constraints; CLO4 responsibility |
| Build and iterate | Subsystem folders, `07-prototyping.md` | CLO2 prototyping, testing and refinement |
| Validate and communicate limitations | `tests/`, `08-testing.md` | CLO1 evidence-based solution; CLO2 refinement; CLO4 accountability |
| Collaborate through Issues and Pull Requests | `.github/`, review history | CLO3 multidisciplinary teamwork and communication |
| Reflect, self-learn and teach forward | `09-reflection.md`, `AI_USE.md` | CLO5 active/self-directed learning; CLO3 peer communication |

## Formal assessment alignment

| Approved category | Weight | Appropriate repository evidence | Important caution |
|---|---:|---|---|
| Project Progress and Participation (individual) | 24% | Checkpoint summaries, linked Issues, evidence of preparation, reflection and responsible participation | Do not grade raw commit count; quality, understanding and participation matter |
| Written Reports (individual) | 46% | Problem definition, analysis, solution justification, evaluation, ethics/impact and individual interpretation of shared evidence | The repository can supply evidence, but each student must demonstrate individual authorship and mastery |
| Solution Demonstration (team) | 20% | Versioned prototype, clear demonstration plan, requirement/test links and audience-appropriate explanation | A polished demo without traceable validation should not imply a mature solution |
| Teamwork and Collaboration (individual) | 10% | Issue ownership, peer review, meeting evidence, constructive feedback, leadership and accountability | GitHub traces support judgement but do not capture all offline teamwork |

## Suggested two-semester rhythm

### Semester 1 - Learn, reproduce, and adapt

- Frame the problem and stakeholder need
- Compare existing commercial, industrial, research and open-source solutions
- Select and reproduce a reference project or subsystem
- Learn Git/GitHub through Issues, commits, branches, and Pull Requests
- Document what worked, what failed, what was changed, and why

### Semester 2 - Design, build, validate, and release

- Lock requirements, architecture, budget, risk, and project plan
- Build subsystem prototypes and integrate incrementally
- Review progress through linked Issues and evidence
- Validate against measurable criteria
- Release a reproducible open-source project and teach the journey

## Teaching principle

GitHub should not be introduced as a final upload destination. It should be used weekly as the shared engineering workspace. The assessment should reward traceable decisions, evidence, responsible collaboration, and honest iteration - not commit count or a polished README alone.

This exemplar interprets the approved framework; it does not change the formal assessment weights or rubrics.
