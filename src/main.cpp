#include <Arduino.h>
#include <framework/nrf_utill.h>
#include <motion_controller.h>
#include <framework/ota.h>
#include <framework/gps.h>
#include <servo_controller.h>

void setup()
{
  Serial.begin(115200);
  prepareServos();
  prepareRfnListener();
  prepareDriver();
  prepareGPS();
  startWiFi();
  otaLogic();
}

void loop()
{
  if (!boatInfoTransmitter)
  {
    waitMessageWithOperationType();
  }
  else
  {
    sendDataToController();
  }
  ArduinoOTA.handle();
  bridge.handle();
}