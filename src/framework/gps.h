#ifndef __GPS_H__
#include "varaibles.h"
#include <TinyGPS++.h>
MessageData getBoatInfoMessageData();
void prepareGPS();
float getLatitude();
float getLongitude();
#endif // __GPS_H__