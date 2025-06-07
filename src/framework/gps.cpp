#include "gps.h"

TinyGPSPlus GPS;

float getLatitude()
{
    RawDegrees lngRaw = GPS.location.rawLng();
    return (float)lngRaw.deg + (lngRaw.billionths / 1e9f);
}

float getLongitude()
{
    RawDegrees latRaw = GPS.location.rawLat();
    return (float)latRaw.deg + (latRaw.billionths / 1e9f);
}

void prepareGPS()
{
    Serial1.begin(GPS_PORT, SERIAL_8N1, 15, 2);
}
