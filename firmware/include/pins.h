#pragma once

namespace Pins
{
constexpr int I2C_SDA = 8;
constexpr int I2C_SCL = 9;

constexpr int PMS_RX = 16;
constexpr int PMS_TX = 17;
constexpr int PMS_SLEEP = 18;

constexpr int GPS_RX = 15;
constexpr int GPS_TX = 14;

constexpr int RS485_RX = 6;      // ESP32 RX, connected to MAX3485 TX
constexpr int RS485_TX = 7;      // ESP32 TX, connected to MAX3485 RX
constexpr int RS485_DE_RE = 5;   // connected to MAX3485 EN

constexpr int RAIN_PULSE = 4;

constexpr int SD_CS = 10;
constexpr int SPI_SCK = 12;
constexpr int SPI_MISO = 13;
constexpr int SPI_MOSI = 11;

constexpr int WIND_12V_ENABLE = 21;
constexpr int STATUS_LED = 2;

constexpr int BATTERY_ADC = 1;
constexpr int SOLAR_ADC = 3;
}
