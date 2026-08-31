#pragma once

#include <stdint.h>

// Central compile-time configuration for the current hardware milestone.
namespace AppConfig
{
constexpr const char* StationId = "ws-esp32s3-001";
constexpr const char* FirmwareName = "IoT Solar Weather Station - Core v0.4";

constexpr uint32_t SerialBaud = 115200;
constexpr uint32_t I2cClockHz = 100000;
constexpr uint32_t EnvironmentalPeriodMs = 5000;
constexpr uint32_t PmsPeriodMs = 10000;
constexpr uint32_t SnapshotPeriodMs = 10000;
constexpr uint32_t UploadPeriodMs = 60000;
constexpr uint32_t PmsReadTimeoutMs = 1500;
constexpr uint32_t SensorStaleAfterMs = 30000;
constexpr uint32_t GnssUpdatePeriodMs = 10000;
constexpr uint32_t GnssFixStaleAfterMs = 30000;
constexpr uint32_t GnssCommunicationTimeoutMs = 30000;
constexpr uint32_t GnssProbeRetryPeriodMs = 60000;
constexpr uint32_t WindSpeedPeriodMs = 2000;
constexpr uint32_t WifiConnectTimeoutMs = 15000;
constexpr uint32_t WifiRetryPeriodMs = 30000;
constexpr uint32_t HttpConnectTimeoutMs = 3000;
constexpr uint32_t HttpReadTimeoutMs = 5000;

constexpr bool EnableI2cSensors = true;
constexpr bool EnablePms7003 = true;
constexpr bool EnableGnss = true;
constexpr bool EnableRs485Wind = true;
constexpr bool EnableRain = false;
constexpr bool EnablePowerTelemetry = false;
constexpr bool EnableWifi = true;

namespace Uart
{
constexpr int PmsPort = 2;
constexpr uint32_t PmsBaud = 9600;
constexpr int GnssPort = 1;
constexpr uint32_t GnssBaud = 9600;

// The verified standalone diagnostic uses UART1. Production overrides this to
// UART0 while its debug Serial console runs over native USB CDC, leaving UART1
// for GNSS and UART2 for PMS7003.
#ifndef WIND_SPEED_UART_PORT
#define WIND_SPEED_UART_PORT 1
#endif
constexpr int WindSpeedPort = WIND_SPEED_UART_PORT;
constexpr int WindDirectionPort = 2;
constexpr uint32_t WindBaud = 4800;
}

constexpr float RainMmPerTip = 0.2794f;
}

