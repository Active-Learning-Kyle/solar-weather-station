# Gate 05: Improve

Testing exists to support the next engineering decision, not to produce a successful-looking demonstration.

## What the current evidence supports

- the core environmental and particulate sensors operated together on the v0.1 bench prototype;
- the v0.2 local upload, validation, storage and dashboard path operated end to end;
- the installed GNSS interface and full v0.3 path were hardware verified;
- backend tests cover validation, null handling, database migration, GNSS, wind, legacy payloads and dashboard assets;
- all firmware environments can be compiled independently; and
- the wind-speed protocol was observed with the standalone diagnostic.

## What remains uncertain

- Core v0.4 has not completed the full combined hardware sequence;
- wind direction remains outside production;
- sensors have not been compared against a documented reference for accuracy claims;
- the enclosure has not passed ingress, thermal or radiation-shield testing;
- battery endurance and solar energy balance have not been measured; and
- no approved long-duration field record supports unattended operation.

## Next decision sequence

1. Run the complete v0.4 hardware procedure with all existing subsystems active.
2. Record Serial, API, database and dashboard evidence for normal, calm, disconnected and recovered wind states.
3. Update the [test matrix](../../tests/test-matrix.csv) with the commit, hardware revision and result.
4. If v0.4 passes, measure complete-system power before adding autonomous operation.
5. Complete enclosure and field-readiness checks before any supervised outdoor run.
6. Compare priority measurements with a documented reference and narrow any unsupported claim.

## Iteration rule

A failed test should change a driver, interface, mechanical feature, procedure or claim. Preserve the failed evidence and the reason for the next decision. Do not replace an unavailable value with zero or hide a known limitation in the dashboard.

## Gate decision

Hold feature expansion until combined v0.4 verification is complete. Rain, power telemetry and autonomous field operation remain separate future decisions.
