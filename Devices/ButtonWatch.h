#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

#include "BusInWatch.h"
#ifndef _buttDefined
    #define _buttDefined
    BusIn boardButtons(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN, BUTTON1);

    void doNothing(){ }
#endif

class ButtonWatch : public BusInWatch{
public:
    void (*APressed)() = &doNothing;
    void (*BPressed)() = &doNothing;
    void (*CPressed)() = &doNothing;
    void (*DPressed)() = &doNothing;
    void (*_BoardPressed)() = &doNothing;

    ButtonWatch() : BusInWatch(&boardButtons)
    { }

    void CheckAndRunEvents(){
        if (UpdatePending()){
            char state = GetInput();

            switch (state) {
                case 0b1:
                    APressed();
                break;
                case 0b10:
                    BPressed();
                break;
                case 0b100:
                    CPressed();
                break;
                case 0b1000:
                    DPressed();
                break;
                case 0b10000:
                    _BoardPressed();
                break;
            }
        }
    }
};