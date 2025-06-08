#include "varaibles.h"

MessageData currentBoatInfo;
bool boatInfoTransmitter;
uint16_t lastTransmitterSendTime = 0;
unsigned long last_message_milis = 0;
bool IS_STOPPED;

uint8_t LAST_UPDATE_DURATION;
