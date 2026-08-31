#include "Ltr390Sensor.h"

#include <Arduino.h>

namespace
{
constexpr float UvIndexScale = 2300.0f;
}

bool Ltr390Sensor::begin()
{
    initialized_ = sensor_.begin();
    if (!initialized_)
    {
        lastError_ = "LTR390 not detected";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    sensor_.setMode(LTR390_MODE_UVS);
    sensor_.setGain(LTR390_GAIN_3);
    sensor_.setResolution(LTR390_RESOLUTION_18BIT);

    lastError_ = "";
    return true;
}

bool Ltr390Sensor::read(WeatherData& data)
{
    ++readCount_;

    if (!initialized_)
    {
        lastReadSuccess_ = false;
        lastError_ = "LTR390 not initialized";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    if (!sensor_.newDataAvailable())
    {
        lastReadSuccess_ = false;
        lastError_ = "LTR390 data not ready";
        ++errorCount_;
        ++consecutiveFailures_;
        return false;
    }

    const uint32_t uvRaw = sensor_.readUVS();
    data.uvRaw = uvRaw;
    data.uvIndex = static_cast<float>(uvRaw) / UvIndexScale;
    lastReadSuccess_ = true;
    consecutiveFailures_ = 0;
    lastSuccessfulReadMs_ = millis();
    lastError_ = "";
    return true;
}

SensorDiagnostic Ltr390Sensor::diagnostic() const
{
    return {"LTR390", initialized_, lastReadSuccess_, readCount_, errorCount_, consecutiveFailures_, lastSuccessfulReadMs_, lastReadSuccess_, lastError_};
}

const char* Ltr390Sensor::lastError() const
{
    return lastError_;
}
