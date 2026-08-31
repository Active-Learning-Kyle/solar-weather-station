#include "Bh1750Sensor.h"

#include <Arduino.h>

#include <Wire.h>

bool Bh1750Sensor::begin()
{
    initialized_ = sensor_.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
    if (!initialized_)
    {
        initialized_ = sensor_.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5C, &Wire);
    }

    if (!initialized_)
    {
        lastError_ = "BH1750 not detected";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    lastError_ = "";
    return true;
}

bool Bh1750Sensor::read(WeatherData& data)
{
    ++readCount_;

    if (!initialized_)
    {
        lastReadSuccess_ = false;
        lastError_ = "BH1750 not initialized";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    const float lux = sensor_.readLightLevel();
    if (lux < 0.0f)
    {
        lastReadSuccess_ = false;
        lastError_ = "BH1750 read failed";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    data.lightLux = lux;
    lastReadSuccess_ = true;
    consecutiveFailures_ = 0;
    lastSuccessfulReadMs_ = millis();
    lastError_ = "";
    return true;
}

SensorDiagnostic Bh1750Sensor::diagnostic() const
{
    return {"BH1750", initialized_, lastReadSuccess_, readCount_, errorCount_, consecutiveFailures_, lastSuccessfulReadMs_, lastReadSuccess_, lastError_};
}

const char* Bh1750Sensor::lastError() const
{
    return lastError_;
}
