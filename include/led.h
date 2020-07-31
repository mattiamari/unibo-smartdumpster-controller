#ifndef SMARTDUMPSTER_LED_H
#define SMARTDUMPSTER_LED_H

namespace smartdumpster
{
    class Led
    {
    public:
        virtual ~Led() {}
        virtual bool isOn() = 0;
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        virtual void toggle() = 0;
    };
}

#endif