# Data Schema v0.2

Each record is local-first and carries evidence/diagnostic metadata. The preview CSV implements the same logical fields.

| Field | Type / unit | Meaning |
|---|---|---|
| `timestamp_iso8601` | string | timezone-qualified sample timestamp |
| `station_revision` | string | hardware/mechanical configuration |
| `firmware_revision` | string | source baseline |
| `evidence_level` | enum | `synthetic_preview`, `bench_measured`, `field_observed`, `reference_derived` |
| `temperature_c` | °C | SHT45 channel |
| `relative_humidity_percent` | %RH | SHT45 channel |
| `pressure_hpa` | hPa | BMP390 channel |
| `uva_counts` | raw counts | LTR390 UVA response; not automatically UV Index |
| `wind_speed_mps` | m/s | Modbus wind-speed value |
| `wind_direction_deg` | degrees | Modbus vane heading |
| `battery_v` | V | calibrated battery sense when real |
| `solar_input_w` | W | optional measured/estimated input with method metadata |
| `gnss_fix` | boolean | valid fix state separate from module communication |
| `local_logged` | boolean | record committed to local storage |
| `remote_received` | boolean | remote copy received during original interval |
| `backfilled` | boolean | remote record later recovered from local storage |
| `restart_count` | integer | cumulative boot/restart count |
| `sensor_status` | enum | `ok`, `stale`, `range`, `comm_error`, `unverified` |

## Quality-display rules

- Never draw a continuous line across missing intervals without a visible gap/backfill marker.
- Display local logging and remote receipt separately.
- Show revision and evidence level near every export/dashboard view.
- Preserve raw values; derived/calibrated values need method, coefficients and reference metadata.
- Exact deployment coordinates and access/security information belong outside public exports.

