#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

#include "BusInWatch.h"

class BusInOutWatch : BusInWatch{
    protected:
        BusOut *Output = 0x0;

    public:
        bool IgnoreAllOff = true;
        bool IgnoreRepeat = true;
        microseconds msBetweenInputs = 5000ms;

    BusInOutWatch(BusIn *In, BusOut *Out) : BusInWatch(In){
        Output = Out;
    }

    void UpdateOutput(){
        if (UpdatePending()){
            timer.reset();
            lastInput = *Input;
            *Output = *Input;
        }
    }
};