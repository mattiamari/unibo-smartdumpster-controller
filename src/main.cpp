#include <Arduino.h>
#include <SoftwareSerial.h>

#include "scheduler.h"
#include "controller.h"
#include "serial_reader.h"
#include "hw_servo.h"
#include "hw_led.h"

#define PIN_LED_A 10
#define PIN_LED_B 11
#define PIN_LED_C 12
#define PIN_SERVO 6
#define PIN_BT_TX 7
#define PIN_BT_RX 8

smartdumpster::Scheduler *scheduler;
smartdumpster::Controller *controller;
smartdumpster::SerialReader *serialReader;
smartdumpster::Servo *servo;
smartdumpster::Led *leds[3];

unsigned long time = 0;
unsigned long diff;
SoftwareSerial btSerial(PIN_BT_TX, PIN_BT_RX);

void setup()
{
    Serial.begin(9600);

    servo = new smartdumpster::HWServo(PIN_SERVO);
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
    serialReader = new smartdumpster::SerialReader(&btSerial, controller);

    scheduler->add(controller, 1000 / TICK_INTERVAL_MS); // run every 1 second
    scheduler->add(serialReader, 1); // run on every tick
    servo->setAngle(servo->getAngleMin());

    btSerial.begin(9600);
    btSerial.listen();

    delay(2000);
    btSerial.println("AT+NAMEsmartdumpster01");
    // btSerial.write("AT+ROLE=0");
}

void loop()
{
    time = millis();

    scheduler->schedule();
    diff = millis() - time;

    if (diff < TICK_INTERVAL_MS) {
        delay(TICK_INTERVAL_MS - diff);
    } else if (diff > TICK_INTERVAL_MS) {
        Serial.println("Can't keep up");
    }
}
