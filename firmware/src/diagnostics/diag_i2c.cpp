#include <Arduino.h>
#include "app_config.h"
#include "core/I2CManager.h"

void setup()
{
    Serial.begin(AppConfig::SerialBaud);
    delay(800);
    Serial.println("DIAGNOSTIC FIRMWARE - I2C BUS AND ENVIRONMENTAL SENSOR ADDRESSES");
    Core::I2CManager::begin();
    Core::I2CManager::scanBus();
    Serial.println("Scan is startup-only. Reset the board to scan again.");
}

void loop() { delay(1000); }
