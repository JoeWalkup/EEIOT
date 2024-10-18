#include <ledblink.h>

const int ledPin = 13;

LEDController led(ledPin);

void setup(){
  led.begin();
}

void loop() {
  led.blink(500);
}
