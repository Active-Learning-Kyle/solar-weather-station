#pragma once

#include <Arduino.h>

namespace Core
{
class NetworkManager
{
public:
    enum class State
    {
        Disabled,
        Connecting,
        Connected,
        Disconnected,
        RetryWait
    };

    static void begin();
    static void tick();
    static bool isWiFiConnected();
    static bool isTimeSynced();
    static State state();
    static const char* stateName();
    static const char* ipAddress();
    static int32_t rssi();

private:
    static void startConnection();
    static void startNtp();

    static State state_;
    static bool timeSynced_;
    static bool ntpStarted_;
    static uint32_t stateChangedMs_;
    static uint32_t lastNtpCheckMs_;
};
}

