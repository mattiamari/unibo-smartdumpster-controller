#include "controller.h"


using namespace smartdumpster;

Controller::Controller(Servo *servo, Led *leds[TRASH_TYPES_COUNT], BluetoothSerial *btSerial) {
    this->servo = servo;
    this->leds = leds;
    this->btSerial = btSerial;
}

void Controller::openLid(TrashType type) {
    leds[type - 1]->turnOn();
    currentState = STATE_OPENING;
}

void Controller::moreTime() {
    resetTimer();
}

void Controller::step() {
    switch (currentState) {
        case STATE_CLOSED: /* noop */ break;
        case STATE_OPENING: stateOpening(); break;
        case STATE_OPEN: stateOpen(); break;
        case STATE_CLOSING: stateClosing();
    }
}

bool Controller::isComplete() {
    return false;
}

ControllerState Controller::getState() {
    return currentState;
}

void Controller::stateOpening() {
    static unsigned int elapsed = 0;

    servo->setAngle(180);
    TASK_WAIT(elapsed, 1)
    resetTimer();
    btSerial->println("open");
    currentState = STATE_OPEN;
}

void Controller::stateOpen() {
    timeRemaining -= 1;

    if (timeRemaining == 0) {
        currentState = STATE_CLOSING;
    }
}

void Controller::stateClosing() {
    static unsigned int elapsed = 0;
    
    servo->setAngle(50);
    TASK_WAIT(elapsed, 1)
    resetTimer();
    turnOffLeds();
    btSerial->println("closed");
    currentState = STATE_CLOSED;
}

void Controller::resetTimer() {
    timeRemaining = T_DELIVER_SEC;
}

void Controller::turnOffLeds() {
    for (int i = 0; i < TRASH_TYPES_COUNT; i++) {
        leds[i]->turnOff();
    }
}