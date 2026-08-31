#pragma once

#include <stdint.h>
#include "sensor_status.h"

enum class GnssState : uint8_t
{
    NotConnected,
    CommunicationOkNoFix,
    FixValid,
    FixStale
};

struct WeatherData
{
    // Values are meaningful only when the corresponding health entry reports
    // latestValueValid=true. Zero is therefore preserved as a valid reading.
    float temperature;
    float humidity;
    float pressure;
    int32_t pressurePa;
    float pressureSensorTemperature;
    float lightLux;
    uint32_t uvRaw;
    float uvIndex;
    float pm1_0;
    float pm2_5;
    float pm10;
    float pm1_0Standard;
    float pm2_5Standard;
    float pm10Standard;
    float pm1_0Atmospheric;
    float pm2_5Atmospheric;
    float pm10Atmospheric;
    float windSpeed;
    uint8_t windSpeedLastModbusResult;
    float windDirection;
    float rainfall;
    // GNSS numeric fields are meaningful only when their explicit validity
    // flags permit them. Serializers must emit null, never 0.0, for an
    // unavailable position.
    bool gnssCommunicationOk;
    bool gnssFixValid;
    bool gnssUtcValid;
    GnssState gnssState;
    uint16_t gnssYear;
    uint8_t gnssMonth;
    uint8_t gnssDay;
    uint8_t gnssHour;
    uint8_t gnssMinute;
    uint8_t gnssSecond;
    double latitude;
    double longitude;
    double altitude;
    uint8_t gnssSatellites;
    double gnssSpeedKmph;
    double gnssCourseDeg;
    uint8_t gnssMode;
    uint32_t gnssLastSuccessfulFixMs;
    uint32_t gnssBytesReceived;
    uint32_t gnssValidSentences;
    uint32_t gnssFailedChecksum;
    float batteryVoltage;
    float solarVoltage;
    uint64_t timestamp;
    uint32_t uptimeMs;

    SensorHealth sht4xHealth;
    SensorHealth bmp180Health;
    SensorHealth bh1750Health;
    SensorHealth ltr390Health;
    SensorHealth pms7003Health;
    SensorHealth windSpeedHealth;
};
