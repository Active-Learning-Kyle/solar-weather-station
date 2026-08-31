#include "Bmp180Sensor.h"

#include <Arduino.h>

bool Bmp180Sensor::begin()
{
    initialized_ = sensor_.begin();
    if (!initialized_)
    {
        lastError_ = "BMP180 not detected";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    lastError_ = "";
    return true;
}

bool Bmp180Sensor::read(WeatherData& data)
{
    ++readCount_;

    if (!initialized_)
    {
        lastReadSuccess_ = false;
        lastError_ = "BMP180 not initialized";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    data.pressureSensorTemperature = sensor_.readTemperature();
    data.pressurePa = sensor_.readPressure();
    data.pressure = data.pressurePa / 100.0f;

    if (data.pressurePa <= 0)
    {
        lastReadSuccess_ = false;
        lastError_ = "BMP180 read failed";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    lastReadSuccess_ = true;
    consecutiveFailures_ = 0;
    lastSuccessfulReadMs_ = millis();
    lastError_ = "";
    return true;
}

SensorDiagnostic Bmp180Sensor::diagnostic() const
{
    return {"BMP180", initialized_, lastReadSuccess_, readCount_, errorCount_, consecutiveFailures_, lastSuccessfulReadMs_, lastReadSuccess_, lastError_};
}

const char* Bmp180Sensor::lastError() const
{
    return lastError_;
}

