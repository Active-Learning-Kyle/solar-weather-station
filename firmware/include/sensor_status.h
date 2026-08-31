#pragma once

#include <stdint.h>

struct SensorDiagnostic
{
    const char* name;
    bool initialized;
    bool lastReadSuccess;
    uint32_t readCount;
    uint32_t errorCount;
    uint32_t consecutiveFailures;
    uint32_t lastSuccessfulReadMs;
    bool latestValueValid;
    const char* lastError;
};

struct SensorHealth
{
    bool initialized = false;
    bool latestValueValid = false;
    bool stale = true;
    uint32_t lastSuccessfulReadMs = 0;
    uint32_t consecutiveFailures = 0;
    uint32_t totalFailures = 0;
};
