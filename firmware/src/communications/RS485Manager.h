#pragma once

#include "weather_data.h"
#include "app_config.h"

#include <Arduino.h>
#include <ModbusMaster.h>

struct RS485Diagnostic
{
    bool initialized;
    bool lastReadSuccess;
    bool lastReadingPlausible;
    uint32_t totalReads;
    uint32_t successfulReads;
    uint32_t failedReads;
    uint32_t consecutiveFailures;
    uint32_t timeoutCount;
    uint32_t errorCount;
    uint32_t lastSuccessfulReadMs;
    uint16_t lastRawValue;
    float lastWindSpeedMps;
    uint8_t lastResultCode;
};

class RS485Manager
{
public:
    void begin(bool startBackgroundWorker = false);
    void update(WeatherData& data);
    bool readWindSpeed(WeatherData& data, bool verbose = true);
    bool readWindDirectionPlaceholder();
    void scanWindSensor();
    void printWindSpeedBootSummary() const;
    void printStatus() const;
    void testBus();
    RS485Diagnostic diagnostic() const;

private:
    static void taskEntry(void* parameter);
    void taskLoop();
    static void preTransmission();
    static void postTransmission();

    bool readHoldingRegister(uint8_t slaveId, uint16_t registerAddress, uint16_t registerLength, uint16_t& value);
    void recordResult(uint8_t resultCode, bool success);
    void updateHealth(WeatherData& data) const;
    const char* resultText(uint8_t resultCode) const;
    void printRegister(uint16_t reg) const;

    HardwareSerial rs485Serial_{AppConfig::Uart::WindSpeedPort};
    ModbusMaster node_;
    TaskHandle_t taskHandle_ = nullptr;
    portMUX_TYPE snapshotMutex_ = portMUX_INITIALIZER_UNLOCKED;
    WeatherData workerSnapshot_ = {};
    bool initialized_ = false;
    bool lastReadSuccess_ = false;
    bool lastReadingPlausible_ = false;
    uint32_t totalReads_ = 0;
    uint32_t successfulReads_ = 0;
    uint32_t failedReads_ = 0;
    uint32_t consecutiveFailures_ = 0;
    uint32_t timeoutCount_ = 0;
    uint32_t errorCount_ = 0;
    uint32_t lastSuccessfulReadMs_ = 0;
    uint16_t lastRawValue_ = 0;
    float lastWindSpeedMps_ = 0.0f;
    uint8_t lastResultCode_ = 0;
};
