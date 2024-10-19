#ifndef LEDBLINK_H
#define LEDBLINK_H

#include <Arduino.h>

class LEDController {
public:
    LEDController(int pin);

    void begin();

    void turnOn();

    void turnOff();

    void toggle();

    void blink(int interval);

private:
    int ledPin;
    bool isOn;
    unsigned long previousMillis;
};

#endif
