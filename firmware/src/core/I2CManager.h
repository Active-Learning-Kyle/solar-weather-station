#pragma once

#include <Arduino.h>

namespace Core
{
class I2CManager
{
public:
    static void begin();
    static void scanBus();

private:
    static bool isDetected(uint8_t address);
    static void printAddress(uint8_t address);
    static bool detectedAddresses_[128];
};
}

