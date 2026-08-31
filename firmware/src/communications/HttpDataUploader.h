#pragma once

#include "weather_data.h"

#include <Arduino.h>

struct UploadStatus
{
    uint32_t successfulUploads;
    uint32_t failedUploads;
    uint32_t consecutiveFailures;
    uint32_t lastSuccessfulUploadMs;
    int lastHttpResponseCode;
};

class HttpDataUploader
{
public:
    static void begin();
    static bool enqueue(const WeatherData& data);
    static UploadStatus status();

private:
    static void task(void* parameter);
    static void recordResult(bool success, int responseCode);
};
