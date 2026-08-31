#include "NetworkManager.h"

#include "app_config.h"

#include <WiFi.h>
#include <time.h>

#if __has_include("secrets.h")
#include "secrets.h"
#else
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#endif

#ifndef NTP_SERVER
#define NTP_SERVER "pool.ntp.org"
#endif

#ifndef GMT_OFFSET_SECONDS
#define GMT_OFFSET_SECONDS 28800
#endif

#ifndef DAYLIGHT_OFFSET_SECONDS
#define DAYLIGHT_OFFSET_SECONDS 0
#endif

namespace Core
{
NetworkManager::State NetworkManager::state_ = NetworkManager::State::Disabled;
bool NetworkManager::timeSynced_ = false;
bool NetworkManager::ntpStarted_ = false;
uint32_t NetworkManager::stateChangedMs_ = 0;
uint32_t NetworkManager::lastNtpCheckMs_ = 0;

void NetworkManager::begin()
{
    if (!AppConfig::EnableWifi || WIFI_SSID[0] == '\0')
    {
        state_ = State::Disabled;
        Serial.println("Wi-Fi disabled: configure firmware/include/secrets.h to enable it");
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setAutoReconnect(false);
    startConnection();
}

void NetworkManager::startConnection()
{
    Serial.println("Wi-Fi connection attempt started");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    state_ = State::Connecting;
    stateChangedMs_ = millis();
}

void NetworkManager::startNtp()
{
    configTime(GMT_OFFSET_SECONDS, DAYLIGHT_OFFSET_SECONDS, NTP_SERVER);
    ntpStarted_ = true;
    lastNtpCheckMs_ = 0;
    Serial.println("NTP synchronization requested");
}

void NetworkManager::tick()
{
    if (state_ == State::Disabled)
    {
        return;
    }

    const uint32_t nowMs = millis();
    if (WiFi.status() == WL_CONNECTED)
    {
        if (state_ != State::Connected)
        {
            state_ = State::Connected;
            stateChangedMs_ = nowMs;
            Serial.print("Wi-Fi connected, IP: ");
            Serial.println(WiFi.localIP());
            startNtp();
        }

        if (ntpStarted_ && !timeSynced_ &&
            (lastNtpCheckMs_ == 0 || (nowMs - lastNtpCheckMs_) >= 1000))
        {
            lastNtpCheckMs_ = nowMs;
            time_t currentTime = time(nullptr);
            if (currentTime > 1700000000)
            {
                timeSynced_ = true;
                Serial.println("NTP time synchronized");
            }
        }
        return;
    }

    if (state_ == State::Connected)
    {
        state_ = State::Disconnected;
        stateChangedMs_ = nowMs;
        Serial.println("Wi-Fi disconnected; measurements continue");
    }

    if (state_ == State::Connecting &&
        (nowMs - stateChangedMs_) >= AppConfig::WifiConnectTimeoutMs)
    {
        WiFi.disconnect();
        state_ = State::RetryWait;
        stateChangedMs_ = nowMs;
        Serial.println("Wi-Fi attempt timed out; retry scheduled");
    }
    else if (state_ == State::Disconnected)
    {
        state_ = State::RetryWait;
        stateChangedMs_ = nowMs;
    }
    else if (state_ == State::RetryWait &&
             (nowMs - stateChangedMs_) >= AppConfig::WifiRetryPeriodMs)
    {
        startConnection();
    }
}

bool NetworkManager::isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

bool NetworkManager::isTimeSynced()
{
    return timeSynced_;
}

NetworkManager::State NetworkManager::state()
{
    return state_;
}

const char* NetworkManager::stateName()
{
    switch (state_)
    {
        case State::Disabled: return "DISABLED";
        case State::Connecting: return "CONNECTING";
        case State::Connected: return "CONNECTED";
        case State::Disconnected: return "DISCONNECTED";
        case State::RetryWait: return "RETRY_WAIT";
        default: return "UNKNOWN";
    }
}

const char* NetworkManager::ipAddress()
{
    static char ipBuffer[16];
    snprintf(ipBuffer, sizeof(ipBuffer), "%s", WiFi.localIP().toString().c_str());
    return ipBuffer;
}

int32_t NetworkManager::rssi()
{
    if (!isWiFiConnected())
    {
        return 0;
    }

    return WiFi.RSSI();
}
}
