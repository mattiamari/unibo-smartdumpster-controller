#ifndef SMARTDUMPSTER_SERIAL_READER_H
#define SMARTDUMPSTER_SERIAL_READER_H

#include "task.h"
#include "controller.h"
#include <SoftwareSerial.h>

namespace smartdumpster {
    const char dumpsterID[] = "162db43a-f153-4efd-8671-a0ca8c921031";

    enum BtCommands {
        CMD_HELLO    = 'H',
        CMD_OPEN     = 'O',
        CMD_POSTPONE = 'P',
        CMD_END      = 'E'
    };

    const TrashType trashTypeLut[4] = {
        TRASH_NONE,
        TRASH_PLASTIC,
        TRASH_PAPER,
        TRASH_UNSORTED
    };

    class SerialReader : public Task
    {
    public:
        SerialReader(SoftwareSerial *serial, Controller *controller);
        void step();
        bool isComplete();
    private:
        SoftwareSerial *serial;
        Controller *controller;
    };
}

#endif