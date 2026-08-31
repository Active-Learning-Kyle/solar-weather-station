#include "SensorManager.h"

#include "core/SerialPrintManager.h"

#include <Arduino.h>

void SensorManager::begin()
{
    Serial.println("Initializing environmental I2C sensors...");

    sht40_.begin();
    printBeginStatus(sht40_.diagnostic());

    bmp180_.begin();
    printBeginStatus(bmp180_.diagnostic());

    bh1750_.begin();
    printBeginStatus(bh1750_.diagnostic());

    ltr390_.begin();
    printBeginStatus(ltr390_.diagnostic());

    updateHealth(weatherData_.sht4xHealth, sht40_.diagnostic());
    updateHealth(weatherData_.bmp180Health, bmp180_.diagnostic());
    updateHealth(weatherData_.bh1750Health, bh1750_.diagnostic());
    updateHealth(weatherData_.ltr390Health, ltr390_.diagnostic());
}

void SensorManager::readAndPrint()
{
    Core::SerialPrintManager::Lock serialLock;

    Serial.println("----- Environmental Sensor Readings -----");

    const bool sht40Ok = sht40_.read(weatherData_);
    printReadStatus(sht40_.diagnostic());
    if (sht40Ok)
    {
        Serial.print("  Temperature: ");
        Serial.print(weatherData_.temperature, 2);
        Serial.println(" C");
        Serial.print("  Humidity: ");
        Serial.print(weatherData_.humidity, 2);
        Serial.println(" %");
    }

    const bool bmp180Ok = bmp180_.read(weatherData_);
    printReadStatus(bmp180_.diagnostic());
    if (bmp180Ok)
    {
        Serial.print("  BMP180 temperature: ");
        Serial.print(weatherData_.pressureSensorTemperature, 2);
        Serial.println(" C");
        Serial.print("  Pressure: ");
        Serial.print(weatherData_.pressurePa);
        Serial.println(" Pa");
        Serial.print("  Pressure: ");
        Serial.print(weatherData_.pressure, 2);
        Serial.println(" hPa");
    }

    const bool bh1750Ok = bh1750_.read(weatherData_);
    printReadStatus(bh1750_.diagnostic());
    if (bh1750Ok)
    {
        Serial.print("  Light: ");
        Serial.print(weatherData_.lightLux, 2);
        Serial.println(" lx");
    }

    const bool ltr390Ok = ltr390_.read(weatherData_);
    printReadStatus(ltr390_.diagnostic());
    if (ltr390Ok)
    {
        Serial.print("  UV raw: ");
        Serial.println(weatherData_.uvRaw);
        Serial.print("  UV index estimate: ");
        Serial.println(weatherData_.uvIndex, 2);
    }

    weatherData_.timestamp = millis();
    Serial.print("WeatherData timestamp: ");
    Serial.print(weatherData_.timestamp);
    Serial.println(" ms");

    Serial.println("Sensor diagnostics:");
    printDiagnosticSummary(sht40_.diagnostic());
    printDiagnosticSummary(bmp180_.diagnostic());
    printDiagnosticSummary(bh1750_.diagnostic());
    printDiagnosticSummary(ltr390_.diagnostic());
    Serial.println("-----------------------------------------");
}

void SensorManager::read()
{
    // Each driver is attempted independently: one missing device never prevents
    // the other sensors from updating the shared snapshot.
    if (!sht40_.diagnostic().initialized) sht40_.begin();
    if (!bmp180_.diagnostic().initialized) bmp180_.begin();
    if (!bh1750_.diagnostic().initialized) bh1750_.begin();
    if (!ltr390_.diagnostic().initialized) ltr390_.begin();
    sht40_.read(weatherData_);
    bmp180_.read(weatherData_);
    bh1750_.read(weatherData_);
    ltr390_.read(weatherData_);

    updateHealth(weatherData_.sht4xHealth, sht40_.diagnostic());
    updateHealth(weatherData_.bmp180Health, bmp180_.diagnostic());
    updateHealth(weatherData_.bh1750Health, bh1750_.diagnostic());
    updateHealth(weatherData_.ltr390Health, ltr390_.diagnostic());
    weatherData_.timestamp = millis();
    weatherData_.uptimeMs = millis();
}

WeatherData& SensorManager::data()
{
    return weatherData_;
}

const SensorDiagnostic SensorManager::sht4xDiagnostic() const { return sht40_.diagnostic(); }
const SensorDiagnostic SensorManager::bmp180Diagnostic() const { return bmp180_.diagnostic(); }
const SensorDiagnostic SensorManager::bh1750Diagnostic() const { return bh1750_.diagnostic(); }
const SensorDiagnostic SensorManager::ltr390Diagnostic() const { return ltr390_.diagnostic(); }

void SensorManager::updateHealth(SensorHealth& health, const SensorDiagnostic& diagnostic)
{
    health.initialized = diagnostic.initialized;
    health.latestValueValid = diagnostic.latestValueValid;
    health.lastSuccessfulReadMs = diagnostic.lastSuccessfulReadMs;
    health.consecutiveFailures = diagnostic.consecutiveFailures;
    health.totalFailures = diagnostic.errorCount;
}

void SensorManager::printBeginStatus(const SensorDiagnostic& diagnostic)
{
    Serial.print(diagnostic.name);
    Serial.print(" init: ");
    Serial.println(diagnostic.initialized ? "PASS" : "FAIL");
    if (!diagnostic.initialized)
    {
        Serial.print("  ");
        Serial.println(diagnostic.lastError);
    }
}

void SensorManager::printReadStatus(const SensorDiagnostic& diagnostic)
{
    Serial.print(diagnostic.name);
    Serial.print(": ");
    Serial.println(diagnostic.lastReadSuccess ? "OK" : "FAIL");
    if (!diagnostic.lastReadSuccess)
    {
        Serial.print("  ");
        Serial.println(diagnostic.lastError);
    }
}

void SensorManager::printDiagnosticSummary(const SensorDiagnostic& diagnostic)
{
    Serial.print("  ");
    Serial.print(diagnostic.name);
    Serial.print(" initialized=");
    Serial.print(diagnostic.initialized ? "yes" : "no");
    Serial.print(", last_read=");
    Serial.print(diagnostic.lastReadSuccess ? "success" : "fail");
    Serial.print(", read_count=");
    Serial.print(diagnostic.readCount);
    Serial.print(", error_count=");
    Serial.print(diagnostic.errorCount);
    Serial.print(", consecutive_failures=");
    Serial.print(diagnostic.consecutiveFailures);
    if (diagnostic.lastError[0] != '\0')
    {
        Serial.print(", last_error=");
        Serial.print(diagnostic.lastError);
    }
    Serial.println();
}
