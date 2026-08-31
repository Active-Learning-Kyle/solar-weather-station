#include "WeatherDataSerializer.h"

#include "app_config.h"
#include "core/FirmwareInfo.h"
#include "core/NetworkManager.h"

#include <ArduinoJson.h>
#include <DFRobot_GNSS.h>
#include <time.h>

namespace
{
bool valid(const SensorHealth& health, uint32_t nowMs)
{
    return health.initialized && health.latestValueValid &&
           health.lastSuccessfulReadMs != 0 &&
           (nowMs - health.lastSuccessfulReadMs) <= AppConfig::SensorStaleAfterMs;
}

void addHealth(JsonObject target, const SensorHealth& health, uint32_t nowMs)
{
    const bool isStale = health.lastSuccessfulReadMs == 0 ||
                         (nowMs - health.lastSuccessfulReadMs) > AppConfig::SensorStaleAfterMs;
    target["initialized"] = health.initialized;
    target["valid"] = valid(health, nowMs);
    target["stale"] = isStale;
    target["consecutive_failures"] = health.consecutiveFailures;
    target["total_failures"] = health.totalFailures;
}

template <typename T>
void valueOrNull(JsonObject target, const char* key, T value, bool isValid)
{
    if (isValid)
        target[key] = value;
    else
        target[key] = nullptr;
}

const char* gnssStateText(GnssState state)
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
    return "NOT CONNECTED";
}

const char* gnssModeText(uint8_t mode)
{
    switch (mode)
    {
    case eGPS:
        return "GPS";
    case eBeiDou:
        return "BeiDou";
    case eGPS_BeiDou:
        return "GPS + BeiDou";
    case eGLONASS:
        return "GLONASS";
    case eGPS_GLONASS:
        return "GPS + GLONASS";
    case eBeiDou_GLONASS:
        return "BeiDou + GLONASS";
    case eGPS_BeiDou_GLONASS:
        return "GPS + BeiDou + GLONASS";
    default:
        return nullptr;
    }
}

const char* windStatusText(const WeatherData& data, uint32_t nowMs)
{
    constexpr uint8_t ModbusResponseTimedOut = 0xE2;
    const SensorHealth& health = data.windSpeedHealth;
    if (!health.initialized)
        return "NOT CONNECTED";
    if (health.latestValueValid && health.lastSuccessfulReadMs != 0 &&
        nowMs - health.lastSuccessfulReadMs > AppConfig::SensorStaleAfterMs)
        return "STALE";
    if (health.latestValueValid)
        return "OK";
    if (data.windSpeedLastModbusResult == ModbusResponseTimedOut)
        return "TIMEOUT";
    return "CHECK";
}
}

String WeatherDataSerializer::toJson(const WeatherData& data, uint32_t nowMs)
{
    JsonDocument document;
    document["schema_version"] = "weather.measurement.v1";
    document["station_id"] = AppConfig::StationId;
    document["firmware_version"] = Core::FirmwareInfo::version();
    document["uptime_ms"] = data.uptimeMs;

    if (Core::NetworkManager::isTimeSynced())
    {
        time_t currentTime = time(nullptr);
        struct tm utcTime;
        gmtime_r(&currentTime, &utcTime);
        char timestamp[25];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", &utcTime);
        document["device_timestamp"] = timestamp;
    }
    else
        document["device_timestamp"] = nullptr;

    const bool shtValid = valid(data.sht4xHealth, nowMs);
    const bool bmpValid = valid(data.bmp180Health, nowMs);
    const bool lightValid = valid(data.bh1750Health, nowMs);
    const bool uvValid = valid(data.ltr390Health, nowMs);
    const bool pmsValid = valid(data.pms7003Health, nowMs);
    const bool windValid = valid(data.windSpeedHealth, nowMs);

    JsonObject environment = document["environment"].to<JsonObject>();
    valueOrNull(environment, "temperature_c", data.temperature, shtValid);
    valueOrNull(environment, "humidity_percent", data.humidity, shtValid);
    valueOrNull(environment, "pressure_hpa", data.pressure, bmpValid);
    valueOrNull(environment, "light_lux", data.lightLux, lightValid);
    valueOrNull(environment, "uv_index", data.uvIndex, uvValid);

    JsonObject particulate = document["particulate"].to<JsonObject>();
    valueOrNull(particulate, "pm1_ugm3", data.pm1_0, pmsValid);
    valueOrNull(particulate, "pm25_ugm3", data.pm2_5, pmsValid);
    valueOrNull(particulate, "pm10_ugm3", data.pm10, pmsValid);

    JsonObject wind = document["wind"].to<JsonObject>();
    valueOrNull(wind, "speed_mps", data.windSpeed, windValid);
    wind["status"] = windStatusText(data, nowMs);
    wind["last_modbus_result"] = data.windSpeedLastModbusResult;

    JsonObject gnss = document["gnss"].to<JsonObject>();
    gnss["state"] = gnssStateText(data.gnssState);
    gnss["communication_ok"] = data.gnssCommunicationOk;
    gnss["fix_valid"] = data.gnssFixValid;
    if (data.gnssUtcValid)
    {
        char utc[25];
        snprintf(utc, sizeof(utc), "%04u-%02u-%02uT%02u:%02u:%02uZ",
                 data.gnssYear, data.gnssMonth, data.gnssDay,
                 data.gnssHour, data.gnssMinute, data.gnssSecond);
        gnss["utc"] = utc;
    }
    else
        gnss["utc"] = nullptr;
    valueOrNull(gnss, "latitude", data.latitude, data.gnssFixValid);
    valueOrNull(gnss, "longitude", data.longitude, data.gnssFixValid);
    valueOrNull(gnss, "altitude_m", data.altitude,
                data.gnssFixValid && isfinite(data.altitude));
    valueOrNull(gnss, "satellites", data.gnssSatellites,
                data.gnssCommunicationOk);
    valueOrNull(gnss, "speed_kmph", data.gnssSpeedKmph,
                data.gnssFixValid && isfinite(data.gnssSpeedKmph));
    valueOrNull(gnss, "course_deg", data.gnssCourseDeg,
                data.gnssFixValid && isfinite(data.gnssCourseDeg));
    const char* mode = gnssModeText(data.gnssMode);
    if (mode != nullptr)
        gnss["mode"] = mode;
    else
        gnss["mode"] = nullptr;
    valueOrNull(gnss, "last_successful_fix_ms", data.gnssLastSuccessfulFixMs,
                data.gnssLastSuccessfulFixMs != 0);

    JsonObject health = document["health"].to<JsonObject>();
    addHealth(health["sht4x"].to<JsonObject>(), data.sht4xHealth, nowMs);
    addHealth(health["bmp180"].to<JsonObject>(), data.bmp180Health, nowMs);
    addHealth(health["bh1750"].to<JsonObject>(), data.bh1750Health, nowMs);
    addHealth(health["ltr390"].to<JsonObject>(), data.ltr390Health, nowMs);
    addHealth(health["pms7003"].to<JsonObject>(), data.pms7003Health, nowMs);
    addHealth(health["wind_speed"].to<JsonObject>(), data.windSpeedHealth, nowMs);

    String json;
    serializeJson(document, json);
    return json;
}
