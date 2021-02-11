#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#ifndef _grdDefined
    #define _grdDefined
    SPI spi(PC_12, PC_11, PC_10); 

    DigitalOut cs(PB_6);            //Chip Select ACTIVE LOW
    DigitalOut oe(PB_12);           //Output Enable ACTIVE LOW
#endif

class LedMatrix{
private:
    bool wState = false;

public:
    char matrixState[8][2] = {};

    void writeMatrix(){

        for (char y=0;y<8;y++){
            cs=0;
            spi.write(matrixState[y][1]);
            spi.write(matrixState[y][0]);
            spi.write(y);
            cs=1;
            wait_ns(1);
        }
    }

    void SetLed(char x, char y){
        x++;

        char _x = x*x;

        cs=0;
        if (x>7){
            spi.write(_x);
            spi.write(0x00);
        }
        else{
            spi.write(0x00);
            spi.write(_x);
        }
        spi.write(y);
        cs=1;
    }

};