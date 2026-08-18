#include <Arduino.h>

#if __has_include("config.h")
#include "config.h"
#else
#include "config.example.h"
#endif

static uint32_t sample_index = 0;

static void emitSyntheticPreview() {
  const float phase = (sample_index % 144) / 144.0f * 2.0f * PI;
  const float temperature = 28.0f + 3.5f * sinf(phase - PI / 2.0f);
  const float humidity = 76.0f - 10.0f * sinf(phase - PI / 2.0f);
  const float pressure = 1008.0f + 1.2f * sinf(phase / 3.0f);

  Serial.printf(
      "{\"station_revision\":\"%s\",\"firmware_revision\":\"%s\","
      "\"evidence_level\":\"synthetic_preview\",\"sample_index\":%lu,"
      "\"temperature_c\":%.2f,\"relative_humidity_percent\":%.2f,"
      "\"pressure_hpa\":%.2f,\"sensor_status\":\"unverified\"}\n",
      STATION_REVISION, FIRMWARE_REVISION,
      static_cast<unsigned long>(sample_index), temperature, humidity, pressure);
  ++sample_index;
}

void setup() {
  pinMode(PIN_FIELD_POWER_ENABLE, OUTPUT);
  digitalWrite(PIN_FIELD_POWER_ENABLE, LOW);
  Serial.begin(115200);
  delay(500);
  Serial.println("Solar Weather Station v0.2 preview: synthetic output only");
}

void loop() {
#if PREVIEW_SYNTHETIC
  emitSyntheticPreview();
#else
#error "Real sensor mode is intentionally blocked until drivers and evidence are reviewed."
#endif
  delay(SAMPLE_INTERVAL_MS);
}

