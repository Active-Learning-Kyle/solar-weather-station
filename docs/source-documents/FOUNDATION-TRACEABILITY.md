# Project Foundation v0.1 Traceability

## Purpose

This record prevents two common errors:

1. treating the source PDF as if every recommendation were already built and validated; and
2. allowing the living repository to drift away from the original project reasoning without explanation.

The source is the immutable 26-page [`Solar_Weather_Station_Project_Foundation_v0.1.pdf`](Solar_Weather_Station_Project_Foundation_v0.1.pdf), dated 14 August 2026.

## Section mapping

| Foundation section | Living repository location | Current interpretation |
|---|---|---|
| 3. Problem Identification and Project Purpose | `docs/project-journey/01-problem.md` | Working problem statement retained; target user and decision still require field validation |
| 4. Objectives, Scope, and Success Criteria | `docs/project-journey/04-design-requirements.md` | Converted into testable requirement IDs; targets remain proposed until evidence is committed |
| 5. Reference Project Lineage | `docs/project-journey/03-reference-projects.md`, `THIRD_PARTY.md` | Exact URLs and licences recorded; reuse audit remains open in Issue #2 |
| 6. Project Design History and Decisions | `docs/project-journey/05-design-decisions.md` | Claims tagged by evidence level so reported progress is not confused with repository evidence |
| 7-8. Architecture and Hardware | `README.md`, `hardware/` | Architecture retained; exact board, pins, sensor models, and register maps remain incomplete |
| 9. Mechanical and Enclosure Design | `mechanical/` | Triangular/louvered concept and separated power zone recorded; CAD evidence still pending |
| 10. Firmware and Data Architecture | `firmware/esp32s3/`, `dashboard/` | Modular-driver and common-schema direction retained; implementation not yet present |
| 11. RS-485 / Modbus Lessons | `hardware/`, planned diagnostics tools | A/B shorting is explicitly rejected as a valid loopback test; exact field bus design remains open |
| 12. Power and Solar Autonomy | `docs/project-journey/06-budget.md`, Issue #5 | Three-day no-solar autonomy is a planning target, not a measured claim |
| 13. Budgeting and Procurement | `bom/bom.csv`, `docs/project-journey/06-budget.md` | Planning bands retained; quotations and actual cost remain missing |
| 14-16. Validation, Risks, Roadmap | `tests/test-matrix.csv`, Issues #1, #4, #5, #6 | Test IDs and high-priority gaps transferred into trackable work |
| 17. GitHub Blueprint | Repository structure and `.github/` | First GitHub-native structure implemented; release assets and automation remain incomplete |
| 18. Licensing and Attribution | `THIRD_PARTY.md`, `LICENSES/` | No project-wide licence selected until code/design reuse is audited |
| 19. Release Definition of Done | README status, test matrix, Issues | v1.0 is explicitly blocked until the listed evidence exists |
| Appendices A-C | `bom/bom.csv`, `tests/test-matrix.csv` | Baseline BOM and tests migrated with pending values preserved |

## Evidence status of key source claims

| Source claim | Evidence class | Repository treatment |
|---|---|---|
| ESP32-S3 selected as preferred controller | Documented design direction | Retained; exact development-board SKU still open |
| Wind-direction decoding reported working | Project-history report | Not labelled validated until raw frames, heading test, hardware revision, and firmware are committed |
| MAX485 used during diagnostics | Project-history report | Retained as prototype history; not recommended as the final 3.3 V interface without explicit level handling |
| TEL0157 communication succeeded | Project-history report | Communication and outdoor-fix tests remain separate; outdoor fix evidence is still missing |
| Waveshare Solar Power Manager (D) is in the planned architecture | Documented design direction | Exact wiring and complete-system power measurements remain missing |
| Custom triangular/louvered enclosure is in development | Documented concept | CAD, material, assembly-cycle, rain, and thermal-bias evidence remain missing |
| 24-hour stable sensor run | Proposed release criterion | Not completed |
| Three-day autonomy without useful solar input | Planning target | Not measured and not presented as guaranteed runtime |
| 72-hour outdoor validation | Proposed release criterion | Not completed; tracked by Issue #6 |

## Conflicts and cautions

- The PDF describes a future public repository, while the current repository is Private. Public release requires a separate review of licensing, course-document distribution, credentials, location data, and personal information.
- The project is not a certified meteorological station and has no formal IP rating or commercial compliance certification.
- `teamsuperpanda/Weather-Station` uses PolyForm Noncommercial 1.0.0 and was archived on 7 June 2026; it is a learning reference, not a conventional open-source licensing model.
- The James Hughes transmitter and receiver firmware repositories are GPL-3.0. Any copied or adapted code must preserve and satisfy applicable GPL obligations.
- SI1145 is a legacy inferred-UV option. A baseline UV method and its optical path/calibration are still pending.
- Exact current prices, availability, and supplier links are time-dependent and must be refreshed before procurement.
