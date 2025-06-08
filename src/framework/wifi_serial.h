#pragma once
#include <WiFi.h>
#include <Print.h>

class SerialWiFiBridge : public Print {
public:
    SerialWiFiBridge(uint16_t port = 23);

    void begin(const char* ssid, const char* password);
    void handle(); // вызывать в loop()

    bool isClientConnected();

    IPAddress getLocalIP() const;

    // Методы из Print
    size_t write(uint8_t b) override;
    size_t write(const uint8_t* buffer, size_t size) override;

private:
    WiFiServer server;
    WiFiClient client;
};
