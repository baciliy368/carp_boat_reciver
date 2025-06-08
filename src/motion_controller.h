#ifndef __MOTION_CONTROLLER_H__
#include <Arduino.h>
#include <varaibles.h>
#include <HardwareSerial.h>
#include <ESP32Servo.h>
#include <framework/ota.h>

void prepareDriver();
void engineInterface(int8_t x, int8_t y);
void stop();

#endif // __MOTION_CONTROLLER_H__