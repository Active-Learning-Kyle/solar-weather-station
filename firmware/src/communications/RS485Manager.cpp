#include "RS485Manager.h"

#include "core/SerialPrintManager.h"
#include "pins.h"

namespace
{
constexpr uint32_t RS485SerialMode = SERIAL_8N1;
constexpr uint8_t WindSpeedSlaveId = 0x01;
constexpr uint8_t WindDirectionSlaveId = 0x02;
constexpr uint16_t WindRegisterAddress = 0x0000;
constexpr uint16_t WindSpeedRegisterLength = 1;
constexpr float WindSpeedRawDivisor = 10.0f;
// Diagnostic warning threshold only. A value above this is still a successful
// Modbus transaction, but should prompt a wiring/configuration sanity check.
constexpr float MaximumPlausibleWindSpeedMps = 100.0f;

constexpr uint32_t ScanBaudRates[] = {2400, 4800, 9600, 19200};
constexpr uint32_t ScanSerialModes[] = {SERIAL_8N1, SERIAL_8E1, SERIAL_8O1};
constexpr const char* ScanSerialModeNames[] = {"8N1", "8E1", "8O1"};
constexpr uint8_t ScanFirstSlaveId = 1;
constexpr uint8_t ScanLastSlaveId = 20;
constexpr uint16_t ScanRegisters[] = {0x0000, 0x0001, 0x0002, 0x0003};

HardwareSerial* activeRS485Serial = nullptr;
}

void RS485Manager::begin(bool startBackgroundWorker)
{
    pinMode(Pins::RS485_DE_RE, OUTPUT);
    digitalWrite(Pins::RS485_DE_RE, LOW);
    Serial.println("[2] DE/RE pin initialized");

    activeRS485Serial = &rs485Serial_;
    rs485Serial_.begin(AppConfig::Uart::WindBaud, RS485SerialMode, Pins::RS485_RX, Pins::RS485_TX);
    Serial.println("[3] RS485 UART initialized");

    node_.preTransmission(preTransmission);
    node_.postTransmission(postTransmission);
    node_.begin(WindSpeedSlaveId, rs485Serial_);
    initialized_ = true;
    Serial.println("[4] Modbus initialized");

    Core::SerialPrintManager::Lock serialLock;
    Serial.print("RS485Manager initialized on RX GPIO");
    Serial.print(Pins::RS485_RX);
    Serial.print(", TX GPIO");
    Serial.print(Pins::RS485_TX);
    Serial.print(", DE/RE GPIO");
    Serial.print(Pins::RS485_DE_RE);
    Serial.print(", baud ");
    Serial.println(AppConfig::Uart::WindBaud);
    Serial.print("RS485 peripheral: UART");
    Serial.println(AppConfig::Uart::WindSpeedPort);
    Serial.println("RS485 mode: MAX3485 wind speed, 4800 8N1, slave 1, register 0x0000");

    if (startBackgroundWorker && taskHandle_ == nullptr)
    {
        if (xTaskCreate(taskEntry, "rs485-wind", 4096, this, 1,
                        &taskHandle_) != pdPASS)
        {
            taskHandle_ = nullptr;
            initialized_ = false;
            Serial.println("RS485 wind worker creation failed; other subsystems remain active");
        }
    }
}

void RS485Manager::update(WeatherData& data)
{
    portENTER_CRITICAL(&snapshotMutex_);
    data.windSpeed = workerSnapshot_.windSpeed;
    data.windSpeedLastModbusResult = workerSnapshot_.windSpeedLastModbusResult;
    data.windSpeedHealth = workerSnapshot_.windSpeedHealth;
    portEXIT_CRITICAL(&snapshotMutex_);
}

void RS485Manager::taskEntry(void* parameter)
{
    static_cast<RS485Manager*>(parameter)->taskLoop();
}

void RS485Manager::taskLoop()
{
    WeatherData latest = {};
    for (;;)
    {
        readWindSpeed(latest, false);
        portENTER_CRITICAL(&snapshotMutex_);
        workerSnapshot_.windSpeed = latest.windSpeed;
        workerSnapshot_.windSpeedLastModbusResult = latest.windSpeedLastModbusResult;
        workerSnapshot_.windSpeedHealth = latest.windSpeedHealth;
        portEXIT_CRITICAL(&snapshotMutex_);
        vTaskDelay(pdMS_TO_TICKS(AppConfig::WindSpeedPeriodMs));
    }
}

bool RS485Manager::readWindSpeed(WeatherData& data, bool verbose)
{
    uint16_t rawValue = 0;
    if (verbose)
    {
        Core::SerialPrintManager::Lock serialLock;
        Serial.println("Request sent: slave=1 function=0x03 register=0x0000 count=1");
    }
    const bool success = readHoldingRegister(WindSpeedSlaveId, WindRegisterAddress, WindSpeedRegisterLength, rawValue);
    const float windSpeedMps = rawValue / WindSpeedRawDivisor;

    if (success)
    {
        data.windSpeed = windSpeedMps;
        data.timestamp = millis();
        lastRawValue_ = rawValue;
        lastWindSpeedMps_ = windSpeedMps;
        lastReadingPlausible_ = windSpeedMps <= MaximumPlausibleWindSpeedMps;
    }
    data.windSpeedLastModbusResult = lastResultCode_;
    updateHealth(data);

    if (!verbose)
        return success;

    Core::SerialPrintManager::Lock serialLock;
    Serial.println("----- RS485 Wind Speed Read -----");
    Serial.print("Slave ID: 0x");
    if (WindSpeedSlaveId < 0x10)
    {
        Serial.print("0");
    }
    Serial.println(WindSpeedSlaveId, HEX);
    Serial.print("Register: 0x");
    printRegister(WindRegisterAddress);
    Serial.println();
    Serial.print("Raw register value: ");
    if (success)
    {
        Serial.println(rawValue);
    }
    else
    {
        Serial.println("not available");
    }
    Serial.print("Wind speed: ");
    if (success)
    {
        Serial.print(windSpeedMps, 1);
        Serial.println(" m/s");
    }
    else
    {
        Serial.println("unavailable");
    }
    Serial.print("Modbus result: 0x");
    if (lastResultCode_ < 0x10)
    {
        Serial.print("0");
    }
    Serial.print(lastResultCode_, HEX);
    Serial.print(" - ");
    Serial.print(resultText(lastResultCode_));
    Serial.println();
    Serial.print("Reads: ");
    Serial.println(totalReads_);
    Serial.print("Successes: ");
    Serial.println(successfulReads_);
    Serial.print("Failures: ");
    Serial.println(failedReads_);
    Serial.print("Consecutive failures: ");
    Serial.println(consecutiveFailures_);
    Serial.print("Last success: ");
    if (lastSuccessfulReadMs_ > 0)
    {
        Serial.print((millis() - lastSuccessfulReadMs_) / 1000U);
        Serial.print(" s ago (raw=");
        Serial.print(lastRawValue_);
        Serial.print(", ");
        Serial.print(lastWindSpeedMps_, 1);
        Serial.println(" m/s)");
    }
    else
    {
        Serial.println("never");
    }
    Serial.print("Status: ");
    if (!success)
    {
        if (lastResultCode_ == node_.ku8MBResponseTimedOut) Serial.println("TIMEOUT");
        else if (lastResultCode_ == node_.ku8MBInvalidCRC) Serial.println("CRC ERROR");
        else if (lastResultCode_ == 0xFF) Serial.println("NOT INITIALIZED");
        else Serial.println("MODBUS ERROR");
    }
    else if (!lastReadingPlausible_)
    {
        Serial.println("VALID READING - SUSPICIOUSLY HIGH");
    }
    else
    {
        Serial.println("VALID READING");
    }
    Serial.println("--------------------------------");

    return success;
}

bool RS485Manager::readWindDirectionPlaceholder()
{
    Core::SerialPrintManager::Lock serialLock;
    Serial.println("----- RS485 Wind Direction Read -----");
    Serial.print("Placeholder slave ID: 0x");
    if (WindDirectionSlaveId < 0x10)
    {
        Serial.print("0");
    }
    Serial.println(WindDirectionSlaveId, HEX);
    Serial.print("Register: 0x");
    printRegister(WindRegisterAddress);
    Serial.println();
    Serial.println("Register length is TBD; direction read is intentionally disabled.");
    Serial.println("No 0-360 degree conversion will be assumed until the register map is confirmed.");
    Serial.println("------------------------------------");

    return false;
}

void RS485Manager::scanWindSensor()
{
    Core::SerialPrintManager::Lock serialLock;
    Serial.println("----- RS485 Wind Sensor Manual Scan -----");
    Serial.println("Scanning baud=2400/4800/9600/19200, mode=8N1/8E1/8O1, id=1-20, reg=0x0000-0x0003");

    for (size_t baudIndex = 0; baudIndex < sizeof(ScanBaudRates) / sizeof(ScanBaudRates[0]); ++baudIndex)
    {
        for (size_t modeIndex = 0; modeIndex < sizeof(ScanSerialModes) / sizeof(ScanSerialModes[0]); ++modeIndex)
        {
            rs485Serial_.end();
            delay(20);
            digitalWrite(Pins::RS485_DE_RE, LOW);
            activeRS485Serial = &rs485Serial_;
            rs485Serial_.begin(ScanBaudRates[baudIndex], ScanSerialModes[modeIndex], Pins::RS485_RX, Pins::RS485_TX);
            node_.preTransmission(preTransmission);
            node_.postTransmission(postTransmission);

            for (uint8_t slaveId = ScanFirstSlaveId; slaveId <= ScanLastSlaveId; ++slaveId)
            {
                for (size_t regIndex = 0; regIndex < sizeof(ScanRegisters) / sizeof(ScanRegisters[0]); ++regIndex)
                {
                    const uint16_t reg = ScanRegisters[regIndex];
                    uint16_t raw = 0;
                    node_.begin(slaveId, rs485Serial_);
                    const uint8_t result = node_.readHoldingRegisters(reg, WindSpeedRegisterLength);
                    if (result == node_.ku8MBSuccess)
                    {
                        raw = node_.getResponseBuffer(0);
                    }

                    Serial.print("baud=");
                    Serial.print(ScanBaudRates[baudIndex]);
                    Serial.print(" mode=");
                    Serial.print(ScanSerialModeNames[modeIndex]);
                    Serial.print(" id=");
                    Serial.print(slaveId);
                    Serial.print(" reg=");
                    printRegister(reg);
                    Serial.print(" result=");
                    Serial.print(result);

                    if (result == node_.ku8MBSuccess)
                    {
                        Serial.print(" raw=");
                        Serial.print(raw);
                        Serial.print(" speed=");
                        Serial.print(raw / WindSpeedRawDivisor, 1);
                        Serial.println("m/s");
                    }
                    else
                    {
                        Serial.print(" ");
                        Serial.println(resultText(result));
                    }
                    delay(25);
                }
            }
        }
    }

    rs485Serial_.end();
    delay(20);
    digitalWrite(Pins::RS485_DE_RE, LOW);
    activeRS485Serial = &rs485Serial_;
    rs485Serial_.begin(AppConfig::Uart::WindBaud, RS485SerialMode, Pins::RS485_RX, Pins::RS485_TX);
    node_.begin(WindSpeedSlaveId, rs485Serial_);
    node_.preTransmission(preTransmission);
    node_.postTransmission(postTransmission);
    Serial.println("----- RS485 scan complete; restored baud=4800 mode=8N1 id=1 -----");
}

void RS485Manager::printWindSpeedBootSummary() const
{
    Core::SerialPrintManager::Lock serialLock;
    Serial.println("========== RS485 WIND SPEED DIAGNOSTIC ==========");
    Serial.println("Wiring:");
    Serial.print("ESP32 RX: GPIO"); Serial.print(Pins::RS485_RX); Serial.println(" <- transceiver RO");
    Serial.print("ESP32 TX: GPIO"); Serial.print(Pins::RS485_TX); Serial.println(" -> transceiver DI");
    Serial.print("RS485 DE/RE: GPIO"); Serial.print(Pins::RS485_DE_RE); Serial.println(" -> shared DE and /RE");
    Serial.println("Sensor A -> transceiver A; sensor B -> transceiver B");
    Serial.println("ESP32, transceiver, sensor supply: common ground required");
    Serial.println("Sensor power: external 12 V supply/boost rail per project documentation");
    Serial.println("Transceiver logic: 3.3 V-compatible");
    Serial.println();
    Serial.println("UART:");
    Serial.println("Debug console: UART0 at 115200 baud");
    Serial.print("RS485 peripheral: UART"); Serial.println(AppConfig::Uart::WindSpeedPort);
    Serial.print("Baud: "); Serial.println(AppConfig::Uart::WindBaud);
    Serial.println("Format: 8N1");
    Serial.println();
    Serial.println("Modbus:");
    Serial.print("Slave ID: "); Serial.println(WindSpeedSlaveId);
    Serial.print("Register: "); printRegister(WindRegisterAddress); Serial.println();
    Serial.println("Function: 0x03 (Read Holding Registers)");
    Serial.println("Scale: raw / 10.0");
    Serial.println("Unit: m/s");
    Serial.println("Plausibility warning: values above 100.0 m/s are suspicious");
    Serial.println("Automatic poll: 1 s; manual command: read");
    Serial.println("Bus idle direction: receive (DE/RE LOW)");
    Serial.println("=================================================");
}

void RS485Manager::printStatus() const
{
    const RS485Diagnostic diag = diagnostic();

    Core::SerialPrintManager::Lock serialLock;
    Serial.println("----- RS485 Status -----");
    Serial.print("Initialized: ");
    Serial.println(diag.initialized ? "yes" : "no");
    Serial.print("Wind speed sensor status: ");
    Serial.println(diag.lastReadSuccess ? "OK" : "not OK");
    Serial.print("Successful reads: ");
    Serial.println(diag.successfulReads);
    Serial.print("Timeout count: ");
    Serial.println(diag.timeoutCount);
    Serial.print("CRC/error count: ");
    Serial.println(diag.errorCount);
    Serial.print("Last successful read age: ");
    if (diag.lastSuccessfulReadMs > 0)
    {
        Serial.print(millis() - diag.lastSuccessfulReadMs);
        Serial.println(" ms");
    }
    else
    {
        Serial.println("never");
    }
    Serial.print("Last Modbus result code: ");
    Serial.print(diag.lastResultCode);
    Serial.print(" (");
    Serial.print(resultText(diag.lastResultCode));
    Serial.println(")");
    Serial.print("DE/RE pin state: ");
    Serial.println(digitalRead(Pins::RS485_DE_RE) == HIGH ? "TX/HIGH" : "RX/LOW");
    Serial.println("------------------------");
}

void RS485Manager::testBus()
{
    Core::SerialPrintManager::Lock serialLock;
    Serial.println("----- RS485 Bus Test -----");
    Serial.println("Toggling DE/RE pin to verify transceiver direction control.");
    digitalWrite(Pins::RS485_DE_RE, HIGH);
    delay(20);
    Serial.print("DE/RE after TX enable: ");
    Serial.println(digitalRead(Pins::RS485_DE_RE) == HIGH ? "HIGH" : "LOW");
    digitalWrite(Pins::RS485_DE_RE, LOW);
    delay(20);
    Serial.print("DE/RE after RX enable: ");
    Serial.println(digitalRead(Pins::RS485_DE_RE) == HIGH ? "HIGH" : "LOW");
    Serial.println("-------------------------");
}

RS485Diagnostic RS485Manager::diagnostic() const
{
    return {initialized_, lastReadSuccess_, lastReadingPlausible_, totalReads_, successfulReads_, failedReads_,
            consecutiveFailures_, timeoutCount_, errorCount_, lastSuccessfulReadMs_, lastRawValue_,
            lastWindSpeedMps_, lastResultCode_};
}

void RS485Manager::preTransmission()
{
    digitalWrite(Pins::RS485_DE_RE, HIGH);
    delay(2);
}

void RS485Manager::postTransmission()
{
    if (activeRS485Serial != nullptr)
    {
        activeRS485Serial->flush();
    }
    delay(2);
    digitalWrite(Pins::RS485_DE_RE, LOW);
}

bool RS485Manager::readHoldingRegister(uint8_t slaveId, uint16_t registerAddress, uint16_t registerLength, uint16_t& value)
{
    value = 0;

    if (!initialized_)
    {
        recordResult(0xFF, false);
        return false;
    }

    node_.begin(slaveId, rs485Serial_);
    const uint8_t result = node_.readHoldingRegisters(registerAddress, registerLength);
    const bool success = result == node_.ku8MBSuccess;
    if (success && registerLength > 0)
    {
        value = node_.getResponseBuffer(0);
    }

    recordResult(result, success);
    return success;
}

void RS485Manager::recordResult(uint8_t resultCode, bool success)
{
    ++totalReads_;
    lastResultCode_ = resultCode;
    lastReadSuccess_ = success;
    if (success)
    {
        ++successfulReads_;
        consecutiveFailures_ = 0;
        lastSuccessfulReadMs_ = millis();
        return;
    }

    ++failedReads_;
    ++consecutiveFailures_;
    lastReadingPlausible_ = false;
    if (resultCode == node_.ku8MBResponseTimedOut)
    {
        ++timeoutCount_;
    }
    else
    {
        ++errorCount_;
    }
}

const char* RS485Manager::resultText(uint8_t resultCode) const
{
    if (resultCode == node_.ku8MBSuccess)
    {
        return "Success";
    }
    if (resultCode == node_.ku8MBIllegalFunction)
    {
        return "Illegal function";
    }
    if (resultCode == node_.ku8MBIllegalDataAddress)
    {
        return "Illegal data address";
    }
    if (resultCode == node_.ku8MBIllegalDataValue)
    {
        return "Illegal data value";
    }
    if (resultCode == node_.ku8MBSlaveDeviceFailure)
    {
        return "Slave device failure";
    }
    if (resultCode == node_.ku8MBInvalidSlaveID)
    {
        return "Invalid slave ID/response";
    }
    if (resultCode == node_.ku8MBInvalidFunction)
    {
        return "Invalid function/response";
    }
    if (resultCode == node_.ku8MBResponseTimedOut)
    {
        return "Response timed out";
    }
    if (resultCode == node_.ku8MBInvalidCRC)
    {
        return "Invalid CRC";
    }
    if (resultCode == 0xFF)
    {
        return "Not initialized";
    }

    return "Generic communication error";
}

void RS485Manager::updateHealth(WeatherData& data) const
{
    SensorHealth& health = data.windSpeedHealth;
    health.initialized = initialized_;
    health.latestValueValid = lastReadSuccess_;
    health.lastSuccessfulReadMs = lastSuccessfulReadMs_;
    health.consecutiveFailures = consecutiveFailures_;
    health.totalFailures = failedReads_;
    health.stale = lastSuccessfulReadMs_ == 0 ||
                   (millis() - lastSuccessfulReadMs_) > AppConfig::SensorStaleAfterMs;
}

void RS485Manager::printRegister(uint16_t reg) const
{
    Serial.print("0x");
    if (reg < 0x1000)
    {
        Serial.print("0");
    }
    if (reg < 0x0100)
    {
        Serial.print("0");
    }
    if (reg < 0x0010)
    {
        Serial.print("0");
    }
    Serial.print(reg, HEX);
}
