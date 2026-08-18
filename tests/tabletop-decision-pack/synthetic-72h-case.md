# SYNTHETIC 72-Hour Tabletop Case — NOT TEST EVIDENCE

> **FICTIONAL DATASET FOR GATE D.** Configuration, values, events and observations below were created for ENGG2202 decision practice. No physical weather station produced these data.

## Decision prompt

Select one action based only on the evidence below:

- `proceed`;
- `revise`;
- `return to bench`; or
- `reference only`.

State the safety level, whether the same configuration may return outdoors, who has authority for the next step, evidence used and information still missing.

## Fictional configuration

- **Configuration ID:** `SYNTH-D-01`
- **Run:** 72 hours at a controlled semi-open candidate site
- **Logging:** 5-minute local records plus a remote dashboard
- **Reference:** fictional handheld/reference channel with a declared temperature accuracy band
- **Power:** fictional solar panel, protected battery and low-battery warning
- **Claim boundary:** supervised first field validation only—not meteorological, seasonal or unattended reliability

## Observation summary

| Evidence area | Synthetic observation |
|---|---|
| Normal operation | Most sensor records, timestamps, local logging and remote data are continuous and plausible. Mounting, connectors and cables remain secure. |
| Missing interval | The remote dashboard has a 1 h 35 min gap. The local logger remains active and the buffered records become available after communication recovers. |
| Battery/reboot | During the second night, the battery reaches the fictional warning region and the controller reboots once. Logging resumes automatically after 3 minutes; the cause is not yet isolated. |
| Sensor/reference disagreement | One priority temperature channel remains approximately `+1.6 °C` above the fictional reference across repeated comparisons, beyond the fictional declared accuracy band. The difference is persistent rather than a single outlier. |
| Enclosure | No visible liquid water reaches electronics. On retrieval, light condensation is observed on an internal wall away from live parts. |
| Physical condition | No loose mounting, cable damage, connector movement, abnormal heat, smell, swelling or public-contact incident is observed. |

## Key-event timeline

| Elapsed time | Synthetic event | Automatic/manual outcome |
|---:|---|---|
| 0–18 h | Normal daylight and first-night operation | Continue; no safety observation |
| 18 h 20 min | Remote communication becomes unavailable | Local timestamps/logging continue |
| 19 h 55 min | Remote communication recovers | Buffered records become available; investigate network path |
| 42 h 10 min | Low-battery warning | Preserve power and system logs |
| 42 h 12 min | Single controller reboot | Automatic restart; logging resumes after 3 min |
| 48–70 h | Repeated reference spot comparisons show persistent temperature bias | Bias remains beyond fictional accuracy band |
| 72 h retrieval | Light internal-wall condensation; no liquid water/electrical damage | Record and inspect enclosure design |

## Evidence deliberately missing

- measured solar input and full energy balance;
- confirmed root cause of the reboot;
- locked battery margin/stop threshold;
- reference instrument model, calibration traceability and uncertainty;
- replicated sensor comparison after calibration or replacement;
- condensation mechanism and repeat enclosure test; and
- an independent decision from the TA.

## Safety boundary for the exercise

The case contains **no stated immediate safety stop** such as battery distress, wet live electronics, unstable mounting, smoke, abnormal heat or uncontrolled public risk. It also does not demonstrate that the configuration is ready to return outdoors unchanged.
