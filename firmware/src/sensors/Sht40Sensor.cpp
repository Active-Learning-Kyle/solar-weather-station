#include "Sht40Sensor.h"

#include <Arduino.h>

bool Sht40Sensor::begin()
{
    initialized_ = sensor_.begin();
    if (!initialized_)
    {
        lastError_ = "SHT4x not detected";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    sensor_.setPrecision(SHT4X_HIGH_PRECISION);
    sensor_.setHeater(SHT4X_NO_HEATER);
    lastError_ = "";
    return true;
}

bool Sht40Sensor::read(WeatherData& data)
{
    ++readCount_;

    if (!initialized_)
    {
        lastReadSuccess_ = false;
        lastError_ = "SHT4x not initialized";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    sensors_event_t humidity;
    sensors_event_t temperature;
    if (!sensor_.getEvent(&humidity, &temperature))
    {
        lastReadSuccess_ = false;
        lastError_ = "SHT4x read failed";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    data.temperature = temperature.temperature;
    data.humidity = humidity.relative_humidity;
    lastReadSuccess_ = true;
    consecutiveFailures_ = 0;
    lastSuccessfulReadMs_ = millis();
    lastError_ = "";
    return true;
}

SensorDiagnostic Sht40Sensor::diagnostic() const
{
    return {"SHT4x", initialized_, lastReadSuccess_, readCount_, errorCount_, consecutiveFailures_, lastSuccessfulReadMs_, lastReadSuccess_, lastError_};
}

const char* Sht40Sensor::lastError() const
{
    return lastError_;
}

