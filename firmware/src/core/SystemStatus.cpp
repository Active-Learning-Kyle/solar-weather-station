#include "SystemStatus.h"

#include "FirmwareInfo.h"
#include "NetworkManager.h"
#include "SerialPrintManager.h"

#include <time.h>

namespace Core
{
void SystemStatus::print()
{
    SerialPrintManager::Lock serialLock;

    Serial.println("----- System Status -----");
    Serial.print("Firmware: ");
    Serial.println(FirmwareInfo::version());
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" s");
    Serial.print("Free heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    Serial.print("WiFi: ");
    Serial.println(NetworkManager::isWiFiConnected() ? "connected" : "disconnected");

    if (NetworkManager::isWiFiConnected())
    {
        Serial.print("IP: ");
        Serial.println(NetworkManager::ipAddress());
        Serial.print("RSSI: ");
        Serial.print(NetworkManager::rssi());
        Serial.println(" dBm");
    }

    Serial.print("NTP time: ");
    Serial.println(NetworkManager::isTimeSynced() ? "synced" : "not synced");

    struct tm timeInfo;
    if (NetworkManager::isTimeSynced() && getLocalTime(&timeInfo, 100))
    {
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
        Serial.print("Local time: ");
        Serial.println(buffer);
    }

    Serial.println("-------------------------");
}
}
