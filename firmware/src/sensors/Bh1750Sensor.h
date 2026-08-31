#pragma once

#include "sensor_status.h"
#include "weather_data.h"

#include <BH1750.h>

class Bh1750Sensor
{
public:
    bool begin();
    bool read(WeatherData& data);
    SensorDiagnostic diagnostic() const;
    const char* lastError() const;

private:
    BH1750 sensor_;
    bool initialized_ = false;
    bool lastReadSuccess_ = false;
    uint32_t readCount_ = 0;
    uint32_t errorCount_ = 0;
    uint32_t consecutiveFailures_ = 0;
    uint32_t lastSuccessfulReadMs_ = 0;
    const char* lastError_ = "not initialized";
};
