#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

class Schedule{
public:
    void (*func)() = 0x0;
    unsigned int tickGap = 100;

    Schedule(){};

    Schedule(void (*func)(), unsigned int tickGap){
        this->func = func;
        this->tickGap = tickGap;
    }
};

class Scheduler{
private:
    unsigned int tickNum = 0, tickLim = 10000;
    Schedule *_schedule = 0x0;

    void CheckSchedule(){
        tickNum = (tickNum+1)%tickLim;
        for (unsigned int i=0;i<scheduleSize;i++){
            if (_schedule[i].func!=0x0 && tickNum % _schedule[i].tickGap == 0) _schedule[i].func();
        }
    }

public:
    unsigned int scheduleSize = 0;
    nanoseconds tickRate_ns = 1ms;

    Scheduler(unsigned int size){
        scheduleSize = size;
        _schedule = new Schedule[size];
    }

    void SetSchedule(unsigned int indx, void (*func)(), unsigned int tickGap){
        _schedule[indx] = Schedule(func,tickGap);
    }

    void Start(){
        while (true){
            CheckSchedule();
            wait_ns(tickRate_ns.count());
        }
    }
};