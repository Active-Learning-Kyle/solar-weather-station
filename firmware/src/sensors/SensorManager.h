#pragma once

#include "Bh1750Sensor.h"
#include "Bmp180Sensor.h"
#include "Ltr390Sensor.h"
#include "Sht40Sensor.h"
#include "weather_data.h"

class SensorManager
{
public:
    void begin();
    void read();
    void readAndPrint();
    WeatherData& data();
    const SensorDiagnostic sht4xDiagnostic() const;
    const SensorDiagnostic bmp180Diagnostic() const;
    const SensorDiagnostic bh1750Diagnostic() const;
    const SensorDiagnostic ltr390Diagnostic() const;

private:
    void printBeginStatus(const SensorDiagnostic& diagnostic);
    void printReadStatus(const SensorDiagnostic& diagnostic);
    void printDiagnosticSummary(const SensorDiagnostic& diagnostic);
    static void updateHealth(SensorHealth& health, const SensorDiagnostic& diagnostic);

    WeatherData weatherData_ = {};
    Sht40Sensor sht40_;
    Bmp180Sensor bmp180_;
    Bh1750Sensor bh1750_;
    Ltr390Sensor ltr390_;
};

