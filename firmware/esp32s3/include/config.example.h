#pragma once

// Copy to config.h for a local build. Do not commit credentials or precise site data.
#define STATION_REVISION "HW-v0.2-preview"
#define FIRMWARE_REVISION "FW-v0.2-preview"
#define SAMPLE_INTERVAL_MS 600000UL

#define PIN_I2C_SDA 8
#define PIN_I2C_SCL 9
#define PIN_SD_CS 10
#define PIN_RS485_DE_RE 4
#define PIN_FIELD_POWER_ENABLE 5
#define PIN_RS485_TX 15
#define PIN_RS485_RX 16
#define PIN_GNSS_TX 17
#define PIN_GNSS_RX 18
#define PIN_BATTERY_ADC 1

// PREVIEW_SYNTHETIC is supplied by platformio.ini. Remove it only when real drivers,
// calibration and hardware evidence are ready.

