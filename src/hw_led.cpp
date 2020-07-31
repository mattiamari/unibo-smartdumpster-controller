#include "hw_led.h"

using namespace smartdumpster;

HWLed::HWLed(byte pin) {
    this->pin = pin;
    ledState = false;
    pinMode(this->pin, OUTPUT);
}

bool HWLed::isOn() {
    return ledState;
}

void HWLed::turnOn() {
    digitalWrite(pin, HIGH);
    ledState = true;
}

void HWLed::turnOff() {
    digitalWrite(pin, LOW);
    ledState = false;
}

void HWLed::toggle() {
    if(isOn()) {
        turnOff();
        return;
    }
    turnOn();
}