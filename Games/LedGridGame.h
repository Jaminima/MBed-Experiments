#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Devices/LedGrid.h"

class LedGridGame{
    protected:
        bool side = false;

    public:
        LedMatrix _ledmatrix[2];

        bool GetState(char x, char y){
            y%=8;
            x%=16;

            return (_ledmatrix[!side].matrixState[y][(x/8)] >> (x%8)) & 1U;
        }

        void SetState(char x, char y, bool State){
            y%=8;
            x%=16;

            _ledmatrix[side].matrixState[y][(x/8)] ^= (-State ^ _ledmatrix[side].matrixState[y][(x/8)]) & (1UL << (x%8));
        }
};