#ifndef SMARTDUMPSTER_TASK_H
#define SMARTDUMPSTER_TASK_H

#define TICK_INTERVAL_MS 20

#define TASK_WAIT(COUNTER, DELAY) if ((COUNTER) < (DELAY)) {(COUNTER) += 1; return;} (COUNTER) = 0;

namespace smartdumpster
{
    class Task
    {
    public:
        virtual ~Task() {};
        virtual void step() = 0;
        virtual bool isComplete() = 0;
    };
}

#endif
