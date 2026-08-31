#include <Arduino.h>
#include "app_config.h"
#include "communications/RS485Manager.h"

namespace
{
constexpr uint32_t PollPeriodMs = 1000;
static_assert(AppConfig::Uart::WindSpeedPort != 0, "RS485 must not share UART0 with the debug console");
RS485Manager rs485;
WeatherData data = {};
uint32_t lastReadMs = 0;
bool firstReadPending = true;
String serialCommand;

void performRead()
{
    if (firstReadPending)
    {
        Serial.println("[5] Starting first Modbus read");
        firstReadPending = false;
    }
    rs485.readWindSpeed(data);
}

void handleSerialCommand()
{
    while (Serial.available() > 0)
    {
        const char c = static_cast<char>(Serial.read());
        if (c == '\r') continue;
        if (c == '\n')
        {
            serialCommand.trim();
            if (serialCommand.equalsIgnoreCase("read") || serialCommand.equalsIgnoreCase("wind_speed_read"))
            {
                performRead();
                lastReadMs = millis();
            }
            else if (serialCommand.length() > 0)
            {
                Serial.println("Available command: read");
            }
            serialCommand = "";
        }
        else if (serialCommand.length() < 40)
        {
            serialCommand += c;
        }
    }
}
}

void setup()
{
    Serial.begin(115200);
    delay(800);
    Serial.println("[BOOT] diag_wind_speed entered");
    Serial.println("[1] Serial initialized");
    rs485.begin();
    rs485.printWindSpeedBootSummary();
}

void loop()
{
    const uint32_t nowMs = millis();
    handleSerialCommand();
    if (lastReadMs == 0 || nowMs - lastReadMs >= PollPeriodMs)
    {
        lastReadMs = nowMs;
        performRead();
    }
    delay(10);
}
