#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Headers/LedGrid.h"
#include "Headers/Random.h"

class GameOfLife{
    private:
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

        void SetRandom(Random *rnd){
            for (char x=0,y=0;y<8;){    
                SetState(x, y, rnd->RandomBool());
                x++;
                if(x==16) { x=0; y++; }
            }
            side=!side;
        }

        bool _rules(char x, char y){
            char i = 0;
            
            i+=GetState(x-1,y-1);
            i+=GetState(x,y-1);
            i+=GetState(x+1,y-1);
            i+=GetState(x-1,y);
            i+=GetState(x+1,y);
            i+=GetState(x-1,y+1);
            i+=GetState(x,y+1);
            i+=GetState(x+1,y+1);

            if (GetState(x, y)) return i == 2 || i == 3;
            else return i == 3;
        }

        void DoTick(){
            _ledmatrix[side].Clear();
            for (char x=0,y=0;y<8;){
                if (_rules(x, y)) SetState(x, y, true);
                x++;
                if(x==16) { x=0; y++; }
            }
            side = !side;
        }

        void Draw(){
            _ledmatrix[side].writeMatrix();
        }
};