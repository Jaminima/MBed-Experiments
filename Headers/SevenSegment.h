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
    private:
        //DP C B A D G E F
        char _numLayouts[10] { 0b01111011, 0b01100000, 0b00111110, 0b01111100, 0b01100101, 0b01011101, 0b01011111, 0b01110000, 0b01111111, 0b01110101 };

    public:

    void SetTarget(bool target){
        if (!target){
            _LED_D1_LE = 1;
            wait_us(1);
            _LED_D1_LE = 0;
            wait_us(1);
        }
        else{
            _LED_D2_LE = 1;
            wait_us(1);
            _LED_D2_LE = 0;
            wait_us(1);
        }
    }

    void SetSegmentNum(unsigned int i, bool targetPin){
        _ledData = _numLayouts[i];
        SetTarget(targetPin);
    }

    void SetSegment(char pinState, bool targetPin){
        SetTarget(targetPin);
        _ledData = pinState;
    }

};