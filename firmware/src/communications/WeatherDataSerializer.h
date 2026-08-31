#pragma once

#include "weather_data.h"

#include <Arduino.h>

class WeatherDataSerializer
{
public:
    static String toJson(const WeatherData& data, uint32_t nowMs);
};
