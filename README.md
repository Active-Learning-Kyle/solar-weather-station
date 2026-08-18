# Solar Weather Station

> An open-source, solar-powered ESP32-S3 weather station for local microclimate monitoring and engineering education.

[![Project status](https://img.shields.io/badge/status-v0.2%20teaching%20preview-198754)](#current-status)
[![Hardware](https://img.shields.io/badge/hardware-ESP32--S3-blue)](hardware/README.md)
[![Course](https://img.shields.io/badge/HKU-ENGG2202-7b2d8e)](teaching/ENGG2202-exemplar.md)
[![License](https://img.shields.io/badge/license-under%20review-lightgrey)](LICENSES/README.md)

**Learn from existing engineering → Rebuild → Adapt → Validate → Open-source → Teach forward.**

This repository is a real engineering project used as one live exemplar for [ENGG2202 - Green Technology](https://github.com/heqihao522828-crypto/ENGG2202-Green-Technology). The separate course repository explains the Green Technology journey, active-learning process and reusable student framework. This repository shows what that framework looks like when applied to one incomplete project.

It records not only the proposed solution, but also the green problem/baseline, alternatives considered, open-reference learning, design decisions, budget, materials, prototypes, failures, tests and reflections. Students may study and replace the method with their own Green Technology problem; they are not expected to copy this topic or solution.

> [中文 GitHub 导览：每个页面和文件为什么存在](docs/GITHUB-GUIDE-ZH.md)

> [Course–exemplar synchronisation record](teaching/COURSE-SYNC.md): when the project changes, check whether the ENGG2202 teaching example must change too—and vice versa.

<p align="center">
  <img src="tests/synthetic-v0.2/preview-summary.svg" width="900" alt="Synthetic v0.2 72-hour teaching-preview summary: 100 percent local records, 99.54 percent live remote receipt, zero simulated restarts and 3.87 volt modelled minimum battery. Not field evidence.">
</p>

> **Preview boundary:** the repository now shows a complete v0.2 engineering story, including generated data and a final decision. The sensor values, power profile, physical observations and field result are synthetic—not measurements or deployment approval.

## Why this project?

Regional weather data does not always represent the microclimate where an engineering decision is made. The instructor interview confirms the first use as a `go / conditional go / no-go` decision for a supervised 72-hour first field validation of a student environmental-monitoring prototype. A real TA interview has defined the workflow needs, while the supervised dry run, exact point near HKU's Tam Wing Fan Innovation Wing One, permission, reference access and thresholds still require validation.

## Intended capabilities

- Wind speed and wind direction
- Temperature, humidity, and pressure
- SHT45 temperature/humidity, BMP390 pressure and an experimental LTR390 UVA-count channel
- GNSS time and location
- Solar and battery operation
- Local data logging and a web dashboard
- RS-485 / Modbus connections for robust outdoor sensors

These are design targets, not claims that every subsystem has been validated.

## System architecture

```mermaid
flowchart LR
    S[Solar panel] --> P[Power manager]
    P --> B[Battery]
    B --> M[ESP32-S3 controller]
    W[Wind sensors] --> R[RS-485 / Modbus] --> M
    E[Environmental sensors] --> M
    G[GNSS] --> M
    M --> L[Local storage]
    M --> D[Dashboard / data export]
```

The diagram is deliberately high-level. Pin assignments, electrical interfaces, protocols, and verified limits belong in the subsystem documentation rather than being implied by this overview.

## Current status

| Area | Status | Evidence needed next |
|---|---|---|
| Problem and project foundation | [Original v0.1 PDF imported](docs/source-documents/Solar_Weather_Station_Project_Foundation_v0.1.pdf) | Maintain traceability as the living documents evolve |
| Solution landscape | [Gates A–E teaching journey complete](docs/project-journey/00-gates-a-e-overview.md); conditional hybrid reference-plus-educational-prototype direction selected | Treat real TA/site/reference/quotation evidence and prototype validation as future verification, never as completed by the simulations |
| Reference-project lineage | Exact project links and observed licences recorded | Lock immutable commits before any file reuse |
| ESP32-S3 architecture | [v0.2 interface map and synthetic firmware scaffold complete](docs/project-journey/prototype-v0.2-teaching-preview.md) | Replace design assignments with schematic, build/flash and bench evidence |
| Environmental sensor | [SHT45 + BMP390 + LTR390 selected](docs/project-journey/adr/ADR-004-environmental-sensor-set.md) | Verify exact breakouts, shield/optical path and reference comparison |
| Power subsystem | [Synthetic budget complete](docs/project-journey/power-budget-v0.2.md): 4.83 Wh/day and 5.5-day model | Instrument every mode, select exact battery/panel and run endurance test |
| Outdoor enclosure | [Three-zone v0.2 specification complete](mechanical/v0.2-enclosure-spec.md) | Add CAD/prints, assembly cycles, spray, heat/condensation and mounting evidence |
| 72-hour outdoor validation | [432-record synthetic preview complete](tests/synthetic-v0.2/report.md) | Obtain real site approval and replace generated data/observations with field evidence |

## Project journey

The engineering narrative is split into reviewable steps:

0. [One-page Gates A–E decision overview](docs/project-journey/00-gates-a-e-overview.md)
1. [Problem identification](docs/project-journey/01-problem.md)
2. [Existing-solution landscape](docs/project-journey/02-solution-landscape.md)
3. [Reference projects](docs/project-journey/03-reference-projects.md)
4. [Design requirements](docs/project-journey/04-design-requirements.md)
5. [Design decisions](docs/project-journey/05-design-decisions.md)
   - [Environmental sensor ADR](docs/project-journey/adr/ADR-004-environmental-sensor-set.md)
6. [Budget and procurement](docs/project-journey/06-budget.md)
   - [Synthetic power budget](docs/project-journey/power-budget-v0.2.md)
7. [Prototyping](docs/project-journey/07-prototyping.md)
   - [Integrated v0.2 teaching preview](docs/project-journey/prototype-v0.2-teaching-preview.md)
8. [Testing and validation](docs/project-journey/08-testing.md)
   - [Synthetic 72-hour report](tests/synthetic-v0.2/report.md)
9. [Reflection and teaching transfer](docs/project-journey/09-reflection.md)

## Repository map

| Folder/file | What it is for |
|---|---|
| `README.md` | The project’s front door: purpose, status, architecture, and navigation |
| `docs/project-journey/` | The traceable engineering process behind the final design |
| `hardware/` | Schematics, wiring, PCB, interfaces, and electrical evidence |
| `mechanical/` | CAD, drawings, enclosure, mounting, and fabrication guidance |
| `firmware/esp32s3/` | Embedded source code, configuration, and flashing instructions |
| `dashboard/` | Data model, visualisation, and deployment instructions |
| `bom/` | Bill of materials, suppliers, cost, and procurement status |
| `tests/` | Test plans, raw evidence, acceptance criteria, and results |
| `teaching/` | How this project maps to ENGG2202 learning and assessment |
| `.github/` | Contribution templates used by GitHub Issues and Pull Requests |

## Quick start

You can reproduce the evidence pipeline now even though the physical build is not verified:

```powershell
./tests/synthetic-v0.2/generate-preview.ps1
```

For the physical pathway:

1. Review the requirements and safety constraints.
2. Replace planning prices with quotations and approve the exact BOM revision.
3. Fabricate the enclosure and mounting parts.
4. Assemble and inspect the electrical system.
5. Configure and flash the firmware.
6. Run subsystem diagnostics.
7. Complete the validation matrix before field deployment.

Until those instructions and real tests are complete, treat this repository as a **work-in-progress teaching and engineering record**, not a finished consumer product or weather-data service.

## Budget framework

| Baseline | Current planning total | Evidence level |
|---|---:|---|
| v0.2 preview system | HKD 3,715 | synthetic planning costs; no approved purchase |

The [BOM](bom/bom.csv) exposes each assumed part and cost. Shipping, tax, failed parts, labour, tools and a purchased reference instrument are excluded; all values require current quotations.

## Project baselines

- [Solar Weather Station Project Foundation v0.1](docs/source-documents/Solar_Weather_Station_Project_Foundation_v0.1.pdf) - immutable 26-page engineering baseline dated 14 August 2026.
- [Foundation traceability record](docs/source-documents/FOUNDATION-TRACEABILITY.md) - maps source sections and claims into the living repository.
- The ENGG2202 course template is retained under `teaching/source-documents/` as an internal course-design reference. Review its distribution status before making this repository public.

## Contributing

Ideas, test results, sensor comparisons, documentation improvements, and design reviews are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md) and open an Issue before making a major design change.

## Licensing and attribution

The final licence has not yet been selected because third-party firmware and hardware-design lineage must be audited first. See [THIRD_PARTY.md](THIRD_PARTY.md) and [LICENSES/README.md](LICENSES/README.md). Do not copy external code or design files into this repository until their licence and attribution requirements are recorded.

## Safety

Outdoor electrical systems, rechargeable batteries, fabrication tools, and elevated mounting introduce real hazards. Risk assessment, supervision, weather protection, strain relief, fusing, and appropriate test procedures are required. This repository does not replace professional engineering judgement.

