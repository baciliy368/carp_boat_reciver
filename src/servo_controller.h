#ifndef __SERVO_CONTROLLER_H__
#include <ESP32Servo.h>
#include <varaibles.h>

// servo items
extern Servo servoHolder_1;

void prepareServos();
void servoAction(uint8_t code);
void servoPosition(int releasePosition, int finalPosition);
void releaseServo();
#endif // __MOTION_CONTROLLER_H__