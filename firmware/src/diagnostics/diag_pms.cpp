#include <Arduino.h>
#include "app_config.h"
#include "sensors/PMS7003Sensor.h"

namespace { PMS7003Sensor sensor; WeatherData data = {}; uint32_t lastReadMs = 0; }

void setup()
{
    Serial.begin(AppConfig::SerialBaud);
    delay(800);
    Serial.println("DIAGNOSTIC FIRMWARE - PMS7003");
    sensor.begin();
}

void loop()
{
    const uint32_t nowMs = millis();
    if (lastReadMs == 0 || nowMs - lastReadMs >= AppConfig::PmsPeriodMs)
    {
        lastReadMs = nowMs;
        if (sensor.read(data, AppConfig::PmsReadTimeoutMs))
        {
            Serial.print("PM1.0/PM2.5/PM10 atmospheric: ");
            Serial.print(data.pm1_0); Serial.print(" / ");
            Serial.print(data.pm2_5); Serial.print(" / ");
            Serial.print(data.pm10); Serial.println(" ug/m3");
        }
        else Serial.println("PMS7003 frame unavailable");
        sensor.printStatus();
    }
    delay(5);
}
