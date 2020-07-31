#ifndef SMARTDUMPSTER_HW_SERVO_H
#define SMARTDUMPSTER_HW_SERVO_H

#include "servo.h"
#include <Arduino.h>
#include <Servo.h>

namespace smartdumpster {
    class HWServo : public Servo
    {
    public:
        HWServo(byte pin);
        void setAngle(int angle);
        int getAngle();
        int getAngleMin();
        int getAngleMax();

    private:
        ::Servo servo;
    };
}

#endif