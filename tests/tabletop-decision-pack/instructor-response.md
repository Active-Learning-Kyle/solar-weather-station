# Gate D Instructor Response

**Case:** [`SYNTH-D-01`](synthetic-72h-case.md)  
**Participant role:** instructor / deployment-decision owner  
**Evidence type:** human decision on fictional data; not prototype performance

## Decision

**`REVISE` — do not proceed outdoors with the configuration as-is.**

The overall architecture remains plausible because the fictional system runs for most of 72 hours, preserves local logging through a network interruption and automatically recovers after one reboot. There is no stated immediate safety failure that requires abandoning the architecture. However, the configuration has not met the current first-test purpose because power margin, measurement disagreement and condensation remain unresolved.

## Decision reasons

| Finding | Instructor interpretation | Required action before another field run |
|---|---|---|
| 1 h 35 min dashboard gap with local records retained | Primarily communication/observability evidence, not automatically sensor/system data loss | distinguish network, upload and local-log states in the report/dashboard; verify recovery/backfill |
| Low-battery warning and one reboot | Power margin or recovery behaviour is insufficiently understood | inspect battery sizing, measured load and solar charging; isolate reboot cause; repeat power/recovery bench test |
| Persistent temperature/reference difference beyond the fictional accuracy band | Priority measurement cannot support the intended accuracy claim | verify reference metadata/method; calibrate or replace the sensor; repeat comparison |
| Light internal condensation | No immediate wet-electronics event, but enclosure reliability is not resolved | review ventilation, sealing, thermal path and condensation control; repeat controlled enclosure test |
| Mounting/connectors/cables stable | No evidence of a physical-system rejection in this case | retain the architecture while preserving the same checks |

## Required sequence

1. investigate and modify the affected subsystems;
2. run targeted bench power, recovery, sensor-comparison and enclosure tests;
3. update thresholds/dashboard/checklist where the evidence was ambiguous; and
4. request a new supervised field decision only after the bench evidence is reviewed.

## What would change the decision?

- **Toward `proceed`:** adequate measured power margin, explained recovery, acceptable/characterised sensor comparison and controlled condensation result.
- **Toward `return to bench`:** repeated unexplained reboot, unstable/random sensing, worsening ingress/condensation or a newly identified safety hazard.
- **Toward `reference only`:** stable and educational operation but measurement performance that remains unsuitable for the intended data use.
