#ifndef SMARTDUMPSTER_SCHEDULER_H
#define SMARTDUMPSTER_SCHEDULER_H

#include "task.h"

#define MAX_TASKS 1

namespace smartdumpster
{
    typedef struct TaskInfo_s {
        Task *task;
        unsigned int interval;
        unsigned int elapsed;
    } TaskInfo;

    class Scheduler
    {
    public:
        Scheduler();
        ~Scheduler() {};
        void add(Task *task, unsigned int interval);
        void add(Task *task);
        void remove(Task *task);
        bool has(Task *task);
        void clear();
        void schedule();
        unsigned int getTaskCount();

    private:
        TaskInfo tasks[MAX_TASKS];
        unsigned int taskCount;
    };
}

#endif
