#include <motion_controller.h>

int pwmRate(int pwm)
{
  pwm = abs(pwm);
  pwm = constrain(pwm, 0, 100);

  if (pwm <= 20)
    return 100;

  return map(pwm, 20, 100, 80, 255);
}

void prepareDriver()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1_left, OUTPUT);
  pinMode(in1_right, OUTPUT);
  pinMode(in2_left, OUTPUT);
  pinMode(in2_right, OUTPUT);
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
  bridge.print("fristForward ");
  bridge.println(speed);
  analogWrite(enA, speed);
  digitalWrite(in1_left, HIGH);
  digitalWrite(in1_right, LOW);
}

void secondForward(int speed)
{
  bridge.print("secondForward ");
  bridge.println(speed);
  analogWrite(enB, speed);
  digitalWrite(in2_left, LOW);
  digitalWrite(in2_right, HIGH);
}

void firstBackward(int speed)
{
  bridge.print("firstBackward ");
  bridge.println(speed);
  analogWrite(enA, speed);
  digitalWrite(in1_left, LOW);
  digitalWrite(in1_right, HIGH);
  ;
}

void secondBackward(int speed)
{
  bridge.print("secondBackward ");
  bridge.println(speed);
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
  bridge.println("stop");
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
  bridge.print("x: ");
  bridge.print(x);
  bridge.print("y: ");
  bridge.println(y);
  // стик влево
  if (x > 20)
  {
    // проверка вертикальной оси
    if (y >= 20)
    {
      // если вертикальная ось вперед
      forwardLeft(x, y);
    }
    else if (y <= -20)
    {
      // если вертикальная ось назад
      backwardLeft(x, y);
    }
    else
    {
      left(x);
    }
  }
  // стик вправо
  else if (x < -20)
  {
    // проверка вертикальной оси
    if (y >= 20)
    {
      // если вертикальная ось вперед
      forwardRight(x, y);
    }
    else if (y <= -20)
    {
      // если вертикальная ось назад
      backwardRight(x, y);
    }
    else
    {
      right(x);
    }
  }
  else
  {
    // если стик прямо
    if (y > 0)
    {
      forward(y);
    }
    // если стик прямо
    else if (y < 0)
    {
      backward(y);
    }
  }
}
