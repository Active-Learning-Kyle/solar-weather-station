#include "PMS7003Sensor.h"

#include "core/SerialPrintManager.h"
#include "pins.h"

namespace
{
constexpr uint8_t FrameHeader1 = 0x42;
constexpr uint8_t FrameHeader2 = 0x4D;
constexpr uint16_t ExpectedFrameLength = 28;
}

void PMS7003Sensor::begin()
{
    pinMode(Pins::PMS_SLEEP, OUTPUT);
    wake();
    pmsSerial_.begin(AppConfig::Uart::PmsBaud, SERIAL_8N1, Pins::PMS_RX, Pins::PMS_TX);
    initialized_ = true;
    lastError_ = "";

    Serial.print("PMS7003 initialized on RX GPIO");
    Serial.print(Pins::PMS_RX);
    Serial.print(", TX GPIO");
    Serial.print(Pins::PMS_TX);
    Serial.print(", SET GPIO");
    Serial.print(Pins::PMS_SLEEP);
    Serial.print(", baud ");
    Serial.println(AppConfig::Uart::PmsBaud);
}

bool PMS7003Sensor::read(WeatherData& data, uint32_t timeoutMs)
{
    if (!initialized_)
    {
        latestValueValid_ = false;
        ++readFailures_;
        ++consecutiveFailures_;
        lastError_ = "PMS7003 not initialized";
        return false;
    }

    if (!awake_)
    {
        latestValueValid_ = false;
        ++readFailures_;
        ++consecutiveFailures_;
        lastError_ = "PMS7003 is asleep";
        return false;
    }

    uint8_t frame[FrameSize] = {};
    if (!readFrame(frame, timeoutMs))
    {
        latestValueValid_ = false;
        ++readFailures_;
        ++consecutiveFailures_;
        return false;
    }

    data.pm1_0Standard = readUint16(frame, 4);
    data.pm2_5Standard = readUint16(frame, 6);
    data.pm10Standard = readUint16(frame, 8);
    data.pm1_0Atmospheric = readUint16(frame, 10);
    data.pm2_5Atmospheric = readUint16(frame, 12);
    data.pm10Atmospheric = readUint16(frame, 14);

    data.pm1_0 = data.pm1_0Atmospheric;
    data.pm2_5 = data.pm2_5Atmospheric;
    data.pm10 = data.pm10Atmospheric;
    data.timestamp = millis();

    ++framesReceived_;
    consecutiveFailures_ = 0;
    lastValidFrameMs_ = millis();
    latestValueValid_ = true;
    lastError_ = "";
    return true;
}

void PMS7003Sensor::wake()
{
    digitalWrite(Pins::PMS_SLEEP, HIGH);
    awake_ = true;
}

void PMS7003Sensor::sleep()
{
    digitalWrite(Pins::PMS_SLEEP, LOW);
    awake_ = false;
}

void PMS7003Sensor::printStatus() const
{
    Core::SerialPrintManager::Lock serialLock;

    const PMS7003Diagnostic diag = diagnostic();

    Serial.println("----- PMS7003 Status -----");
    Serial.print("Initialized: ");
    Serial.println(diag.initialized ? "yes" : "no");
    Serial.print("Awake: ");
    Serial.println(diag.awake ? "yes" : "no");
    Serial.print("Frames received: ");
    Serial.println(diag.framesReceived);
    Serial.print("Checksum errors: ");
    Serial.println(diag.checksumErrors);
    Serial.print("Read failures: ");
    Serial.println(diag.readFailures);
    Serial.print("Last valid frame age: ");
    if (diag.lastValidFrameMs > 0)
    {
        Serial.print(millis() - diag.lastValidFrameMs);
        Serial.println(" ms");
    }
    else
    {
        Serial.println("never");
    }
    Serial.print("SET pin state: ");
    Serial.println(diag.awake ? "HIGH" : "LOW");
    Serial.print("Last error: ");
    Serial.println(diag.lastError[0] == '\0' ? "none" : diag.lastError);
    Serial.println("--------------------------");
}

PMS7003Diagnostic PMS7003Sensor::diagnostic() const
{
    return {initialized_, framesReceived_, checksumErrors_, readFailures_, consecutiveFailures_, lastValidFrameMs_, latestValueValid_, awake_, lastError_};
}

bool PMS7003Sensor::readFrame(uint8_t* frame, uint32_t timeoutMs)
{
    const uint32_t startMs = millis();
    size_t index = 0;

    while ((millis() - startMs) < timeoutMs)
    {
        while (pmsSerial_.available() > 0)
        {
            const int value = pmsSerial_.read();
            if (value < 0)
            {
                continue;
            }

            const uint8_t byteValue = static_cast<uint8_t>(value);

            if (index == 0 && byteValue != FrameHeader1)
            {
                continue;
            }

            if (index == 1 && byteValue != FrameHeader2)
            {
                index = 0;
                continue;
            }

            frame[index] = byteValue;
            ++index;

            if (index == FrameSize)
            {
                if (!validateFrame(frame))
                {
                    ++checksumErrors_;
                    lastError_ = "PMS7003 checksum or frame validation failed";
                    index = 0;
                    continue;
                }

                return true;
            }
        }

        delay(1);
    }

    lastError_ = "PMS7003 read timeout";
    return false;
}

bool PMS7003Sensor::validateFrame(const uint8_t* frame)
{
    if (frame[0] != FrameHeader1 || frame[1] != FrameHeader2)
    {
        return false;
    }

    if (readUint16(frame, 2) != ExpectedFrameLength)
    {
        return false;
    }

    uint16_t checksum = 0;
    for (size_t i = 0; i < FrameSize - 2; ++i)
    {
        checksum += frame[i];
    }

    return checksum == readUint16(frame, FrameSize - 2);
}

uint16_t PMS7003Sensor::readUint16(const uint8_t* frame, size_t index) const
{
    return (static_cast<uint16_t>(frame[index]) << 8) | frame[index + 1];
}

void PMS7003Sensor::flushInput()
{
    while (pmsSerial_.available() > 0)
    {
        pmsSerial_.read();
    }
}
