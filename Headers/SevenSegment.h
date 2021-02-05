#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#ifndef _segDefined
    #define _segDefined
    DigitalOut _LED_DIGIT_OE(LED_DIGIT_OE_PIN,0);
    BusOut _ledData(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);

    DigitalOut _LED_D1_LE(LED_D1_LE_PIN,0);
    DigitalOut _LED_D2_LE(LED_D2_LE_PIN,0);
#endif

class SevenSegment{
public:

    void SetSegment(char pinState, bool targetPin){
        _LED_D1_LE = !targetPin;
        _LED_D2_LE = targetPin;

        wait_us(1);
        _ledData = pinState;
    }

};