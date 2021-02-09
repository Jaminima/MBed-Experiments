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

Ticker _tick;

Schedule *_schedule = 0x0;
unsigned int scheduleSize = 0;
unsigned int tickNum = 0, tickLim = 1000;
float tickRate_ms = 100;

void SetupScheduler(unsigned int size){
    scheduleSize = size;
    _schedule = new Schedule[size];
}

void CheckSchedule(){
    tickNum = (tickNum+1)%tickLim;
    for (unsigned int i=0;i<scheduleSize;i++){
        if (tickNum % _schedule[i].tickGap == 0) _schedule[i].func();
    }
}

void StartScheduler(){
    _tick.attach_us(&CheckSchedule,tickRate_ms);
}