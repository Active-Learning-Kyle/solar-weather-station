#pragma once

#include "app_config.h"
#include "sensors/GnssNmeaHemisphere.h"
#include "weather_data.h"

#include <Arduino.h>
#include <DFRobot_GNSS.h>

// Production TEL0157 owner. All DFRobot library calls run on a dedicated
// FreeRTOS task; update() only copies a short locked snapshot into WeatherData.
class GPSManager
{
public:
    GPSManager();

    void begin(WeatherData& data);
    void update();
    void printStatus();

private:
    struct Snapshot
    {
        bool communicationOk = false;
        bool fixValid = false;
        bool utcValid = false;
        GnssState state = GnssState::NotConnected;
        uint16_t year = 0;
        uint8_t month = 0;
        uint8_t day = 0;
        uint8_t hour = 0;
        uint8_t minute = 0;
        uint8_t second = 0;
        double latitude = 0.0;
        double longitude = 0.0;
        double altitude = 0.0;
        uint8_t satellites = 0;
        double speedKmph = 0.0;
        double courseDeg = 0.0;
        uint8_t mode = 0;
        uint32_t lastSuccessfulFixMs = 0;
        uint32_t bytesReceived = 0;
        uint32_t validSentences = 0;
        uint32_t failedChecksums = 0;
    };

    static void taskEntry(void* parameter);
    static void gnssCallback(char* data, uint8_t length);
    void taskLoop();
    bool probeAndConfigure();
    void readModuleData();
    void refreshState(uint32_t nowMs);
    void publishSnapshot();
    void handleGnssData(char* data, uint8_t length);
    bool currentFixIsValid() const;
    static const char* stateText(GnssState state);

    static GPSManager* callbackOwner_;

    HardwareSerial gpsSerial_;
    DFRobot_GNSS_UART gnss_;
    GnssNmeaHemisphere nmeaHemisphere_;
    WeatherData* weatherData_ = nullptr;
    TaskHandle_t taskHandle_ = nullptr;
    portMUX_TYPE snapshotMutex_ = portMUX_INITIALIZER_UNLOCKED;
    Snapshot snapshot_ = {};

    sTim_t utc_ = {};
    sTim_t date_ = {};
    sLonLat_t latitude_ = {};
    sLonLat_t longitude_ = {};
    double altitude_ = 0.0;
    double speedKnots_ = 0.0;
    double courseDegrees_ = 0.0;
    uint8_t satellites_ = 0;
    uint8_t gnssMode_ = 0;
    uint32_t lastProbeMs_ = 0;
    uint32_t lastReadMs_ = 0;
    uint32_t lastNmeaMs_ = 0;
    uint32_t lastSuccessfulFixMs_ = 0;
    uint32_t rawBytesReceived_ = 0;
    bool libraryStarted_ = false;
    bool configured_ = false;
    bool latestReadHadNmea_ = false;
    bool latestReadHadFix_ = false;
};
