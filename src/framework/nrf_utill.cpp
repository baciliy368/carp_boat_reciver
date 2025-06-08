#include "nrf_utill.h"

RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);
uint8_t address[][6] = {"1Node", "2Node"};
bool role = false;
bool radioNumber = 1;

void sendMessage(MessageData messageData)
{
  radio.write(&messageData, sizeof(MessageData));
}

MessageData waitResponse()
{
  uint8_t pipe;
  MessageData messageData;
  radio.startListening();
  while (!radio.available(&pipe))
  {
    // ждать данные
  }
  if (radio.available(&pipe))
  {
    uint8_t bytes = radio.getPayloadSize();
    radio.read(&messageData, bytes);
  }
  radio.stopListening();
  return messageData;
}

void prepareRfnListener()
{
  if (!radio.begin())
  {
    Serial.println(F("radio hardware is not responding!!"));
    while (1)
    {
    } // hold in infinite loop
  }
  radioNumber = 0 == 1;
  radio.setPALevel(RF24_PA_HIGH);  // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

  radio.setPayloadSize(24); // размер пакета, в байтах

  radio.openWritingPipe(address[radioNumber]);     // хотим слушать трубу 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  radio.startListening();
}

void prepareRfn()
{
  if (!radio.begin())
  {
    Serial.println(F("radio hardware is not responding!!"));
    while (1)
    {
    } // hold in infinite loop
  }
  radioNumber = 1 == 1;
  radio.setPALevel(RF24_PA_HIGH);  // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS); // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS

  radio.setPayloadSize(24); // размер пакета, в байтах

  radio.openWritingPipe(address[radioNumber]);     // хотим слушать трубу 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  radio.stopListening(); // не слушаем радиоэфир, мы передатчик
}

void waitMessageWithOperationType()
{
  if ((millis() - last_message_milis > 250) && !IS_STOPPED)
  {
    stop();
    IS_STOPPED = true;
  }
  uint8_t pipe;
  
  if (radio.available(&pipe))
  {
    MessageData messageData;                       // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();        // get the size of the payload
    radio.read(&messageData, sizeof(MessageData)); // fetch payload from FIFO
    switch (messageData.operation_type)
    {
    case 15:
      engineInterface(messageData.joystickX, messageData.joystickY);
      IS_STOPPED = false;
      break;
    case 16:
      stop();
      IS_STOPPED = true;
      break;
    case 5:
      radio.stopListening();
      lastTransmitterSendTime = millis();
      boatInfoTransmitter = true;
      break;
    case 45:
    case 46:
    case 47:
    case 48:
      servoAction(messageData.operation_type);
      break;
    case 25:
      if (isWiFiEnabled())
      {
        startWiFi();
      }
      else
      {
        disableWifi();
      }
      break;
    default:
      break;
    }
    last_message_milis = millis();
  }
}

void sendDataToController()
{
  if (millis() - lastTransmitterSendTime <= TRANSMITTER_WAIT_TIME)
  {
    MessageData messageData = getBoatInfoMessageData();
    radio.write(&messageData, sizeof(MessageData));
  }
  else
  {
    radio.startListening();
    delay(500);
    boatInfoTransmitter = false;
  }
}
