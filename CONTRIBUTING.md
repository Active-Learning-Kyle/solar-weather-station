# Contributing

This repository is an experimental hardware/software project moving toward a reproducible public release. Contributions are welcome, but evidence and honest status labels are more important than feature count.

## Before making a change

- Read the [README](README.md), the relevant [milestone record](docs/milestones/), and [Troubleshooting](docs/troubleshooting.md).
- Keep credentials and local network details out of commits. Create `firmware/include/secrets.h` from the tracked example; never edit the example with real values.
- Confirm whether your work affects the production `weather_station` environment, an isolated diagnostic, the backend, or documentation only.
- Open an issue or discussion before changing pin allocations, payload/schema fields, stored database columns, or milestone scope; these changes affect hardware and reproducibility.

## Evidence labels

Use these terms consistently:

| Label | Meaning |
| --- | --- |
| **Planned** | No implementation is claimed |
| **Software implemented** | Code exists; state whether it compiled or has automated tests |
| **Diagnostic available** | An isolated test exists; main integration is not implied |
| **Hardware verified** | Observed on named physical hardware with a described procedure |
| **Complete** | The documented acceptance result for that milestone was observed |

Compilation is not hardware verification, and a diagnostic passing is not production integration. Do not describe GNSS, wind, rain, power telemetry, prediction, or field operation as complete unless a later milestone supplies the evidence.

## Development checks

Build the current firmware and any diagnostic you changed from `firmware/`:

```powershell
pio run -e weather_station
pio run -e diag_i2c
```

Run backend tests with the verified Python version:

```powershell
cd backend
py -3.11 -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\.venv\Scripts\python.exe -m pytest -q
```

Hardware-related contributions should record:

- exact ESP32 board and sensor/module revision;
- power voltage and relevant wiring/pins;
- PlatformIO environment and firmware commit;
- steps performed and observed Serial/API output;
- whether the test was bench, enclosure, or outdoor/field work;
- failures and unresolved uncertainty, including calibration limits.

## Documentation and milestone records

- Use repository-relative links and meaningful image alt text.
- Do not commit personal paths, SSIDs, passwords, public IPs, or unredacted location data.
- Store milestone evidence under `docs/images/vX.Y/` and explain what each image proves—and what it does not.
- Use [the milestone template](docs/milestones/template.md) for v0.4 onward.
- Preserve diagnostic knowledge and failure investigations; do not delete them just because the final integration works.
- Update the README status table when a milestone status genuinely changes, but keep detailed procedures in the milestone document.

## Scope and safety

- Avoid unrelated firmware/backend changes in a documentation pull request.
- Outdoor power, lithium cells, charging, and 12 V subsystems require appropriate protection, fusing, enclosure, and qualified review. Existing power notes are preliminary.
- v0.3 HTTP has no TLS or authentication and can contain precise GNSS location. Do not expose it to the public internet.
- Redact coordinate-bearing screenshots with an opaque cover and coarse range; remove personal paths and keep originals outside public Git history.

## Licence and AI-assisted work

By contributing, you agree that your contribution can be released under the repository's [MIT License](LICENSE). Do not submit third-party material unless its licence and attribution are recorded in [THIRD_PARTY.md](THIRD_PARTY.md).

Read [AI_USE.md](AI_USE.md) before submitting AI-assisted code or documentation. Record material assistance, human checks and test evidence in the Pull Request. The contributor remains responsible for the result.
