#pragma once

#include "sensor_status.h"
#include "weather_data.h"

#include <Adafruit_SHT4x.h>

class Sht40Sensor
{
public:
    bool begin();
    bool read(WeatherData& data);
    SensorDiagnostic diagnostic() const;
    const char* lastError() const;

private:
    Adafruit_SHT4x sensor_;
    bool initialized_ = false;
    bool lastReadSuccess_ = false;
    uint32_t readCount_ = 0;
    uint32_t errorCount_ = 0;
    uint32_t consecutiveFailures_ = 0;
    uint32_t lastSuccessfulReadMs_ = 0;
    const char* lastError_ = "not initialized";
};

