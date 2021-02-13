#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

#include "BusInWatch.h"

class BusInOutWatch : public BusInWatch{
    protected:
        BusOut *Output = 0x0;

    public:

        BusInOutWatch(BusIn *In, BusOut *Out) : BusInWatch(In){
            Output = Out;
        }

        void ClearState() override{
            lastInput = 0x0;
            *Output = lastInput;
            timer.reset();
        }

        void UpdateOutput(){
            if (UpdatePending()){
                timer.reset();
                lastInput = *Input;
                *Output = *Input;
            }
        }
};