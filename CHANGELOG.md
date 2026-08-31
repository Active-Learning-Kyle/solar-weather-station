# Changelog

This file records project releases and milestone-level changes. Detailed evidence remains in [`docs/milestones/`](docs/milestones/).

## Unreleased

- Migrated the verified Core v0.4 hardware, firmware, backend, CAD and evidence into the independent public-project history.
- Rebuilt the README around the project motivation, SDG direction, real prototype, live dashboard, internal electronics, editable CAD and reproduction path.
- Added transparent provenance notes for project photographs, generated explanatory visualisations and SDG communication assets.
- Added the six-Gate project journey, system test matrix and field-readiness record.
- Added continuous integration for the backend and all firmware environments.
- Added public contribution, security, AI-use, third-party dependency and release guidance.
- Added the MIT License and reorganised the README as the repository front door.

## Core v0.4

- Integrated verified RS485 wind speed into the production firmware, JSON payload, API, SQLite storage, dashboard and history charts.
- Preserved valid calm readings as `0.0 m/s` and timeouts as unavailable.
- Kept wind direction as a separate diagnostic.
- Retained backward compatibility with v0.3 payloads and databases.
- Added editable mechanical CAD, print preparation and assembly documentation for the Weather Station Body, Power Module and Connecting Base.

## Core v0.3

- Integrated TEL0157/L76K GNSS communication, fix state, UTC, position, altitude, satellites and motion.
- Added independent GNSS diagnostics and a documented NMEA hemisphere workaround.
- Added nullable GNSS API and database fields while preserving earlier records.
- Added privacy-safe public evidence.

## Core v0.2

- Added non-blocking Wi-Fi reconnects and periodic HTTP uploads.
- Added FastAPI validation, SQLite storage and latest/history endpoints.
- Added the responsive local dashboard and backend automated tests.

## Core v0.1

- Integrated SHT4x, BMP180, BH1750, LTR390 and PMS7003 sensing.
- Added shared measurement snapshots, explicit sensor health, validation, staleness and failure counters.
- Added isolated I²C and PMS7003 diagnostics.
