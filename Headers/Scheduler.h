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
    unsigned int tickNum = 0, tickLim = 0xFFFFFFFF;
    Schedule *_schedule = 0x0;

    void CheckSchedule(){
        tickNum = (tickNum+1)%tickLim;
        for (unsigned int i=0;i<scheduleSize;i++){
            if (_schedule[i].func!=0x0 && tickNum % _schedule[i].tickGap == 0) _schedule[i].func();
        }
    }

public:
    unsigned int scheduleSize = 0;
    nanoseconds tickRate_ns = 1ns;

    Scheduler(unsigned int size){
        scheduleSize = size;
        _schedule = new Schedule[size];
    }

    void SetSchedule(unsigned int indx, void (*func)(), unsigned int tickGap){
        _schedule[indx] = Schedule(func,tickGap);
    }

    void SetSchedule_ms(unsigned int indx, void (*func)(), milliseconds timeGap){
        unsigned int ticks = timeGap/tickRate_ns;
        _schedule[indx] = Schedule(func,ticks/1000);
    }

    void SetSchedule_ns(unsigned int indx, void (*func)(), nanoseconds timeGap){
        unsigned int ticks = timeGap/tickRate_ns;
        _schedule[indx] = Schedule(func,ticks);
    }

    void Start(){
        while (true){
            CheckSchedule();
            wait_ns(tickRate_ns.count());
        }
    }
};