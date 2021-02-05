#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

class BusWatch{
    private:
     BusIn *Input = 0x0;
     BusOut *Output = 0x0;
     int lastInput;
     TimerCompat timer;

    public:
    bool IgnoreAllOff = true;
    bool IgnoreRepeat = true;
    microseconds msBetweenInputs = 5000ms;

    BusWatch(BusIn *In, BusOut *Out){
        timer.start();
        Input = In;
        Output = Out;
    }

    bool InputHasChanged(){
        return *Input != lastInput || !IgnoreRepeat;
    }

    bool UpdatePending(){
        if (InputHasChanged() && timer.elapsed_time() > msBetweenInputs) return *Input!=0x0;
        else return false;
    }

    void UpdateOutput(){
        if (UpdatePending()){
            timer.reset();
            lastInput = *Input;
            *Output = *Input;
        }
    }
};