#include "boat_info.h"
#include "framework/ota.h"
#include "framework/gps.h"
float getBatteryValue()
{
    return 12.35;
}

MessageData getBoatInfoMessageData()
{
    MessageData messageData;

    messageData.battery_voltage = getBatteryValue();
    messageData.wifi = isWiFiEnabled();

    messageData.latitude = getLatitude();
    messageData.longitude = getLongitude();
    
    return messageData;
}