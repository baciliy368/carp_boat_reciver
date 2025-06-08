#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <stdint.h>

#define NRF_CE_PIN 4
#define NRF_CSN_PIN 5

#define BAT_PIN 5
#define GPS_PORT 9600

#define ENC_A_PIN 33
#define ENC_B_PIN 25
#define ENC_BUTTON_PIN 32


extern uint8_t LAST_UPDATE_DURATION;

struct MessageData
{
  float latitude;        // 4 байта
  float longitude;       // 4 байта
  float battery_voltage; // 4 байта

  uint8_t operation_type; // 1 байт
  uint8_t wifi;           // 1 байт
  uint8_t maxSpeed;       // 1 байт
  int8_t joystickX;      // 1 байт

  int8_t joystickY;  // 1 байт
  uint8_t reserved1;  // 1 байт
  uint16_t reserved2; // 2 байта (выравнивание)

  // uint8_t reserved[16]; // 16 байт под расширение, crc и т.д.
};
extern bool boatInfoTransmitter;


// PWM items
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
const int in1_right = 26; // left
const int in1_left = 27;  // right
const int enA = 25;
const int in2_right = 14; // left
const int in2_left = 12;  // right
const int enB = 13;

#define OTA_UPDATE_INTERVAL 300
#define TRANSMITTER_WAIT_TIME 2000
extern uint16_t lastTransmitterSendTime;
extern const char MENU_POINTER;


extern unsigned long last_message_milis;
extern bool IS_STOPPED;
//sevo items
#define RELEASE_DEGREE 80
#define DEFAULT_DEGREE 0

#endif // __VARIABLES_H__