#ifndef SMARTDUMPSTER_HW_LED_H
#define SMARTDUMPSTER_HW_LED_H

#include "led.h"
#include <Arduino.h>

namespace smartdumpster
{
    class HWLed : public Led {
    public:
        HWLed(byte pin);
        bool isOn();
        void turnOn();
        void turnOff();
        void toggle();

    private:
        byte pin;
        bool ledState;
    };
}

#endif