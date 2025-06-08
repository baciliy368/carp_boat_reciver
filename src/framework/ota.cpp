#include <framework/ota.h>

SerialWiFiBridge bridge;

bool isWiFiEnabled()
{
  return WiFi.status() != WL_CONNECTED;
}

void startWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin("dog_room", "NGHaUH8H88");
  Serial.println("start connection");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  bridge.begin("dog_room", "NGHaUH8H88");
  bridge.println("Wi-Fi Serial bridge started");
  Serial.println(WiFi.localIP());
}

void otaLogic()
{
  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      bridge.println("Start updating " + type); })
      .onEnd([]()
             { bridge.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { bridge.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
      bridge.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        bridge.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        bridge.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        bridge.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        bridge.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        bridge.println("End Failed");
      } });

  ArduinoOTA.begin();
}

void disableWifi()
{
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}