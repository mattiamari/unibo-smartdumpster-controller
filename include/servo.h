#ifndef SMARTDUMPSTER_SERVO_H
#define SMARTDUMPSTER_SERVO_H

namespace smartdumpster
{
    class Servo
    {
    public:
        virtual ~Servo() {}
        virtual void setAngle(int angle) = 0;
        virtual int getAngle() = 0;
        virtual int getAngleMin() = 0;
        virtual int getAngleMax() = 0;
    };
}

#endif