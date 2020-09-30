#include "serial_reader.h"

using namespace smartdumpster;

SerialReader::SerialReader(SoftwareSerial *serial, Controller *controller) {
    this->serial = serial;
    this->controller = controller;
}

void SerialReader::step() {
    char btReadBuf[3];
    int trashType = 0;

    if (serial->available() >= 2) {
        serial->readBytesUntil(CMD_END, btReadBuf, 3);

        switch(btReadBuf[0]) {
            case CMD_HELLO:
                serial->println(dumpsterID);
                break;
            case CMD_OPEN:
                trashType = btReadBuf[1] - '0';
                if (trashType < 1 || trashType > 3) break;
                controller->openLid(trashTypeLut[trashType]);
                break;
            case CMD_POSTPONE: controller->moreTime(); break;
        }
    }
}

bool SerialReader::isComplete() {
    return false;
}