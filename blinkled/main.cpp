#include "ledblink.h"

const int ledPin = 16;

LEDController led(ledPin);

void setup(){
  led.begin();
}

void loop(){
  led.blink(500);
}
