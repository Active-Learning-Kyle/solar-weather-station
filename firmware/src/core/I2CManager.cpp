#include "I2CManager.h"

#include "SerialPrintManager.h"
#include "pins.h"
#include "app_config.h"

#include <Wire.h>
#include <string.h>

namespace
{
struct ExpectedI2CDevice
{
    const char* name;
    const uint8_t* addresses;
    size_t addressCount;
};

constexpr uint8_t Sht40Addresses[] = {0x44};
constexpr uint8_t Bmp180Addresses[] = {0x77};
constexpr uint8_t Bh1750Addresses[] = {0x23, 0x5C};
constexpr uint8_t Ltr390Addresses[] = {0x53};

constexpr ExpectedI2CDevice ExpectedDevices[] = {
    {"SHT4x", Sht40Addresses, sizeof(Sht40Addresses) / sizeof(Sht40Addresses[0])},
    {"BMP180", Bmp180Addresses, sizeof(Bmp180Addresses) / sizeof(Bmp180Addresses[0])},
    {"BH1750", Bh1750Addresses, sizeof(Bh1750Addresses) / sizeof(Bh1750Addresses[0])},
    {"LTR390", Ltr390Addresses, sizeof(Ltr390Addresses) / sizeof(Ltr390Addresses[0])},
};
}

namespace Core
{
bool I2CManager::detectedAddresses_[128] = {};

void I2CManager::begin()
{
    Serial.print("Initializing I2C bus on SDA GPIO");
    Serial.print(Pins::I2C_SDA);
    Serial.print(", SCL GPIO");
    Serial.println(Pins::I2C_SCL);

    Wire.begin(Pins::I2C_SDA, Pins::I2C_SCL);
    Wire.setClock(AppConfig::I2cClockHz);
}

void I2CManager::scanBus()
{
    SerialPrintManager::Lock serialLock;

    memset(detectedAddresses_, 0, sizeof(detectedAddresses_));

    Serial.println("Scanning I2C bus...");

    uint8_t detectedCount = 0;
    for (uint8_t address = 0x01; address <= 0x7F; ++address)
    {
        Wire.beginTransmission(address);
        const uint8_t result = Wire.endTransmission();

        if (result == 0)
        {
            detectedAddresses_[address] = true;
            ++detectedCount;

            Serial.print("I2C device detected at ");
            printAddress(address);
            Serial.println();
        }
    }

    if (detectedCount == 0)
    {
        Serial.println("No I2C devices detected");
    }
    else
    {
        Serial.print("I2C scan complete, devices found: ");
        Serial.println(detectedCount);
    }

    Serial.println("Expected I2C sensor check:");
    for (const ExpectedI2CDevice& device : ExpectedDevices)
    {
        bool present = false;
        for (size_t i = 0; i < device.addressCount; ++i)
        {
            if (isDetected(device.addresses[i]))
            {
                present = true;
                break;
            }
        }

        Serial.print(device.name);
        Serial.print(": ");
        Serial.print(present ? "PASS" : "FAIL");
        Serial.print(" (expected ");
        for (size_t i = 0; i < device.addressCount; ++i)
        {
            if (i > 0)
            {
                Serial.print(" or ");
            }
            printAddress(device.addresses[i]);
        }
        Serial.println(")");
    }
}

bool I2CManager::isDetected(uint8_t address)
{
    return address < sizeof(detectedAddresses_) && detectedAddresses_[address];
}

void I2CManager::printAddress(uint8_t address)
{
    Serial.print("0x");
    if (address < 0x10)
    {
        Serial.print("0");
    }
    Serial.print(address, HEX);
}
}
