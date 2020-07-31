#include "hw_servo.h"

using namespace smartdumpster;

HWServo::HWServo(byte pin) {
    servo.attach(pin);
}

int HWServo::getAngle() {
    return servo.read();
}

void HWServo::setAngle(int angle) {
    servo.write(angle);
}

int HWServo::getAngleMin() {
    return 30;
}

int HWServo::getAngleMax() {
    return 130;
}
