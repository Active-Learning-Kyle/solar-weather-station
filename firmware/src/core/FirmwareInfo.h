#pragma once

#include <Arduino.h>

namespace Core
{
class FirmwareInfo
{
public:
    static const char* version();
    static void printBootBanner();
};
}

