#include "GPSManager.h"

#include "core/SerialPrintManager.h"
#include "pins.h"

namespace
{
constexpr double KnotsToKmph = 1.852;
constexpr eGnssMode_t RequestedMode = eGPS_BeiDou_GLONASS;

bool due(uint32_t nowMs, uint32_t lastMs, uint32_t periodMs)
{
    return lastMs == 0 || nowMs - lastMs >= periodMs;
}

bool validDate(const sTim_t& date)
{
    return date.year >= 2000 && date.year <= 2099 && date.month >= 1 &&
           date.month <= 12 && date.date >= 1 && date.date <= 31;
}

bool validUtc(const sTim_t& utc)
{
    // Midnight is valid. Leap-second value 60 is also accepted.
    return utc.hour <= 23 && utc.minute <= 59 && utc.second <= 60;
}

bool validLatitudeMagnitude(const sLonLat_t& latitude)
{
    return isfinite(latitude.latitudeDegree) &&
           latitude.latitudeDegree >= 0.0 && latitude.latitudeDegree <= 90.0;
}

bool validLongitudeMagnitude(const sLonLat_t& longitude)
{
    return isfinite(longitude.lonitudeDegree) &&
           longitude.lonitudeDegree >= 0.0 && longitude.lonitudeDegree <= 180.0;
}
} // namespace

GPSManager* GPSManager::callbackOwner_ = nullptr;

GPSManager::GPSManager()
    : gpsSerial_(AppConfig::Uart::GnssPort),
      gnss_(&gpsSerial_, AppConfig::Uart::GnssBaud, Pins::GPS_RX, Pins::GPS_TX)
{
}

void GPSManager::begin(WeatherData& data)
{
    weatherData_ = &data;
    callbackOwner_ = this;
    gnss_.setCallback(gnssCallback);
    update();

    if (taskHandle_ == nullptr)
    {
        if (xTaskCreate(taskEntry, "gnss-worker", 6144, this, 1,
                        &taskHandle_) != pdPASS)
        {
            taskHandle_ = nullptr;
            Core::SerialPrintManager::Lock serialLock;
            Serial.println("GNSS worker creation failed; other subsystems remain active");
        }
    }
}

void GPSManager::update()
{
    if (weatherData_ == nullptr)
        return;

    portENTER_CRITICAL(&snapshotMutex_);
    const Snapshot current = snapshot_;
    portEXIT_CRITICAL(&snapshotMutex_);

    weatherData_->gnssCommunicationOk = current.communicationOk;
    weatherData_->gnssFixValid = current.fixValid;
    weatherData_->gnssUtcValid = current.utcValid;
    weatherData_->gnssState = current.state;
    weatherData_->gnssYear = current.year;
    weatherData_->gnssMonth = current.month;
    weatherData_->gnssDay = current.day;
    weatherData_->gnssHour = current.hour;
    weatherData_->gnssMinute = current.minute;
    weatherData_->gnssSecond = current.second;
    weatherData_->latitude = current.latitude;
    weatherData_->longitude = current.longitude;
    weatherData_->altitude = current.altitude;
    weatherData_->gnssSatellites = current.satellites;
    weatherData_->gnssSpeedKmph = current.speedKmph;
    weatherData_->gnssCourseDeg = current.courseDeg;
    weatherData_->gnssMode = current.mode;
    weatherData_->gnssLastSuccessfulFixMs = current.lastSuccessfulFixMs;
    weatherData_->gnssBytesReceived = current.bytesReceived;
    weatherData_->gnssValidSentences = current.validSentences;
    weatherData_->gnssFailedChecksum = current.failedChecksums;
}

void GPSManager::printStatus()
{
    update();
    if (weatherData_ == nullptr)
        return;

    Core::SerialPrintManager::Lock serialLock;
    Serial.print("GNSS: ");
    Serial.print(stateText(weatherData_->gnssState));
    Serial.print(" (satellites=");
    Serial.print(weatherData_->gnssSatellites);
    Serial.print(", mode=");
    Serial.print(weatherData_->gnssMode);
    Serial.print(", last_fix=");
    if (weatherData_->gnssLastSuccessfulFixMs == 0)
        Serial.print("never");
    else
    {
        Serial.print((millis() - weatherData_->gnssLastSuccessfulFixMs) / 1000);
        Serial.print(" s ago");
    }
    Serial.println(")");

    if (weatherData_->gnssFixValid)
    {
        Serial.print("  Position: ");
        Serial.print(weatherData_->latitude, 7);
        Serial.print(", ");
        Serial.print(weatherData_->longitude, 7);
        Serial.print(" at ");
        Serial.print(weatherData_->altitude, 1);
        Serial.println(" m");
    }
}

void GPSManager::taskEntry(void* parameter)
{
    static_cast<GPSManager*>(parameter)->taskLoop();
}

void GPSManager::taskLoop()
{
    for (;;)
    {
        const uint32_t nowMs = millis();
        if (!libraryStarted_ &&
            due(nowMs, lastProbeMs_, AppConfig::GnssProbeRetryPeriodMs))
        {
            lastProbeMs_ = nowMs;
            probeAndConfigure();
        }

        if (libraryStarted_ &&
            due(nowMs, lastReadMs_, AppConfig::GnssUpdatePeriodMs))
        {
            readModuleData();
        }

        refreshState(millis());
        publishSnapshot();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

bool GPSManager::probeAndConfigure()
{
    if (!gnss_.begin())
    {
        libraryStarted_ = false;
        return false;
    }

    libraryStarted_ = true;
    if (!configured_)
    {
        gnss_.enablePower();
        gnss_.setGnss(RequestedMode);
        configured_ = true;
    }
    readModuleData();
    return true;
}

void GPSManager::readModuleData()
{
    const uint32_t sentencesBefore = nmeaHemisphere_.validSentenceCount();
    const uint32_t fixesBefore = nmeaHemisphere_.fixSentenceCount();
    gnss_.getAllGnss();
    latestReadHadNmea_ = nmeaHemisphere_.validSentenceCount() > sentencesBefore;
    utc_ = gnss_.getUTC();
    date_ = gnss_.getDate();
    latitude_ = gnss_.getLat();
    longitude_ = gnss_.getLon();
    altitude_ = gnss_.getAlt();
    satellites_ = gnss_.getNumSatUsed();
    speedKnots_ = gnss_.getSog();
    courseDegrees_ = gnss_.getCog();
    gnssMode_ = gnss_.getGnssMode();
    lastReadMs_ = millis();

    latestReadHadFix_ = nmeaHemisphere_.fixSentenceCount() > fixesBefore &&
                        currentFixIsValid();
    if (latestReadHadFix_)
        lastSuccessfulFixMs_ = lastReadMs_;
}

void GPSManager::refreshState(uint32_t nowMs)
{
    const bool recentNmea = lastNmeaMs_ != 0 &&
                            nowMs - lastNmeaMs_ <= AppConfig::GnssCommunicationTimeoutMs;
    const bool communicationOk = libraryStarted_ && recentNmea;
    const bool currentFix = communicationOk && latestReadHadFix_ &&
                            lastSuccessfulFixMs_ != 0 &&
                            nowMs - lastSuccessfulFixMs_ <= AppConfig::GnssFixStaleAfterMs;

    GnssState state = GnssState::NotConnected;
    if (communicationOk)
    {
        if (currentFix)
            state = GnssState::FixValid;
        else if (lastSuccessfulFixMs_ != 0)
            state = GnssState::FixStale;
        else
            state = GnssState::CommunicationOkNoFix;
    }

    portENTER_CRITICAL(&snapshotMutex_);
    snapshot_.communicationOk = communicationOk;
    snapshot_.fixValid = currentFix;
    snapshot_.state = state;
    portEXIT_CRITICAL(&snapshotMutex_);
}

void GPSManager::publishSnapshot()
{
    const char latitudeHemisphere = nmeaHemisphere_.latitude();
    const char longitudeHemisphere = nmeaHemisphere_.longitude();

    portENTER_CRITICAL(&snapshotMutex_);
    if (latestReadHadFix_)
    {
        snapshot_.utcValid = true;
        snapshot_.year = date_.year;
        snapshot_.month = date_.month;
        snapshot_.day = date_.date;
        snapshot_.hour = utc_.hour;
        snapshot_.minute = utc_.minute;
        snapshot_.second = utc_.second;
        snapshot_.latitude = latitudeHemisphere == 'S'
                                 ? -latitude_.latitudeDegree
                                 : latitude_.latitudeDegree;
        snapshot_.longitude = longitudeHemisphere == 'W'
                                  ? -longitude_.lonitudeDegree
                                  : longitude_.lonitudeDegree;
        snapshot_.altitude = altitude_;
        snapshot_.speedKmph = speedKnots_ * KnotsToKmph;
        snapshot_.courseDeg = courseDegrees_;
    }
    snapshot_.satellites = satellites_;
    snapshot_.mode = gnssMode_;
    snapshot_.lastSuccessfulFixMs = lastSuccessfulFixMs_;
    snapshot_.bytesReceived = rawBytesReceived_;
    snapshot_.validSentences = nmeaHemisphere_.validSentenceCount();
    snapshot_.failedChecksums = nmeaHemisphere_.checksumFailureCount();
    portEXIT_CRITICAL(&snapshotMutex_);
}

void GPSManager::gnssCallback(char* data, uint8_t length)
{
    if (callbackOwner_ != nullptr)
        callbackOwner_->handleGnssData(data, length);
}

void GPSManager::handleGnssData(char* data, uint8_t length)
{
    rawBytesReceived_ += length;
    lastNmeaMs_ = millis();
    for (uint8_t index = 0; index < length; ++index)
        nmeaHemisphere_.encode(data[index]);
}

bool GPSManager::currentFixIsValid() const
{
    // Do not inspect DFRobot latDirection/lonDirection here: those fields are
    // malformed on the verified TEL0157/library combination. Hemisphere comes
    // exclusively from checksum-validated fix-bearing NMEA sentences.
    return satellites_ > 0 && validUtc(utc_) && validDate(date_) &&
           validLatitudeMagnitude(latitude_) &&
           validLongitudeMagnitude(longitude_) && nmeaHemisphere_.hasBoth();
}

const char* GPSManager::stateText(GnssState state)
{
    switch (state)
    {
    case GnssState::NotConnected:
        return "NOT CONNECTED";
    case GnssState::CommunicationOkNoFix:
        return "COMMUNICATION OK - NO FIX";
    case GnssState::FixValid:
        return "FIX VALID";
    case GnssState::FixStale:
        return "FIX STALE";
    }
    return "UNKNOWN";
}
