#pragma once

#include <Arduino.h>

namespace Core
{
class SerialPrintManager
{
public:
    class Lock
    {
    public:
        explicit Lock(TickType_t timeout = portMAX_DELAY);
        ~Lock();

        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;

    private:
        bool locked_ = false;
    };

    static void begin();
    static bool lock(TickType_t timeout = portMAX_DELAY);
    static void unlock();

private:
    static SemaphoreHandle_t mutex_;
};
}

