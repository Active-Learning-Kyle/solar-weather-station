# 05 - Design Decisions

Use an Architecture Decision Record (ADR) whenever a choice has meaningful alternatives or consequences.

## ADR template

- **Decision ID and date:**
- **Context/problem:**
- **Options considered:**
- **Decision:**
- **Evidence and trade-offs:**
- **Cost/safety/licensing consequences:**
- **How the decision will be tested:**
- **When it should be revisited:**

## Migrated decision status from Project Foundation v0.1

| Topic | Current status | Evidence level | Next decision/evidence |
|---|---|---|---|
| ESP32-S3 main controller | Preferred/confirmed direction | Source-document decision | Lock exact board SKU, pin map and measured board-level sleep current |
| RS-485/Modbus wind instruments | Preferred/confirmed direction | Wind-direction decoding is reported in project history | Commit exact sensor models, raw frames, registers, IDs and T-010/T-011/T-012 evidence |
| MAX485 | Used during diagnostics only | Source-document history | Select native 3.3 V or isolated/protected interface; document level, bias, termination and surge assumptions |
| DFRobot TEL0157 GNSS | Communication reported successful | Source-document history | Prove outdoor fix and define power-on/acquisition policy |
| Environmental sensor | Not selected | Open decision | Compare exact parts, radiation shielding, calibration, supply, interface, availability and cost in Issue #4 |
| UV sensing | Not selected; SI1145 legacy, GUVA-S12SD or modern digital option considered | Open decision | Select optical path and calibration method; do not place behind unverified plastic |
| Solar Power Manager (D) | Planned power architecture | Source-document decision | Document wiring/protection and measure complete system before sizing battery/panel |
| Battery/solar sizing | Not selected | Open decision | Base on PWR-002 measurements and PWR-003 autonomy target |
| Local-first data record | Recommended | Architectural recommendation | Lock schema before dashboard implementation |
| LoRa sender/receiver | Optional, not core v0.2 | Scope decision | Revisit only if the stakeholder/use case requires remote no-Wi-Fi transport |
| Triangular/louvered enclosure with separate power zone | In development | Source-document concept | Commit CAD and test thermal bias, serviceability, ingress paths and 20 assembly cycles |

The repository must distinguish `documented design direction`, `reported project-history result`, and `validated repository evidence`. Only the last category should be presented as verified.
