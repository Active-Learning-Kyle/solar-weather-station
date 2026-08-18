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
| Environmental sensor | SHT45 temperature/RH plus BMP390 pressure selected for v0.2 preview | [ADR-004](adr/ADR-004-environmental-sensor-set.md) and official specifications | Verify breakouts, radiation shield and real reference comparison |
| UV sensing | LTR390 UVA-count channel selected for v0.2 preview | ADR-004; calibrated UV Index explicitly excluded | Verify optical path and controlled/reference response |
| Solar Power Manager (D) | Planned power architecture | Source-document decision | Document wiring/protection and measure complete system before sizing battery/panel |
| Battery/solar sizing | 10 Ah battery class and 10 W panel class selected for the preview | [Synthetic budget](power-budget-v0.2.md); not measured | Replace load profile and site assumptions before purchase/claim |
| Local-first data record | v0.2 schema locked for preview | [Schema and synthetic dataset](../../dashboard/data-schema-v0.2.md) | Implement atomic storage/backfill and fault injection on hardware |
| LoRa sender/receiver | Optional, not core v0.2 | Scope decision | Revisit only if the stakeholder/use case requires remote no-Wi-Fi transport |
| Triangular/louvered enclosure with separate power zone | In development | Source-document concept | Commit CAD and test thermal bias, serviceability, ingress paths and 20 assembly cycles |

The repository must distinguish `documented design direction`, `reported project-history result`, and `validated repository evidence`. Only the last category should be presented as verified.

