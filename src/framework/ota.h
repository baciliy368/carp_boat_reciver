#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <varaibles.h>
#include <framework/wifi_serial.h>


void startWiFi();
void otaLogic();
void disableWifi();
bool isWiFiEnabled();

extern SerialWiFiBridge bridge;