#include <servo_controller.h>
Servo servoHolder_1;

void prepareServos() {
  servoHolder_1.attach(22, 500, 2400);
  servoHolder_1.write(0);
}

void servoPosition(int releasePosition, int finalPosition)
{
    servoHolder_1.write(releasePosition);
    delay(2000);
    servoHolder_1.write(finalPosition);
}

void servoPosition(int position)
{
    servoHolder_1.write(position);
}

void servoAction(uint8_t code)
{
    switch(code){
        case 45:
            servoPosition(RELEASE_DEGREE);
            break;
        case 46:
            servoPosition(DEFAULT_DEGREE);
            break;
        case 47:
            servoPosition(RELEASE_DEGREE, DEFAULT_DEGREE);
            break;
        case 48:
            servoPosition(RELEASE_DEGREE, DEFAULT_DEGREE);
            break;
    }
}



void releaseServo()
{
    servoHolder_1.write(180);
    delay(2000);
    servoHolder_1.write(0);
}
