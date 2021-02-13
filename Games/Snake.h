#pragma once

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Devices/ButtonWatch.h"
#include "Headers/Random.h"
#include "Headers/List.h"
#include "Devices/LedGrid.h"

class Snake{
    private:
        LedMatrix _ledmatrix;
        List _body;
        bool gameRunning = true;
        Random *rnd;
        char food[2];

        void SetState(char x, char y, bool State){
            y%=8;
            x%=16;

            _ledmatrix.matrixState[y][(x/8)] ^= (-State ^ _ledmatrix.matrixState[y][(x/8)]) & (1UL << (x%8));
        }

        char* GetHead(){
            return (char*)_body.head->obj;
        }

        bool IsEmpty(char x, char y){
            ListItem *i = _body.head;
            while (i!=0x0){
                char *p = (char*)i->obj;
                if (p[0]==x && p[1] == y) return false;
                i = i->next;
            }

            return true;
        }

        bool IsFood(char x, char y){
            return food[0] == x && food[1] == y;
        }

        void HitFood(){
            MoveFood();
            score++;
            if (scored!=0x0) scored();
        }

        void MoveFood(){
            char x = food[0], y = food[1];

            while (IsFood(x, y) || !IsEmpty(x, y)){
                x = rnd->RandomRange(16);
                y = rnd->RandomRange(8);
            }

            food[0]=x;
            food[1]=y;
        }

    public:
        ButtonWatch _buttons;
        unsigned int score = 0;
        void (*gameEnded)() = 0x0;
        void (*scored)() = 0x0;

        Snake(Random *_rnd){
            rnd = _rnd;
            _buttons.IgnoreRepeat=false;
            _body.Add(new char[2]{8,4});
            
            MoveFood();
        }

        bool MoveHead(char x, char y){
            if (IsEmpty(x, y)){
                _body.Add(new char[2]{x,y});

                if (IsFood(x,y)) HitFood();
                else _body.Remove(_body.tail);

                return true;
            }
            return false;
        }

        void Draw(){
            _ledmatrix.Clear();

            ListItem *i = _body.head;
            while (i!=0x0){
                char *p = (char*)i->obj;
                SetState(p[0], p[1], true);
                i = i->next;
            }

            SetState(food[0], food[1], true);

            _ledmatrix.writeMatrix();
        }

        void Pressed(char direction){
            if (!gameRunning) return;

            char* pos = GetHead();
            pos = new char[2]{pos[0],pos[1]};

            switch (direction){
                case 0:
                    pos[0]--;
                break;
                case 1:
                    pos[1]--;
                break;
                case 2:
                    pos[0]++;
                break;
                case 3:
                    pos[1]++;
                break;
            }

            if (!MoveHead(pos[0]%16,pos[1]%8)) {
                gameRunning = false;
                if (gameEnded!=0x0) gameEnded();
            }
        }

        void CheckForButton(){
            _buttons.CheckAndRunEvents();
        }
};