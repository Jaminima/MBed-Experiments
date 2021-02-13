#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Games/LedGridGame.h"
#include "Headers/Random.h"

class GameOfLife : public LedGridGame {
    public:
        void SetRandom(Random *rnd){
            _ledmatrix[0].Clear();
            _ledmatrix[1].Clear();

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