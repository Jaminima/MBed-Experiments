#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

class BusInWatch{
    protected:
        BusIn *Input = 0x0;
        int lastInput;
        TimerCompat timer;

    public:
        bool IgnoreAllOff = false;
        bool IgnoreRepeat = true;
        microseconds msBetweenInputs = 500ms;
        microseconds acceptEmptyAfter = 500ms;

        BusInWatch(BusIn *In){
            timer.start();
            Input = In;
        }

        bool InputHasChanged(){
            return *Input != lastInput || !IgnoreRepeat;
        }

        bool AcceptEmpty(){
            return *Input == 0x0 && (timer.elapsed_time() > acceptEmptyAfter && !IgnoreAllOff);
        }

        bool UpdatePending(){
            if (InputHasChanged() && timer.elapsed_time() > msBetweenInputs) { return *Input!=0x0 || AcceptEmpty(); }
            else return false;
        }

        virtual void ClearState(){
            lastInput = 0x0;
            timer.reset();
        }

        int GetInput(){
            if (UpdatePending()){
                timer.reset();
                lastInput = *Input;
                return lastInput;
            }
            return 0x0;
        }
};