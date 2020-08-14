#include <Arduino.h>
#include <BluetoothSerial.h>
#include "scheduler.h"
#include "controller.h"
#include "dummy_servo.h"
#include "hw_led.h"

#define PIN_LED_A 32
#define PIN_LED_B 33
#define PIN_LED_C 25
#define PIN_SERVO 6
#define PIN_BT_TX 7
#define PIN_BT_RX 8

const char *dumpsterID = "162db43a-f153-4efd-8671-a0ca8c921031";

smartdumpster::Scheduler *scheduler;
smartdumpster::Controller *controller;
smartdumpster::Servo *servo;
smartdumpster::Led *leds[3];

unsigned long loopTime = 0;
unsigned long diff;
char btReadBuf[3];
BluetoothSerial btSerial;

enum BtCommands {
    CMD_HELLO    = 'H',
    CMD_OPEN     = 'O',
    CMD_POSTPONE = 'P',
    CMD_END      = 'E'
};

smartdumpster::TrashType trashTypeLut[4] = {
    smartdumpster::TRASH_NONE,
    smartdumpster::TRASH_PLASTIC,
    smartdumpster::TRASH_PAPER,
    smartdumpster::TRASH_UNSORTED
};

void setup()
{
    Serial.begin(9600);
    btSerial.begin("smartdumpster-esp");

    servo = new smartdumpster::DummyServo();
    leds[0] = new smartdumpster::HWLed(PIN_LED_A);
    leds[1] = new smartdumpster::HWLed(PIN_LED_B);
    leds[2] = new smartdumpster::HWLed(PIN_LED_C);

    servo->setAngle(10);
    delay(1000);
    servo->setAngle(200);
    delay(1000);
    servo->setAngle(10);
    delay(1000);

    scheduler = new smartdumpster::Scheduler();
    controller = new smartdumpster::Controller(servo, leds, &btSerial);

    scheduler->add(controller, 1000 / TICK_INTERVAL_MS);
    servo->setAngle(servo->getAngleMin());
}

void loop()
{
    loopTime = millis();

    int trashType = 0;

    if (btSerial.available() >= 2) {
        btSerial.readBytesUntil(CMD_END, btReadBuf, 3);

        Serial.print("Received: ");
        Serial.println(btReadBuf);

        switch(btReadBuf[0]) {
            case CMD_HELLO:
                btSerial.println(dumpsterID);
            case CMD_OPEN:
                trashType = btReadBuf[1] - '0';
                if (trashType < 1 || trashType > 3) break;
                controller->openLid(trashTypeLut[trashType]);
                break;
            case CMD_POSTPONE: controller->moreTime(); break;
        }
    }

    scheduler->schedule();
    diff = millis() - loopTime;

    if (diff < TICK_INTERVAL_MS) {
        delay(TICK_INTERVAL_MS - diff);
    } else if (diff > TICK_INTERVAL_MS) {
        Serial.println("Can't keep up");
    }
}
