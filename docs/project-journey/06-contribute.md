# Gate 06: Contribute

The project is useful to another person only when they can understand what exists, reproduce the supported parts and see the limits before extending it.

## What this release provides

- ESP32-S3 production firmware and isolated diagnostics;
- a typed FastAPI service, SQLite storage and browser dashboard;
- automated backend tests and firmware build checks;
- pin allocation, wiring, BOM and power notes;
- editable Fusion 360 source and mechanical assembly guidance;
- chronological milestone records and privacy-reviewed evidence;
- a system test matrix and field-readiness checklist;
- contribution, security, AI-use and third-party dependency guidance; and
- an MIT licence for original project content.

## Responsible release checks

Before publishing a new release:

1. verify the release commit builds and automated tests pass;
2. state which hardware procedure was run and what was observed;
3. update the status table, test matrix and affected milestone record;
4. remove credentials, private endpoints and precise location data;
5. review images, logs and databases for personal or site-sensitive information;
6. confirm third-party attribution and licence obligations;
7. distinguish planned, compiled, bench-verified and field-verified claims; and
8. list known limitations and the next evidence needed.

The complete maintainer checklist is in [`docs/release-checklist.md`](../release-checklist.md).

## How others can build on the work

Start with the README route that matches the intended task. Use a diagnostic before changing an integrated driver. Open an Issue before changing pins, schemas or milestone scope. Submit one focused Pull Request with the exact test and evidence boundary.

Teaching, demonstration and documentation may help another person use the work. The durable contribution is the repository itself: source, editable design files, evidence, decisions, licence and honest limits.
