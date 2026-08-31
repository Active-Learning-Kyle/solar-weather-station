#include <Arduino.h>
#include <ModbusMaster.h>
#include "app_config.h"
#include "pins.h"

namespace
{
constexpr uint32_t PollPeriodMs = 1000;
constexpr uint32_t DirectionSerialMode = SERIAL_8N1;
constexpr uint8_t DirectionSlaveId = 1;
constexpr uint16_t DirectionStartRegister = 0x0000;
constexpr uint8_t DirectionRegisterCount = 2;
ModbusMaster directionNode;
uint32_t lastPollMs = 0;
String serialCommand;

void preTransmission() { digitalWrite(Pins::RS485_DE_RE, HIGH); delay(2); }
void postTransmission() { Serial2.flush(); delay(2); digitalWrite(Pins::RS485_DE_RE, LOW); }

const char* resultText(uint8_t result)
{
    if (result == directionNode.ku8MBSuccess) return "success";
    if (result == directionNode.ku8MBResponseTimedOut) return "timeout";
    if (result == directionNode.ku8MBInvalidCRC) return "invalid_crc";
    return "error";
}

const char* compassDirectionFromIndex(uint16_t index)
{
    static const char* names[] = {"North", "North-East", "East", "South-East", "South", "South-West", "West", "North-West"};
    return index <= 7 ? names[index] : "Unknown";
}

void readWindDirection()
{
    const uint8_t result = directionNode.readHoldingRegisters(DirectionStartRegister, DirectionRegisterCount);
    Serial.println("\n----- Wind Direction Read -----");
    Serial.print("baud=4800 mode=8N1 id=1 function=0x03 start=0x0000 len=2 result=");
    Serial.print(result); Serial.print(" "); Serial.println(resultText(result));
    if (result == directionNode.ku8MBSuccess)
    {
        const uint16_t index = directionNode.getResponseBuffer(0);
        const uint16_t angleDeg = directionNode.getResponseBuffer(1);
        Serial.print("reg0/direction index="); Serial.println(index);
        Serial.print("reg1/angle_deg="); Serial.println(angleDeg);
        Serial.print("compass direction="); Serial.println(compassDirectionFromIndex(index));
        if (index <= 7) { Serial.print("index nominal angle="); Serial.println(index * 45); }
    }
    Serial.println("-------------------------------");
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
            if (serialCommand.equalsIgnoreCase("dir_read")) readWindDirection();
            else if (serialCommand.length() > 0) Serial.println("Available command: dir_read");
            serialCommand = "";
        }
        else if (serialCommand.length() < 40) serialCommand += c;
    }
}
}

void setup()
{
    Serial.begin(AppConfig::SerialBaud);
    delay(1000);
    Serial.println("DIAGNOSTIC FIRMWARE - LATEST WIND DIRECTION TEST");
    Serial.println("Confirmed: 4800 8N1, slave 1, function 0x03, start 0x0000, length 2");
    Serial.println("reg0=direction index, reg1=angle degrees; command: dir_read");
    pinMode(Pins::RS485_DE_RE, OUTPUT);
    digitalWrite(Pins::RS485_DE_RE, LOW);
    Serial2.begin(AppConfig::Uart::WindBaud, DirectionSerialMode, Pins::RS485_RX, Pins::RS485_TX);
    directionNode.begin(DirectionSlaveId, Serial2);
    directionNode.preTransmission(preTransmission);
    directionNode.postTransmission(postTransmission);
}

void loop()
{
    handleSerialCommand();
    const uint32_t nowMs = millis();
    if (lastPollMs == 0 || nowMs - lastPollMs >= PollPeriodMs)
    {
        lastPollMs = nowMs;
        readWindDirection();
    }
    delay(10);
}
