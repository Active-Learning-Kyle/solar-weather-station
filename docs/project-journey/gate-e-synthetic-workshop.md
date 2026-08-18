# Gate E — Synthetic Matrix Workshop and Sensitivity Review

> **TEACHING SIMULATION — NOT PROCUREMENT OR STAKEHOLDER EVIDENCE.** The perspectives and sensitivity review below complete the exemplar story. No quotation, loan access, product availability or real independent participant score is implied.

## Decision question

Which strategy best supports the current educational objective while preventing a student-built prototype from being mistaken for a dependable weather-data service?

The scored concepts are:

- **A:** turnkey consumer weather station;
- **B:** industrial sensors with a custom logger;
- **C:** reproduce/adapt the OGE V4 reference;
- **D:** independent modular exemplar; and
- **E:** reliable reference instrument plus modular student exemplar.

## Baseline result

The dated [concept-selection matrix](concept-selection-matrix.csv) gives:

| Concept | A | B | C | D | E |
|---|---:|---:|---:|---:|---:|
| Weighted result / 100 | 61 | 76 | 73 | 79 | **88** |

Concept E leads because it separates two legitimate objectives: reliable comparison/data and open engineering learning.

## Fictional independent perspectives

| Role-play perspective | Priority it would challenge | Conditional preference |
|---|---|---|
| Teaching-focused TA | visible learning, repairability and manageable student workflow | E, provided the reference does not replace student diagnosis |
| Measurement-focused reviewer | accuracy, traceability and reference metadata | E or B; the reference must be primary where dependable data is required |
| Operations-focused reviewer | deployment speed, safety and maintenance burden | B or E; do not deploy the student system without passing the real readiness gates |

These perspectives are prompts for discussion, not recorded participant testimony.

## Sensitivity checks

Two plausible weight shifts were tested without changing the concept scores.

| Scenario | Weight change | A | B | C | D | E | Interpretation |
|---|---|---:|---:|---:|---:|---:|---|
| Baseline | published matrix | 61 | 76 | 73 | 79 | **88** | E leads |
| S1: less teaching, more lifecycle cost | learning visibility 20→10; lifecycle cost 10→20 | 65 | 70 | 71 | 75 | **82** | E remains preferred, but its cost burden becomes clearer |
| S2: less modularity, more operational safety | modularity 10→0; safety/maintenance 10→20 | 65 | 76 | 71 | 75 | **86** | E remains preferred; B becomes the strongest single-system alternative |

This is a limited sensitivity demonstration, not a statistical uncertainty analysis. It shows that the hybrid direction is not dependent on one exact weighting choice; it does not prove current affordability or availability.

## Teaching decision

Select **Concept E — reference instrument plus modular educational prototype** for the exemplar:

> Use a reliable commercial or borrowed instrument as the comparison reference and, where dependable weather data is required, as the primary data source. Continue the student-built weather station as a modular educational prototype, subject to real safety, field-testing and validation evidence.

## What this decision does—and does not—authorise

It authorises the next learning direction: develop, test and compare the modular prototype. It does **not** authorise an HKU site, purchase equipment, claim accuracy, pass the 72-hour test or establish Green Technology/ESG impact.

Real work remains in Issues [#4 sensor selection](https://github.com/heqihao522828-crypto/solar-weather-station/issues/4), [#5 power budget](https://github.com/heqihao522828-crypto/solar-weather-station/issues/5), [#6 outdoor validation](https://github.com/heqihao522828-crypto/solar-weather-station/issues/6) and the reference/quotation evidence tracked by T-083.

## Revisit triggers

Re-score or change the strategy if the reference cannot be accessed within budget, the prototype cannot meet safety/readiness controls, maintenance overwhelms learning value, measured accuracy makes comparison meaningless, or the course objective changes from engineering learning to a dependable weather-data service.

