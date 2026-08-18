# 08 — Testing and Validation

Testing connects each requirement to evidence.

## Levels

1. Sensor/subsystem bench tests
2. Power and communications tests
3. Integrated station tests
4. Outdoor endurance and environmental tests
5. Data-quality comparison and independent reproduction

The [v0.2 synthetic 72-hour preview](../../tests/synthetic-v0.2/README.md) now demonstrates the complete data-generation, observation, retrieval, analysis and decision chain. It contains 432 generated records and a simulated `proceed to next supervised test` decision. The real outdoor test has **not** been completed; record firmware commit, hardware revision, approved location, actual conditions, sampling interval, missing data, resets, energy state and acceptance criteria before interpreting a real result.

See [`tests/test-matrix.csv`](../../tests/test-matrix.csv).

