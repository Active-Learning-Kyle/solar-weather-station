#include <Arduino.h>
#include <DFRobot_GNSS.h>

#include "app_config.h"
#include "pins.h"
#include "sensors/GnssNmeaHemisphere.h"

namespace
{
constexpr uint32_t StatusPeriodMs = 10000;
constexpr uint32_t RetryPeriodMs = 15000;
constexpr uint32_t RawCaptureDurationMs = 15000;
constexpr uint32_t RawPollPeriodMs = 3000;
constexpr uint8_t InitialAttempts = 3;
constexpr eGnssMode_t RequestedMode = eGPS_BeiDou_GLONASS;

HardwareSerial gnssSerial(AppConfig::Uart::GnssPort);
// DFRobot's public declaration takes RX then TX. Its implementation uses
// confusing internal names, but forwards argument 3 to HardwareSerial RX and
// argument 4 to HardwareSerial TX. Do not reverse these working project pins.
DFRobot_GNSS_UART gnss(&gnssSerial, AppConfig::Uart::GnssBaud,
                       Pins::GPS_RX, Pins::GPS_TX);

bool communicationOk = false;
uint32_t lastStatusMs = 0;
uint32_t lastRetryMs = 0;
String command;
uint32_t rawByteCount = 0;
bool rawCaptureActive = false;
uint32_t rawCaptureEndMs = 0;
uint32_t nextRawPollMs = 0;
GnssNmeaHemisphere nmeaHemisphere;

const char* modeText(uint8_t mode)
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
        return "unknown";
    }
}

double signedLatitude(const sLonLat_t& latitude, char hemisphere)
{
    return hemisphere == 'S' ? -latitude.latitudeDegree
                              : latitude.latitudeDegree;
}

double signedLongitude(const sLonLat_t& longitude, char hemisphere)
{
    return hemisphere == 'W' ? -longitude.lonitudeDegree
                              : longitude.lonitudeDegree;
}

bool validLatitudeMagnitude(const sLonLat_t& latitude)
{
    return latitude.latDD <= 90 && latitude.latMM < 60 &&
           latitude.latMMMMM < 100000 && isfinite(latitude.latitudeDegree) &&
           latitude.latitudeDegree >= 0.0 && latitude.latitudeDegree <= 90.0;
}

bool validLongitudeMagnitude(const sLonLat_t& longitude)
{
    return longitude.lonDDD <= 180 && longitude.lonMM < 60 &&
           longitude.lonMMMMM < 100000 &&
           isfinite(longitude.lonitudeDegree) &&
           longitude.lonitudeDegree >= 0.0 &&
           longitude.lonitudeDegree <= 180.0;
}

bool validDate(const sTim_t& date)
{
    return date.year >= 2000 && date.year <= 2099 && date.month >= 1 &&
           date.month <= 12 &&
           date.date >= 1 && date.date <= 31;
}

bool validUtcFields(const sTim_t& utc)
{
    // Midnight (00:00:00) is valid; never require a nonzero UTC component.
    return utc.hour <= 23 && utc.minute <= 59 && utc.second <= 60;
}

void printTwoDigits(uint8_t value)
{
    if (value < 10)
    {
        Serial.print('0');
    }
    Serial.print(value);
}

void printBootHeader()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("DIAGNOSTIC FIRMWARE - DFRobot Gravity GNSS");
    Serial.println("========================================");
    Serial.println("Module target: TEL0157 / Quectel L76K");
    Serial.println("Library: DFRobot_GNSS 1.0.0");
    Serial.println("Interface: UART (module selector must be UART)");
    Serial.print("UART number: ");
    Serial.println(AppConfig::Uart::GnssPort);
    Serial.print("Baud: ");
    Serial.println(AppConfig::Uart::GnssBaud);
    Serial.print("ESP32 RX: GPIO");
    Serial.println(Pins::GPS_RX);
    Serial.print("ESP32 TX: GPIO");
    Serial.println(Pins::GPS_TX);
    Serial.println("Stage A - UART initialization: starting");
}

bool detectAndConfigure()
{
    Serial.println("Stage B - DFRobot library communication: probing device");
    if (!gnss.begin())
    {
        communicationOk = false;
        Serial.println("GNSS DEVICE NOT DETECTED");
        Serial.println("Fix state: NO COMMUNICATION");
        return false;
    }

    communicationOk = true;
    Serial.println("GNSS communication: OK");
    Serial.println("Stage C - Module power/configuration");
    gnss.enablePower();
    Serial.println("Power enable command: SENT");
    gnss.setGnss(RequestedMode);
    const uint8_t mode = gnss.getGnssMode();
    Serial.print("GNSS mode readback: ");
    Serial.print(modeText(mode));
    Serial.print(" (");
    Serial.print(mode);
    Serial.println(")");
    if (mode != RequestedMode)
    {
        Serial.println("WARNING: requested GNSS mode was not confirmed");
    }
    Serial.println("Stage D - Periodic module data reads enabled");
    Serial.println("Commands: raw = 15 s raw GNSS/NMEA capture, status = read now, help");
    return true;
}

const char* fixState(bool fixValid)
{
    if (!communicationOk)
    {
        return "NO COMMUNICATION";
    }
    if (!fixValid)
    {
        return "COMMUNICATION OK - NO FIX";
    }
    return "FIX VALID";
}

void printDirection(const char direction)
{
    const uint8_t byteValue = static_cast<uint8_t>(direction);
    Serial.print("  direction byte: ");
    Serial.print(byteValue);
    Serial.print(" (0x");
    if (byteValue < 0x10)
    {
        Serial.print('0');
    }
    Serial.print(byteValue, HEX);
    Serial.println(')');
    Serial.print("  direction char: ");
    if (direction >= 32 && direction <= 126)
    {
        Serial.println(direction);
    }
    else
    {
        Serial.println("<not printable>");
    }
}

void printStatus()
{
    if (!communicationOk)
    {
        Serial.println("----------------------------------------");
        Serial.println("GNSS communication: FAILED");
        Serial.println("Fix state: NO COMMUNICATION");
        Serial.println("A bounded device probe will be retried; acquisition is not rebooted.");
        Serial.println("----------------------------------------");
        return;
    }

    // Refresh raw NMEA first. The callback silently extracts checksum-validated
    // N/S and E/W fields; raw text is printed only during the bounded raw mode.
    gnss.getAllGnss();
    const sTim_t utc = gnss.getUTC();
    const sTim_t date = gnss.getDate();
    const sLonLat_t latitude = gnss.getLat();
    const sLonLat_t longitude = gnss.getLon();
    const double altitude = gnss.getAlt();
    const uint8_t satellites = gnss.getNumSatUsed();
    const double speedKnots = gnss.getSog();
    const double courseDegrees = gnss.getCog();
    const uint8_t mode = gnss.getGnssMode();
    const bool utcFieldsValid = validUtcFields(utc);
    const bool dateIsValid = validDate(date);
    const bool timeIsValid = utcFieldsValid && dateIsValid;
    const bool latitudeIsValid = validLatitudeMagnitude(latitude);
    const bool longitudeIsValid = validLongitudeMagnitude(longitude);
    const bool positionIsValid = latitudeIsValid && longitudeIsValid;
    const bool fixIsValid =
        satellites > 0 && positionIsValid && timeIsValid;
    const bool dfrobotLatitudeDirectionValid =
        latitude.latDirection == 'N' || latitude.latDirection == 'S';
    const bool dfrobotLongitudeDirectionValid =
        longitude.lonDirection == 'E' || longitude.lonDirection == 'W';
    const char latitudeHemisphere =
        nmeaHemisphere.hasLatitude()
            ? nmeaHemisphere.latitude()
            : (dfrobotLatitudeDirectionValid ? latitude.latDirection : '\0');
    const char longitudeHemisphere =
        nmeaHemisphere.hasLongitude()
            ? nmeaHemisphere.longitude()
            : (dfrobotLongitudeDirectionValid ? longitude.lonDirection : '\0');
    const bool signedPositionValid =
        latitudeHemisphere != '\0' && longitudeHemisphere != '\0';

    Serial.println("========== DFRobot GNSS DIAGNOSTIC ==========");
    Serial.print("Elapsed: ");
    Serial.print(millis() / 1000);
    Serial.println(" s");
    Serial.println("Communication: OK");
    Serial.println("LED observation: external/manual");
    Serial.println();
    Serial.println("--- RAW DFRobot Getter Values ---");
    Serial.print("UTC raw: ");
    printTwoDigits(utc.hour);
    Serial.print(':');
    printTwoDigits(utc.minute);
    Serial.print(':');
    printTwoDigits(utc.second);
    Serial.println();
    Serial.print("Date raw: ");
    Serial.print(date.year);
    Serial.print('-');
    printTwoDigits(date.month);
    Serial.print('-');
    printTwoDigits(date.date);
    Serial.println();

    Serial.println("Latitude raw:");
    Serial.print("  latDD: ");
    Serial.println(latitude.latDD);
    Serial.print("  latMM: ");
    Serial.println(latitude.latMM);
    Serial.print("  latMMMMM: ");
    Serial.println(latitude.latMMMMM);
    Serial.print("  DDMM value (latitude): ");
    Serial.println(latitude.latitude, 7);
    Serial.print("  degree value (latitudeDegree): ");
    Serial.println(latitude.latitudeDegree, 7);
    printDirection(latitude.latDirection);
    Serial.print("  DFRobot direction valid: ");
    Serial.println(dfrobotLatitudeDirectionValid ? "YES" : "NO");

    Serial.println("Longitude raw:");
    Serial.print("  lonDDD: ");
    Serial.println(longitude.lonDDD);
    Serial.print("  lonMM: ");
    Serial.println(longitude.lonMM);
    Serial.print("  lonMMMMM: ");
    Serial.println(longitude.lonMMMMM);
    Serial.print("  DDDMM value (lonitude): ");
    Serial.println(longitude.lonitude, 7);
    Serial.print("  degree value (lonitudeDegree): ");
    Serial.println(longitude.lonitudeDegree, 7);
    printDirection(longitude.lonDirection);
    Serial.print("  DFRobot direction valid: ");
    Serial.println(dfrobotLongitudeDirectionValid ? "YES" : "NO");

    Serial.print("Altitude raw: ");
    Serial.println(altitude, 2);
    Serial.print("Satellites raw: ");
    Serial.println(satellites);
    Serial.print("SOG raw (knots): ");
    Serial.println(speedKnots, 2);
    Serial.print("COG raw (degrees): ");
    Serial.println(courseDegrees, 2);
    Serial.print("GNSS mode raw: ");
    Serial.print(mode);
    Serial.print(" (");
    Serial.print(modeText(mode));
    Serial.println(")");

    Serial.println();
    Serial.println("--- Interpretation ---");
    Serial.print("UTC fields in range: ");
    Serial.println(utcFieldsValid ? "YES" : "NO");
    Serial.print("Date valid: ");
    Serial.println(dateIsValid ? "YES" : "NO");
    Serial.print("Time valid (UTC fields + date): ");
    Serial.println(timeIsValid ? "YES" : "NO");
    Serial.print("Latitude valid: ");
    Serial.println(latitudeIsValid ? "YES" : "NO");
    Serial.print("Longitude valid: ");
    Serial.println(longitudeIsValid ? "YES" : "NO");
    Serial.print("Position data valid: ");
    Serial.println(positionIsValid ? "YES" : "NO");
    Serial.print("NMEA valid sentences observed: ");
    Serial.println(nmeaHemisphere.validSentenceCount());
    Serial.print("NMEA checksum failures: ");
    Serial.println(nmeaHemisphere.checksumFailureCount());
    Serial.print("NMEA latitude hemisphere: ");
    Serial.println(nmeaHemisphere.hasLatitude() ? nmeaHemisphere.latitude()
                                                : '?');
    Serial.print("NMEA longitude hemisphere: ");
    Serial.println(nmeaHemisphere.hasLongitude() ? nmeaHemisphere.longitude()
                                                 : '?');
    Serial.print("Signed coordinates available: ");
    Serial.println(signedPositionValid ? "YES" : "NO");
    Serial.println();
    Serial.println("--- Final interpreted values ---");
    if (latitudeIsValid && latitudeHemisphere != '\0')
    {
        const double finalLatitude =
            signedLatitude(latitude, latitudeHemisphere);
        Serial.print("Final latitude: ");
        if (finalLatitude >= 0.0)
        {
            Serial.print('+');
        }
        Serial.println(finalLatitude, 7);
    }
    else
    {
        Serial.println("Final latitude: unavailable (hemisphere unresolved)");
    }
    if (longitudeIsValid && longitudeHemisphere != '\0')
    {
        const double finalLongitude =
            signedLongitude(longitude, longitudeHemisphere);
        Serial.print("Final longitude: ");
        if (finalLongitude >= 0.0)
        {
            Serial.print('+');
        }
        Serial.println(finalLongitude, 7);
    }
    else
    {
        Serial.println("Final longitude: unavailable (hemisphere unresolved)");
    }
    Serial.print("Fix state: ");
    Serial.println(fixState(fixIsValid));
    Serial.println("==============================================");
}

void rawCallback(char* data, uint8_t length)
{
    for (uint8_t index = 0; index < length; ++index)
    {
        nmeaHemisphere.encode(data[index]);
    }
    if (rawCaptureActive)
    {
        rawByteCount += length;
        Serial.write(reinterpret_cast<const uint8_t*>(data), length);
    }
}

void startRawCapture()
{
    if (!communicationOk)
    {
        Serial.println("Raw NMEA unavailable: GNSS DEVICE NOT DETECTED");
        return;
    }

    rawCaptureActive = true;
    rawCaptureEndMs = millis() + RawCaptureDurationMs;
    nextRawPollMs = millis();
    rawByteCount = 0;
    Serial.println("----- 15 s raw GNSS/NMEA capture start -----");
    Serial.println("Data below comes from DFRobot getAllGnss()/callback:");
}

void serviceRawCapture()
{
    if (!rawCaptureActive)
    {
        return;
    }

    const uint32_t nowMs = millis();
    if (static_cast<int32_t>(nowMs - rawCaptureEndMs) >= 0)
    {
        rawCaptureActive = false;
        Serial.println();
        Serial.print("Raw bytes returned: ");
        Serial.println(rawByteCount);
        if (rawByteCount == 0)
        {
            Serial.println("No raw GNSS/NMEA bytes returned by the library");
        }
        Serial.println("----- raw GNSS/NMEA capture end --------");
        lastStatusMs = millis();
        return;
    }

    if (static_cast<int32_t>(nowMs - nextRawPollMs) >= 0)
    {
        gnss.getAllGnss();
        nextRawPollMs = millis() + RawPollPeriodMs;
    }
}

void handleCommand(const String& input)
{
    String normalized = input;
    normalized.trim();
    normalized.toLowerCase();
    if (normalized == "raw")
    {
        if (rawCaptureActive)
        {
            Serial.println("Raw capture is already active");
        }
        else
        {
            startRawCapture();
        }
    }
    else if (normalized == "status")
    {
        printStatus();
        lastStatusMs = millis();
    }
    else if (normalized == "help")
    {
        Serial.println("Commands: raw = 15 s raw GNSS/NMEA capture, status = read now, help");
    }
    else if (normalized.length() > 0)
    {
        Serial.println("Unknown command. Type help.");
    }
}

void pollConsole()
{
    while (Serial.available() > 0)
    {
        const char c = static_cast<char>(Serial.read());
        if (c == '\n' || c == '\r')
        {
            if (command.length() > 0)
            {
                handleCommand(command);
                command = "";
            }
        }
        else if (command.length() < 31)
        {
            command += c;
        }
    }
}
} // namespace

void setup()
{
    Serial.begin(AppConfig::SerialBaud);
    delay(800);
    printBootHeader();
    gnss.setCallback(rawCallback);

    for (uint8_t attempt = 1; attempt <= InitialAttempts && !communicationOk;
         ++attempt)
    {
        Serial.print("UART/device probe ");
        Serial.print(attempt);
        Serial.print('/');
        Serial.println(InitialAttempts);
        detectAndConfigure();
        if (!communicationOk && attempt < InitialAttempts)
        {
            delay(1000);
        }
    }

    Serial.println("Stage A - UART initialization: complete");
    printStatus();
    lastStatusMs = millis();
    lastRetryMs = lastStatusMs;
}

void loop()
{
    pollConsole();
    serviceRawCapture();
    const uint32_t nowMs = millis();

    if (!communicationOk && nowMs - lastRetryMs >= RetryPeriodMs)
    {
        lastRetryMs = nowMs;
        detectAndConfigure();
    }

    if (!rawCaptureActive && nowMs - lastStatusMs >= StatusPeriodMs)
    {
        lastStatusMs = nowMs;
        printStatus();
    }

    delay(5);
}
