# ESP32-S3 Firmware — v0.2 Preview Scaffold

The PlatformIO project currently compiles only a **synthetic serial-data scaffold** for `ESP32-S3-DevKitC-1`. Real sensor mode is deliberately blocked until drivers, wiring, calibration and hardware evidence are reviewed.

## Preview build

1. Install PlatformIO Core or the VS Code PlatformIO extension.
2. Copy `include/config.example.h` to `include/config.h` only if local changes are needed.
3. Run `pio run` from this folder.
4. Flash with `pio run -t upload` and inspect at 115200 baud.

The preview emits revisioned JSON with `evidence_level=synthetic_preview`; it cannot be mistaken for a sensor reading.

## Before real mode is allowed

- add pinned, licence-reviewed SHT45/BMP390/LTR390/GNSS/Modbus drivers;
- implement local-first append, atomic recovery, watchdog/reset-reason and backfill;
- verify the [pin map](../../hardware/v0.2-interface-map.md) on the exact board;
- add configuration validation and secret injection outside Git;
- pass clean build/flash, bus, power-interruption and data-schema tests; and
- remove the compile-time block only in a reviewed Pull Request linked to evidence.

Never commit Wi-Fi credentials, API keys, device secrets, personal location data or precise restricted-site details.

