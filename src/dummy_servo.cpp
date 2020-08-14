#include "dummy_servo.h"

using namespace smartdumpster;

DummyServo::DummyServo() {
    this->angle = 30;
}

int DummyServo::getAngle() {
    return this->angle;
}

void DummyServo::setAngle(int angle) {
    this->angle = angle;
}

int DummyServo::getAngleMin() {
    return 30;
}

int DummyServo::getAngleMax() {
    return 130;
}
