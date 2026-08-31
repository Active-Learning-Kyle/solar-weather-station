#pragma once

#include "weather_data.h"
#include "app_config.h"

#include <Arduino.h>

struct PMS7003Diagnostic
{
    bool initialized;
    uint32_t framesReceived;
    uint32_t checksumErrors;
    uint32_t readFailures;
    uint32_t consecutiveFailures;
    uint32_t lastValidFrameMs;
    bool latestValueValid;
    bool awake;
    const char* lastError;
};

class PMS7003Sensor
{
public:
    void begin();
    bool read(WeatherData& data, uint32_t timeoutMs = 3000);
    void wake();
    void sleep();
    void printStatus() const;
    PMS7003Diagnostic diagnostic() const;

private:
    static constexpr size_t FrameSize = 32;

    bool readFrame(uint8_t* frame, uint32_t timeoutMs);
    bool validateFrame(const uint8_t* frame);
    uint16_t readUint16(const uint8_t* frame, size_t index) const;
    void flushInput();

    HardwareSerial pmsSerial_{AppConfig::Uart::PmsPort};
    bool initialized_ = false;
    bool awake_ = false;
    uint32_t framesReceived_ = 0;
    uint32_t checksumErrors_ = 0;
    uint32_t readFailures_ = 0;
    uint32_t consecutiveFailures_ = 0;
    uint32_t lastValidFrameMs_ = 0;
    bool latestValueValid_ = false;
    const char* lastError_ = "not initialized";
};

