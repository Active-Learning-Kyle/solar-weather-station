# v0.2 Synthetic Integration and 72-hour Preview

> **EVERY VALUE IN THIS FOLDER IS SYNTHETIC.** The pack exists so students and the instructor can inspect a finished evidence chain before hardware is available. It is not site permission, a measurement, a calibration, an HKU observation or proof that v0.2 exists physically.

## Reproduce the preview

From PowerShell:

```powershell
./tests/synthetic-v0.2/generate-preview.ps1
```

The deterministic script creates:

- `synthetic-72h-data.csv` — 432 ten-minute records;
- `summary.json` — calculated completeness, battery and reference-difference metrics.

The human-observation layers are:

- [daily observations](daily-observations.csv);
- [post-retrieval inspection](post-retrieval.md); and
- [decision report](report.md).

## Story represented

After the earlier Gate D `revise` result, the fictional v0.2 scenario assumes a larger documented energy margin, the selected SHT45/BMP390/LTR390 set, local-first logging and condensation controls. The 72-hour preview then demonstrates how corrected evidence could support progression to a longer supervised comparison test.

## Replacement rule

Real data must live in a new dated folder and name actual hardware/firmware/CAD/BOM revisions, instruments, calibration state, site permission, operators, conditions and raw evidence. Do not relabel this synthetic CSV as measured.

