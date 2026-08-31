#include "SerialPrintManager.h"

namespace Core
{
SemaphoreHandle_t SerialPrintManager::mutex_ = nullptr;

SerialPrintManager::Lock::Lock(TickType_t timeout)
{
    locked_ = SerialPrintManager::lock(timeout);
}

SerialPrintManager::Lock::~Lock()
{
    if (locked_)
    {
        SerialPrintManager::unlock();
    }
}

void SerialPrintManager::begin()
{
    if (mutex_ == nullptr)
    {
        mutex_ = xSemaphoreCreateMutex();
    }
}

bool SerialPrintManager::lock(TickType_t timeout)
{
    begin();
    return mutex_ != nullptr && xSemaphoreTake(mutex_, timeout) == pdTRUE;
}

void SerialPrintManager::unlock()
{
    if (mutex_ != nullptr)
    {
        xSemaphoreGive(mutex_);
    }
}
}

