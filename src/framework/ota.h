#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <varaibles.h>

void startWiFi();
void otaLogic();
void disableWifi();
bool isWiFiEnabled();