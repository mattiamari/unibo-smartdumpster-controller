#ifndef SMARTDUMPSTER_DUMMY_SERVO_H
#define SMARTDUMPSTER_DUMMY_SERVO_H

#include "servo.h"

namespace smartdumpster {
    class DummyServo : public Servo
    {
    public:
        DummyServo();
        void setAngle(int angle);
        int getAngle();
        int getAngleMin();
        int getAngleMax();

    private:
        int angle;
    };
}

#endif