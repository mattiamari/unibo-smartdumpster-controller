#ifndef SMARTDUMPSTER_CONTROLLER_H
#define SMARTDUMPSTER_CONTROLLER_H

#include "task.h"
#include "servo.h"
#include "led.h"
#include <SoftwareSerial.h>

#define T_DELIVER_SEC 10
#define TRASH_TYPES_COUNT 3

namespace smartdumpster {
    enum TrashType {
        TRASH_NONE = 0,
        TRASH_PLASTIC,
        TRASH_PAPER,
        TRASH_UNSORTED
    };

    enum ControllerState {
        STATE_CLOSED = 1,
        STATE_OPENING,
        STATE_OPEN,
        STATE_CLOSING
    };

    class Controller : public Task
    {
    public:
        Controller(Servo *servo, Led *leds[TRASH_TYPES_COUNT], SoftwareSerial *btSerial);
        void openLid(TrashType type);
        void moreTime();
        void step();
        bool isComplete();
        ControllerState getState();

    private:
        Servo *servo;
        Led **leds;
        SoftwareSerial *btSerial;
        ControllerState currentState;
        unsigned int timeRemaining;

        void stateOpening();
        void stateOpen();
        void stateClosing();

        void resetTimer();
        void turnOffLeds();
    };
}

#endif