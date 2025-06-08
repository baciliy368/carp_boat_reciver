#include "wifi_serial.h"

SerialWiFiBridge::SerialWiFiBridge(uint16_t port)
    : server(port), client() {}

void SerialWiFiBridge::begin(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi connected: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void SerialWiFiBridge::handle() {
    if (!client || !client.connected()) {
        client = server.available();
        return;
    }

    // Не читаем клиент, только пишем в него
}

bool SerialWiFiBridge::isClientConnected() {
    return client.connected();  // теперь можно
}

IPAddress SerialWiFiBridge::getLocalIP() const {
    return WiFi.localIP();
}

size_t SerialWiFiBridge::write(uint8_t b) {
    Serial.write(b);
    if (client && client.connected()) client.write(b);
    return 1;
}

size_t SerialWiFiBridge::write(const uint8_t* buffer, size_t size) {
    Serial.write(buffer, size);
    if (client && client.connected()) client.write(buffer, size);
    return size;
}
