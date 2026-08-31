#include "GnssNmeaHemisphere.h"

#include <stdlib.h>
#include <string.h>

void GnssNmeaHemisphere::encode(char value)
{
    if (value == '$')
    {
        collecting_ = true;
        sentenceLength_ = 0;
        sentence_[sentenceLength_++] = value;
        return;
    }

    if (!collecting_)
    {
        return;
    }

    if (value == '\r' || value == '\n' || value == '\0')
    {
        if (sentenceLength_ > 0)
        {
            sentence_[sentenceLength_] = '\0';
            parseSentence();
        }
        collecting_ = false;
        sentenceLength_ = 0;
        return;
    }

    if (sentenceLength_ < SentenceCapacity - 1)
    {
        sentence_[sentenceLength_++] = value;
    }
    else
    {
        collecting_ = false;
        sentenceLength_ = 0;
    }
}

bool GnssNmeaHemisphere::hasLatitude() const
{
    return latitudeHemisphere_ == 'N' || latitudeHemisphere_ == 'S';
}

bool GnssNmeaHemisphere::hasLongitude() const
{
    return longitudeHemisphere_ == 'E' || longitudeHemisphere_ == 'W';
}

bool GnssNmeaHemisphere::hasBoth() const
{
    return hasLatitude() && hasLongitude();
}

char GnssNmeaHemisphere::latitude() const
{
    return latitudeHemisphere_;
}

char GnssNmeaHemisphere::longitude() const
{
    return longitudeHemisphere_;
}

uint32_t GnssNmeaHemisphere::validSentenceCount() const
{
    return validSentenceCount_;
}

uint32_t GnssNmeaHemisphere::fixSentenceCount() const
{
    return fixSentenceCount_;
}

uint32_t GnssNmeaHemisphere::checksumFailureCount() const
{
    return checksumFailureCount_;
}

void GnssNmeaHemisphere::parseSentence()
{
    char* checksumMarker = strchr(sentence_, '*');
    if (checksumMarker == nullptr || checksumMarker[1] == '\0' ||
        checksumMarker[2] == '\0')
    {
        ++checksumFailureCount_;
        return;
    }

    uint8_t calculatedChecksum = 0;
    for (char* cursor = sentence_ + 1; cursor < checksumMarker; ++cursor)
    {
        calculatedChecksum ^= static_cast<uint8_t>(*cursor);
    }

    const int8_t highNibble = hexValue(checksumMarker[1]);
    const int8_t lowNibble = hexValue(checksumMarker[2]);
    if (highNibble < 0 || lowNibble < 0 ||
        calculatedChecksum !=
            static_cast<uint8_t>((highNibble << 4) | lowNibble))
    {
        ++checksumFailureCount_;
        return;
    }

    ++validSentenceCount_;
    *checksumMarker = '\0';

    const size_t MaxFields = 20;
    char* fields[MaxFields] = {};
    size_t fieldCount = 0;
    fields[fieldCount++] = sentence_;
    for (char* cursor = sentence_; *cursor != '\0' && fieldCount < MaxFields;
         ++cursor)
    {
        if (*cursor == ',')
        {
            *cursor = '\0';
            fields[fieldCount++] = cursor + 1;
        }
    }

    const size_t typeLength = strlen(fields[0]);
    if (typeLength < 3)
    {
        return;
    }
    const char* type = fields[0] + typeLength - 3;

    if (strcmp(type, "GGA") == 0 && fieldCount > 6 && atoi(fields[6]) > 0)
    {
        acceptDirections(fields[3], fields[5]);
    }
    else if (strcmp(type, "RMC") == 0 && fieldCount > 6 &&
             fields[2][0] == 'A')
    {
        acceptDirections(fields[4], fields[6]);
    }
    else if (strcmp(type, "GLL") == 0 && fieldCount > 6 &&
             fields[6][0] == 'A')
    {
        acceptDirections(fields[2], fields[4]);
    }
}

void GnssNmeaHemisphere::acceptDirections(const char* latitudeField,
                                           const char* longitudeField)
{
    const bool latitudeValid = latitudeField != nullptr &&
                               (latitudeField[0] == 'N' || latitudeField[0] == 'S');
    const bool longitudeValid = longitudeField != nullptr &&
                                (longitudeField[0] == 'E' || longitudeField[0] == 'W');
    if (latitudeValid)
    {
        latitudeHemisphere_ = latitudeField[0];
    }
    if (longitudeValid)
    {
        longitudeHemisphere_ = longitudeField[0];
    }
    if (latitudeValid && longitudeValid)
    {
        ++fixSentenceCount_;
    }
}

int8_t GnssNmeaHemisphere::hexValue(char value)
{
    if (value >= '0' && value <= '9')
    {
        return value - '0';
    }
    if (value >= 'A' && value <= 'F')
    {
        return value - 'A' + 10;
    }
    if (value >= 'a' && value <= 'f')
    {
        return value - 'a' + 10;
    }
    return -1;
}
