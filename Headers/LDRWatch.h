#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

class LDRWatch{
    private:
        AnalogIn *ldr = 0x0;
        float previousValue;
        TimerCompat timer;

    public:
        microseconds msBetweenCheck = 500ms;
        float changeToTrigger = 0.05f;
        float lowTrigger = 0.4f;
        float highTrigger = 0.6f;

        void (*OnBecomeLow)(float) = 0x0;
        void (*OnBecomeHigh)(float) = 0x0;
        void (*OnChange)(float) = 0x0;

        LDRWatch(AnalogIn *ldr){
            this->ldr = ldr;
            previousValue = *ldr;
            timer.start();
        }

        bool UpdatePending(){
            return abs(*ldr - previousValue) > changeToTrigger && timer.elapsed_time() > msBetweenCheck;
        }

        void CheckAndRunEvents(){
            bool updatepend = UpdatePending();
            float value = GetValue();

            if (updatepend){
                if (value < lowTrigger/* && previousValue > lowTrigger*/) OnBecomeLow(value);
                else if (value > highTrigger/* && previousValue < highTrigger*/) OnBecomeHigh(value);
                else OnChange(value);
            }
        }

        float GetValue(){
            if (UpdatePending()){
                timer.reset();
            }
            previousValue = *ldr;
            return previousValue;
        }
};