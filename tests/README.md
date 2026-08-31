# System Tests and Validation Evidence

The backend test suite and PlatformIO builds check software behavior. The records in this folder connect those checks with bench, integration, mechanical and future field evidence.

## Evidence levels

| Level | Meaning |
| --- | --- |
| Automated | A repeatable software check runs locally and in continuous integration |
| Bench verified | Named hardware behavior was observed under a documented bench procedure |
| Integrated verified | The complete named configuration passed an end-to-end procedure |
| Field verified | A versioned configuration operated at an approved site under documented conditions |
| Pending | The acceptance procedure or required authority is not complete |

## Main records

- [`test-matrix.csv`](test-matrix.csv) links project claims to acceptance criteria, evidence and status.
- [`field-readiness-checklist.md`](field-readiness-checklist.md) controls preparation, monitoring, retrieval and review for an outdoor test.
- [`backend/tests/`](../backend/tests/) contains automated API, storage, compatibility and dashboard tests.
- [`docs/milestones/`](../docs/milestones/) contains hardware procedures and observed milestone evidence.

## Minimum content for a new test record

- test ID, date and author;
- repository commit and firmware environment;
- exact board, sensor, CAD and wiring revisions;
- equipment and reference-instrument information;
- conditions and procedure;
- acceptance criteria written before the result;
- raw data, logs, photographs or observations;
- pass, fail or inconclusive outcome; and
- the resulting Issue, revision or claim change.

Compilation is not hardware verification. A diagnostic pass is not production integration. A bench test is not evidence of outdoor reliability.
