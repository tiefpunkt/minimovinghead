#include <LXESP8266UARTDMX.h>

#define PIN_RED 14
#define PIN_GREEN 12
#define PIN_BLUE 13

#define PIN_SERVO1 4
#define PIN_SERVO2 5

#define STROBE_FREQ_MIN 1
#define STROBE_FREQ_MAX 20

#define STROBE_INTERVAL_MAX 1000 / STROBE_FREQ_MIN / 2
#define STROBE_INTERVAL_MIN 1000 / STROBE_FREQ_MAX / 2

int strobe_interval = 0;
long last_strobe = 0;
byte strobe_state = 0;

int red = 1023;
int green = 1023;
int blue = 1023;

#include <Servo.h> 
Servo servo1;
Servo servo2;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  analogWrite(PIN_RED,1023);
  analogWrite(PIN_GREEN,1023);
  analogWrite(PIN_BLUE,1023);

  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO1);
  
  ESP8266DMX.setDataReceivedCallback(&gotDMXCallback);
  delay(1000);
  ESP8266DMX.startInput();
}

void gotDMXCallback(int slots) {
  red = 4*(255 - ESP8266DMX.getSlot(1));
  green = 4*(255 - ESP8266DMX.getSlot(2));
  blue = 4*(255 - ESP8266DMX.getSlot(3));

  int i = ESP8266DMX.getSlot(4);
  if (i <= 10) {
    strobe_interval = 0;
  } else {
    strobe_interval = map(i, 11,255, STROBE_INTERVAL_MAX, STROBE_INTERVAL_MIN);
  }

  servo1.write(ESP8266DMX.getSlot(5)*180/256);
  servo2.write(ESP8266DMX.getSlot(6)*180/256);
}

void loop() {
  if (strobe_interval == 0) {
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN,green);
    analogWrite(PIN_BLUE,blue);
  } else {
    if (millis()-last_strobe > strobe_interval) {
      if (strobe_state == 0) {
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GREEN,green);
        analogWrite(PIN_BLUE,blue);
        strobe_state = 1;
      } else {
        analogWrite(PIN_RED, 1023);
        analogWrite(PIN_GREEN,1023);
        analogWrite(PIN_BLUE,1023);
        strobe_state = 0;
      }
      last_strobe = millis();
    }
  }
}
