#include <Arduino.h>

#include "app_config.h"
#include "communications/HttpDataUploader.h"
#include "communications/RS485Manager.h"
#include "core/I2CManager.h"
#include "core/NetworkManager.h"
#include "pins.h"
#include "sensors/GPSManager.h"
#include "sensors/PMS7003Sensor.h"
#include "sensors/SensorManager.h"

namespace
{
SensorManager environmentalSensors;
PMS7003Sensor pms7003;
GPSManager gnss;
RS485Manager rs485;
uint32_t lastEnvironmentalReadMs = 0;
uint32_t lastPmsReadMs = 0;
uint32_t lastSnapshotMs = 0;
uint32_t lastUploadScheduleMs = 0;

static_assert(AppConfig::Uart::PmsPort == 2, "PMS7003 production allocation must remain UART2");
static_assert(AppConfig::Uart::GnssPort == 1, "GNSS production allocation must remain UART1");
static_assert(AppConfig::Uart::WindSpeedPort == 0, "Production RS485 must use UART0 with USB CDC debug");

bool due(uint32_t nowMs, uint32_t lastMs, uint32_t periodMs)
{
    return lastMs == 0 || (nowMs - lastMs) >= periodMs;
}

void updatePmsHealth(WeatherData& data)
{
    const PMS7003Diagnostic diagnostic = pms7003.diagnostic();
    SensorHealth& health = data.pms7003Health;
    health.initialized = diagnostic.initialized;
    health.latestValueValid = diagnostic.latestValueValid;
    health.lastSuccessfulReadMs = diagnostic.lastValidFrameMs;
    health.consecutiveFailures = diagnostic.consecutiveFailures;
    health.totalFailures = diagnostic.readFailures + diagnostic.checksumErrors;
}

bool stale(const SensorHealth& health, uint32_t nowMs)
{
    return health.lastSuccessfulReadMs == 0 ||
           (nowMs - health.lastSuccessfulReadMs) > AppConfig::SensorStaleAfterMs;
}

void invalidateIf(bool invalid, SensorHealth& health)
{
    if (invalid && health.latestValueValid)
    {
        health.latestValueValid = false;
        ++health.consecutiveFailures;
        ++health.totalFailures;
    }
}

void validateSnapshot(WeatherData& data)
{
    invalidateIf(data.temperature < -80.0f || data.temperature > 85.0f ||
                     data.humidity < 0.0f || data.humidity > 100.0f,
                 data.sht4xHealth);
    invalidateIf(data.pressure < 300.0f || data.pressure > 1200.0f,
                 data.bmp180Health);
    invalidateIf(data.lightLux < 0.0f, data.bh1750Health);
    invalidateIf(data.pm1_0 < 0.0f || data.pm2_5 < 0.0f || data.pm10 < 0.0f ||
                     data.pm1_0 > 1000.0f || data.pm2_5 > 1000.0f || data.pm10 > 1000.0f,
                 data.pms7003Health);
}

void printValue(const char* label, float value, const char* unit, const SensorHealth& health, uint32_t nowMs)
{
    Serial.print(label);
    Serial.print(": ");
    if (!health.latestValueValid || stale(health, nowMs))
    {
        Serial.println("unavailable");
        return;
    }
    Serial.print(value, 2);
    Serial.print(" ");
    Serial.println(unit);
}

void printHealth(const char* name, SensorHealth& health, uint32_t nowMs)
{
    health.stale = stale(health, nowMs);
    Serial.print(name);
    Serial.print(": ");
    if (!health.initialized)
        Serial.print("NOT INITIALIZED");
    else if (!health.latestValueValid)
        Serial.print("READ FAILED");
    else if (health.stale)
        Serial.print("STALE");
    else
        Serial.print("OK");

    Serial.print(" (failures=");
    Serial.print(health.totalFailures);
    Serial.print(", consecutive=");
    Serial.print(health.consecutiveFailures);
    Serial.print(", last_success=");
    if (health.lastSuccessfulReadMs == 0)
        Serial.print("never");
    else
    {
        Serial.print(nowMs - health.lastSuccessfulReadMs);
        Serial.print(" ms ago");
    }
    Serial.println(")");
}

void printSnapshot()
{
    WeatherData& data = environmentalSensors.data();
    const uint32_t nowMs = millis();
    data.timestamp = nowMs;
    data.uptimeMs = nowMs;
    validateSnapshot(data);

    Serial.println();
    Serial.println("========== WEATHER SNAPSHOT ==========");
    Serial.print("Station: "); Serial.println(AppConfig::StationId);
    Serial.print("Uptime: "); Serial.print(nowMs / 1000); Serial.println(" s");
    printValue("Temperature", data.temperature, "C", data.sht4xHealth, nowMs);
    printValue("Humidity", data.humidity, "%", data.sht4xHealth, nowMs);
    printValue("Pressure", data.pressure, "hPa", data.bmp180Health, nowMs);
    printValue("Light", data.lightLux, "lux", data.bh1750Health, nowMs);
    if (data.ltr390Health.latestValueValid && !stale(data.ltr390Health, nowMs))
    {
        Serial.print("UV raw: "); Serial.println(data.uvRaw);
        Serial.print("UV index estimate: "); Serial.println(data.uvIndex, 2);
    }
    else
        Serial.println("UV: unavailable");
    printValue("PM1.0", data.pm1_0, "ug/m3", data.pms7003Health, nowMs);
    printValue("PM2.5", data.pm2_5, "ug/m3", data.pms7003Health, nowMs);
    printValue("PM10", data.pm10, "ug/m3", data.pms7003Health, nowMs);

    Serial.println();
    Serial.println("Wind:");
    printValue("Wind Speed", data.windSpeed, "m/s", data.windSpeedHealth, nowMs);

    Serial.println();
    Serial.println("Sensor Health:");
    printHealth("SHT4x", data.sht4xHealth, nowMs);
    printHealth("BMP180", data.bmp180Health, nowMs);
    printHealth("BH1750", data.bh1750Health, nowMs);
    printHealth("LTR390", data.ltr390Health, nowMs);
    printHealth("PMS7003", data.pms7003Health, nowMs);
    data.windSpeedHealth.stale = stale(data.windSpeedHealth, nowMs);
    Serial.print("Wind Speed: ");
    if (!data.windSpeedHealth.initialized)
        Serial.print("NOT CONNECTED");
    else if (data.windSpeedHealth.stale && data.windSpeedHealth.latestValueValid)
        Serial.print("STALE");
    else if (!data.windSpeedHealth.latestValueValid)
    {
        if (data.windSpeedLastModbusResult == 0xE2)
            Serial.print("MODBUS TIMEOUT");
        else
            Serial.print("MODBUS ERROR");
    }
    else
        Serial.print("OK");
    Serial.print(" (failures=");
    Serial.print(data.windSpeedHealth.totalFailures);
    Serial.print(", consecutive=");
    Serial.print(data.windSpeedHealth.consecutiveFailures);
    Serial.println(")");

    Serial.println();
    gnss.printStatus();

    const UploadStatus upload = HttpDataUploader::status();
    Serial.println();
    Serial.println("Network:");
    Serial.print("Wi-Fi: "); Serial.println(Core::NetworkManager::stateName());
    if (Core::NetworkManager::isWiFiConnected())
    {
        Serial.print("IP: "); Serial.println(Core::NetworkManager::ipAddress());
    }
    Serial.print("NTP: ");
    Serial.println(Core::NetworkManager::isTimeSynced() ? "SYNCED" : "NOT SYNCED");
    Serial.print("Last upload: ");
    if (upload.lastSuccessfulUploadMs == 0)
        Serial.println("never");
    else
    {
        Serial.print((nowMs - upload.lastSuccessfulUploadMs) / 1000);
        Serial.println(" s ago");
    }
    Serial.print("Uploads: "); Serial.print(upload.successfulUploads); Serial.print(" successful, ");
    Serial.print(upload.failedUploads); Serial.print(" failed (consecutive=");
    Serial.print(upload.consecutiveFailures); Serial.print(", last_http=");
    Serial.print(upload.lastHttpResponseCode); Serial.println(")");
    Serial.println("Deferred: wind direction, rain, battery, solar");
    Serial.println("======================================");
}
}

void setup()
{
    Serial.begin(AppConfig::SerialBaud);
    delay(800);
    Serial.println();
    Serial.println(AppConfig::FirmwareName);
    Serial.println("Active: I2C environmental sensors + PMS7003 + GNSS + RS485 wind speed");

    if (AppConfig::EnableI2cSensors)
    {
        Core::I2CManager::begin();
        Core::I2CManager::scanBus();
        environmentalSensors.begin();
    }
    if (AppConfig::EnablePms7003)
    {
        pms7003.begin();
        updatePmsHealth(environmentalSensors.data());
    }
    if (AppConfig::EnableGnss)
    {
        gnss.begin(environmentalSensors.data());
        Serial.println("GNSS worker started; acquisition is isolated from the main scheduler.");
    }
    if (AppConfig::EnableRs485Wind)
    {
        rs485.begin(true);
        Serial.println("RS485 wind-speed acquisition initialized independently of other sensors.");
    }
    Serial.println("Sensor initialization complete; failed sensors will be retried by the scheduler.");

    Core::NetworkManager::begin();
    HttpDataUploader::begin();
    Serial.println("Network services started independently of sensor acquisition.");
}

void loop()
{
    const uint32_t nowMs = millis();
    Core::NetworkManager::tick();
    if (AppConfig::EnableGnss)
        gnss.update();
    if (AppConfig::EnableRs485Wind)
        rs485.update(environmentalSensors.data());
    if (AppConfig::EnableI2cSensors && due(nowMs, lastEnvironmentalReadMs, AppConfig::EnvironmentalPeriodMs))
    {
        lastEnvironmentalReadMs = nowMs;
        environmentalSensors.read();
    }
    if (AppConfig::EnablePms7003 && due(nowMs, lastPmsReadMs, AppConfig::PmsPeriodMs))
    {
        lastPmsReadMs = nowMs;
        pms7003.read(environmentalSensors.data(), AppConfig::PmsReadTimeoutMs);
        updatePmsHealth(environmentalSensors.data());
    }
    if (due(nowMs, lastSnapshotMs, AppConfig::SnapshotPeriodMs))
    {
        lastSnapshotMs = nowMs;
        printSnapshot();
    }
    if (due(nowMs, lastUploadScheduleMs, AppConfig::UploadPeriodMs))
    {
        lastUploadScheduleMs = nowMs;
        WeatherData& data = environmentalSensors.data();
        if (AppConfig::EnableGnss)
            gnss.update();
        if (AppConfig::EnableRs485Wind)
            rs485.update(data);
        data.uptimeMs = nowMs;
        validateSnapshot(data);
        HttpDataUploader::enqueue(data);
    }
    delay(5);
}
