#pragma once

#include <Arduino.h>

// Minimal, checksum-validated NMEA inspection used only to recover hemisphere
// signs that DFRobot_GNSS 1.0.0 does not return reliably over UART. This is not
// a replacement for the official library's structured GNSS getters.
class GnssNmeaHemisphere
{
public:
    void encode(char value);

    bool hasLatitude() const;
    bool hasLongitude() const;
    bool hasBoth() const;
    char latitude() const;
    char longitude() const;
    uint32_t validSentenceCount() const;
    uint32_t fixSentenceCount() const;
    uint32_t checksumFailureCount() const;

private:
    void parseSentence();
    void acceptDirections(const char* latitudeField,
                          const char* longitudeField);
    static int8_t hexValue(char value);

    static constexpr size_t SentenceCapacity = 128;
    char sentence_[SentenceCapacity] = {};
    size_t sentenceLength_ = 0;
    bool collecting_ = false;
    char latitudeHemisphere_ = '\0';
    char longitudeHemisphere_ = '\0';
    uint32_t validSentenceCount_ = 0;
    uint32_t fixSentenceCount_ = 0;
    uint32_t checksumFailureCount_ = 0;
};
