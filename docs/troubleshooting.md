# Troubleshooting

Use the smallest diagnostic that can prove the failing layer. Preserve logs, exact board/sensor revisions, wiring changes, and whether the result was compiled, bench tested, or field tested.

## First checks

1. Confirm the selected PlatformIO environment and Serial monitor speed (115200).
2. Confirm the board matches the ESP32-S3 pin allocation.
3. Check supply voltage and ground before signal wiring; never apply 5 V logic to an ESP32 GPIO.
4. Test one bus/interface with its diagnostic before modifying production firmware.
5. Return to `weather_station` only after the isolated test passes.

## I²C sensor not detected

From `firmware/`:

```powershell
pio run -e diag_i2c -t upload
pio device monitor -b 115200
```

Expected addresses are SHT4x `0x44`, BMP180 `0x77`, BH1750 `0x23` or `0x5C`, and LTR390 `0x53`.

- Verify the breakout's permitted VCC, then check VCC and GND at the module.
- Check continuity and orientation for SDA GPIO8 and SCL GPIO9.
- Inspect connectors, solder joints, and accidental bridges.
- Check that pull-ups go to 3.3 V and that the bus is not excessively long.
- If an unexpected address appears, verify the module marking and address-select state.
- Do not rewrite a sensor driver until the expected address is present on the bus.

The diagnostic scans once at startup; reset the board after a wiring change.

## I²C address passes but readings fail

- Run the integrated firmware and inspect that sensor's health counters and last error.
- Confirm the detected module matches the driver (not merely the same-looking breakout).
- Check supply stability during Wi-Fi current peaks.
- Test with shorter wiring and one sensor at a time if bus integrity is uncertain.
- For LTR390, distinguish successful raw UV reads from calibrated UV-index accuracy; the current UV index is an estimate.

## PMS7003 not reporting

```powershell
pio run -e diag_pms -t upload
pio device monitor -b 115200
```

- Confirm sensor TX connects to ESP32 RX GPIO16 and sensor RX to ESP32 TX GPIO17.
- Confirm a common ground, the sensor's required supply, UART at 9600 baud, and SET GPIO18 state.
- Inspect `Frames received`, `Checksum errors`, `Read failures`, and `Last valid frame age`.
- A valid parser result requires Plantower headers `0x42 0x4D`, the expected frame length, and a matching checksum.
- Repeated checksum failures suggest signal/wiring/framing issues; no bytes suggests power, TX/RX, or sleep-state issues.

## ESP32 cannot join Wi-Fi

- Confirm `firmware/include/secrets.h` exists and uses the macros from `secrets.example.h`.
- Re-enter the SSID/password locally; never paste credentials into an issue or commit them.
- Watch `CONNECTING`, `RETRY_WAIT`, and `CONNECTED` transitions. A failed attempt times out after 15 seconds and waits 30 seconds before retrying.
- Confirm the network is supported by the board and permits the device to join.
- Sensor reads should continue; a Wi-Fi fault is not expected to reboot or stop acquisition.

## Wi-Fi connects but the backend is unreachable

- Set `BACKEND_HOST` to the backend computer's LAN IP. Do not use `localhost` or `127.0.0.1` in ESP32 firmware.
- Start Uvicorn with `--host 0.0.0.0 --port 8000`, not a loopback-only binding.
- On another device, try `http://<BACKEND_HOST>:8000/docs` to test reachability.
- Permit inbound TCP port 8000 in the backend computer's firewall for the trusted network profile.
- Confirm the ESP32 and backend are on mutually reachable network segments.
- Institutional, guest, and some mesh Wi-Fi networks use client isolation. For development, a home router or personal hotspot that permits device-to-device traffic may be simpler.
- Do not expose the v0.3 service directly to the public internet; it has no TLS or authentication and can store precise location.

## HTTP uploads fail

- Read the Serial response code. Code `0`/negative values generally indicate no HTTP response; 4xx indicates request/schema issues; 5xx indicates backend failure.
- Open FastAPI docs at `/docs` and confirm the backend is running.
- Verify `BACKEND_PORT` and `BACKEND_ENDPOINT` match the backend.
- Check that the payload uses `weather.measurement.v1` and that unavailable sensor values are JSON `null`.
- Remember that v0.3 retains the v0.2 one-element upload queue: after recovery, new snapshots resume, but outage-period observations are not replayed.

## Dashboard has no data or shows STALE/CHECK

- Query `/api/v1/measurements/latest?station=<station-id>` directly.
- Confirm the station field in the dashboard matches uploaded `station_id` exactly.
- A 404 means no row exists for that station. A stale state means the latest stored server timestamp is old.
- `CHECK`/unavailable values can be a valid display of sensor health, not a dashboard rendering fault.
- For trends, confirm history exists inside the selected 1-hour, 24-hour, or 7-day window.

## Backend setup or test failure

The verified interpreter is Python 3.11:

```powershell
cd backend
py -3.11 -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\.venv\Scripts\python.exe -m pytest -q
```

v0.3 performs a narrow additive migration for missing GNSS columns. It does not provide a general migration framework. Use a separate disposable path for tests or manually archive the local development database; do not delete a valued database without a backup.

## GNSS has no UART data

First isolate the receiver:

```powershell
pio run -e diag_gnss -t upload
pio device monitor -b 115200
```

- Remove power before checking that the TEL0157 selector is in UART mode.
- Verify the supported supply and common ground; this project uses 3V3.
- Confirm TEL0157 TX (`D/T`) connects to ESP32 RX GPIO15 and TEL0157 RX (`C/R`) connects to ESP32 TX GPIO14.
- Confirm UART1 at 9600 baud and inspect connector/antenna seating.
- Do not modify the production GNSS worker or parser until independent UART communication is established.

## GNSS receives NMEA but has no fix

- Confirm the active antenna is firmly attached and correctly oriented.
- Test outdoors or with a genuinely clear sky view; windows and indoor locations can prevent or delay acquisition.
- Allow several minutes for a cold start and avoid repeatedly resetting a communicating receiver.
- Inspect valid-sentence and checksum-failure counters. Counts vary by run; sustained failures merit wiring/signal investigation.
- `COMMUNICATION OK - NO FIX` is distinct from `NOT CONNECTED` and should not stop other station data.

## GNSS latitude/longitude is invalid or unavailable

- Confirm a current `FIX VALID` state, at least one satellite used, and valid UTC/date.
- Check that latitude/longitude magnitude tests pass and checksum-valid NMEA supplies both hemisphere fields.
- `FIX STALE`, `COMMUNICATION OK - NO FIX`, and `NOT CONNECTED` intentionally serialize current position as `null`.
- Do not treat zero as the missing-data marker; explicit flags and nulls preserve a real zero coordinate.

## `diag_gnss` works but the main station does not

- Confirm `EnableGnss = true` in `firmware/include/app_config.h`.
- Confirm production uses UART1 GPIO15/14 and that no new component conflicts with it.
- Verify `GPSManager::begin()` runs and Serial reports the GNSS worker start.
- Inspect the structured Serial GNSS state before debugging HTTP.
- Confirm the JSON payload contains `gnss`, then check FastAPI validation and the additive SQLite columns.
- Query the latest endpoint before debugging dashboard rendering.
- Reflash `weather_station` after diagnostics; a diagnostic is a separate firmware image.

## GNSS privacy before publishing evidence

- Treat screenshots, Serial logs, API responses, SQLite exports, and issues as potential precise-location disclosures.
- Use an opaque irreversible cover and a coarse range for public screenshots; do not rely on blur or decimal truncation.
- Remove personal filesystem paths, Wi-Fi details, and backend addresses from captures.
- Keep original coordinate-bearing evidence outside the public repository.

## Diagnostic environment does not build

- Run the command from `firmware/`, where `platformio.ini` is located.
- Confirm dependencies can be installed and that only the intended environment is selected.
- Do not compile a diagnostic source alongside `main.cpp`; the existing `build_src_filter` handles this.
- When reporting a failure, include `pio run -e <environment>` output, PlatformIO version, board revision, and whether the failure is compile-, upload-, or runtime-related.

## Return to the current firmware

Diagnostics replace the application on the device. After testing, explicitly restore the current Core v0.4 firmware:

```powershell
pio run -e weather_station -t upload
pio device monitor -b 115200
```
