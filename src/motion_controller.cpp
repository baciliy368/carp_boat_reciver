#include <motion_controller.h>

int pwmRate(int pwm)
{
  pwm = abs(pwm);
  pwm = constrain(pwm, 0, 100);

  if (pwm <= 20)
    return 100;

  return map(pwm, 20, 100, 80, 255);

  // // 255 - max
  // float pwm_percent = 0.0;
  // int minimal_effective_pwm = 100;
  // if (pwm == 0)
  // {
  //   return 255;
  // }
  // if (pwm / 4095.0 > 0.5)
  // {
  //   pwm_percent = (pwm / 4095.0 - 0.5) * 2;
  // }
  // else
  // {
  //   pwm_percent = (0.5 - (pwm / 4095.0)) * 2;
  // }
  // return minimal_effective_pwm + (255 - minimal_effective_pwm) * pwm_percent;
}

void prepareDriver()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1_left, OUTPUT);
  pinMode(in1_right, OUTPUT);
  pinMode(in2_left, OUTPUT);
  pinMode(in2_right, OUTPUT);
  // ledcAttachChannel(enA, freq, resolution, pwmChannel);
  // ledcAttachChannel(enB, freq, resolution, pwmChannel);
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enA, pwmChannel);

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enB, pwmChannel);
  // Turn off motors - Initial state
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1_left, LOW);
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_left, LOW);
  digitalWrite(in2_right, LOW);
}

void fristForward(int speed)
{
  Serial.print("fristForward ");
  Serial.println(speed);
  analogWrite(enA, speed);
  digitalWrite(in1_left, HIGH);
  digitalWrite(in1_right, LOW);
}

void secondForward(int speed)
{
  Serial.print("secondForward ");
  Serial.println(speed);
  analogWrite(enB, speed);
  digitalWrite(in2_left, LOW);
  digitalWrite(in2_right, HIGH);
}

void firstBackward(int speed)
{
  Serial.print("firstBackward ");
  Serial.println(speed);
  analogWrite(enA, speed);
  digitalWrite(in1_left, LOW);
  digitalWrite(in1_right, HIGH);
  ;
}

void secondBackward(int speed)
{
  Serial.print("secondBackward ");
  Serial.println(speed);
  analogWrite(enB, speed);
  digitalWrite(in2_left, HIGH);
  digitalWrite(in2_right, LOW);
}

void forwardLeft(int x, int y)
{
  fristForward(pwmRate(x) - 50);
  secondForward(pwmRate(y));
}

void forwardRight(int x, int y)
{
  fristForward(pwmRate(y));
  secondForward(pwmRate(x) - 50);
}

void backwardLeft(int x, int y)
{
  firstBackward(pwmRate(x) - 50);
  secondBackward(pwmRate(y));
}

void backwardRight(int x, int y)
{
  firstBackward(pwmRate(y));
  secondBackward(pwmRate(x) - 50);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(in1_left, LOW);
  digitalWrite(in1_right, LOW);

  digitalWrite(in2_left, LOW);
  digitalWrite(in2_right, LOW);
}

void forward(int y)
{
  fristForward(pwmRate(y));
  secondForward(pwmRate(y));
}

void backward(int y)
{
  firstBackward(pwmRate(y) * 0.7);
  secondBackward(pwmRate(y) * 0.7);
}

void left(int x)
{
  firstBackward(pwmRate(x));
  secondForward(pwmRate(x));
}

void right(int x)
{
  fristForward(pwmRate(x));
  secondBackward(pwmRate(x));
}

void engineInterface(int8_t x, int8_t y)
{
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("y: ");
  Serial.println(y);
  if (y > 0)
  { // если движение вперед
    // if(x>2200) {
    //   forwardRight(x, y); //если стик вправо
    // } else if(x<1700) {
    //   forwardLeft(x,  y); //если стик влево
    // } else {
    forward(y); // если стик прямо
    // }
  }
  else if (y < 0)
  { // если движение назад
    // if(x>2200) {
    //   backwardRight(x, y); //если стик вправо
    // } else if(x<1700) {
    //   backwardLeft(x, y); //если стик влево
    // } else {
    backward(y); // если стик прямо
    // }
  }
  else
  {
    if (x > 0)
    {
      right(x); // если стик вправо
    }
    else if (x < 0)
    {
      left(x); // если стик влево
    }
  }
  IS_STOPPED = false;
  last_message_milis = millis();
}
