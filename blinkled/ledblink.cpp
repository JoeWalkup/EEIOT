#include "ledblink.h"

LEDController::LEDController(int pin){
    ledPin = pin;
    isOn = false;
    previousMillis = 0;
}

void LEDController::begin(){
    pinMode(ledPin, OUTPUT);
    turnOff();
}

void LEDController::turnOn() {
    digitalWrite(ledPin, HIGH);
    isOn = true;
}

void LEDController::turnOff() {
    isOn = false;
}

void LEDController::toggle(){
    if (isOn) {
        turnOff();
    } else {
        turnOn();
    }
}

void LEDController::blink(int interval) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        toggle();
        previousMillis = currentMillis;
    }
}
