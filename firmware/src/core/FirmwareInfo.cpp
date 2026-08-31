#include "FirmwareInfo.h"

#ifndef FIRMWARE_VERSION
#define FIRMWARE_VERSION "0.0.0-dev"
#endif

namespace Core
{
const char* FirmwareInfo::version()
{
    return FIRMWARE_VERSION;
}

void FirmwareInfo::printBootBanner()
{
    Serial.println();
    Serial.println("Solar-Powered IoT Weather Station");
    Serial.print("Firmware version: ");
    Serial.println(version());
    Serial.print("Free heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
}
}

