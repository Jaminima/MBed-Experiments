#pragma once

#include "Devices/ButtonWatch.h"
#include "Headers/Random.h"
#include "Headers/Scheduler.h"

#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

Scheduler _sch(6);
AnalogIn LDR(PC_0);
Random rnd(&LDR);

#ifdef _Snake
#include "Games/Snake.h"
#include "Devices/SevenSegment.h"
Snake _snake = Snake(&rnd);
SevenSegment seg;

void snk_buttonCheck(){
    _snake._buttons.CheckAndRunEvents();
}

void snk_APressed(){
    _snake.Pressed(0);
}
void snk_BPressed(){
    _snake.Pressed(1);
}
void snk_CPressed(){
    _snake.Pressed(2);
}
void snk_DPressed(){
    _snake.Pressed(3);
}

void snk_display(){
    _snake.Draw();
}

void snk_scored(){
    seg.SetNumber(_snake.score);
}

void snk_end(){
    
}

void Setup_GameOfLife(){
    _snake._buttons.APressed = &snk_APressed;
    _snake._buttons.BPressed = &snk_BPressed;
    _snake._buttons.CPressed = &snk_CPressed;
    _snake._buttons.DPressed = &snk_DPressed;

    _snake.gameEnded = &snk_end;
    _snake.scored = &snk_scored;

    seg.SetNumber(0);

    _sch.SetSchedule_ns(0,&snk_buttonCheck,200ns);
    _sch.SetSchedule_ns(1,&snk_display,300ns);
}

#endif

#ifdef _GameOfLife
#include "Games/GameOfLife.h"
GameOfLife gameOfLife = GameOfLife();
ButtonWatch gme_buttonwatch = ButtonWatch();

void gme_EPressed(){
    gameOfLife.SetRandom(&rnd);
}

void gme_buttonCheck(){
    gme_buttonwatch.CheckAndRunEvents();
}

void gme_gameTick(){
    gameOfLife.DoTick();
}

void gme_display(){
    gameOfLife.Draw();
}

void Setup_GameOfLife(){
    gme_buttonwatch._BoardPressed = &gme_EPressed;

    gameOfLife.SetRandom(&rnd);

    _sch.SetSchedule_ns(0,&gme_buttonCheck,200ns);
    _sch.SetSchedule_ms(1,&gme_gameTick,250ms);
    _sch.SetSchedule_ns(2,&gme_display,300ns);

}
#endif

#ifdef _SevenSegment
#include "Devices/SevenSegment.h"

ButtonWatch seg_buttonwatch = ButtonWatch();
SevenSegment seg;
unsigned int i=0;
void seg_changeSevenSeg(){
    seg.SetNumber(i);
}

void seg_buttonCheck(){
    seg_buttonwatch.CheckAndRunEvents();
}

void seg_APressed(){
    i--;
}
void seg_BPressed(){
    i/=2;
}
void seg_CPressed(){
    i++;
}
void seg_DPressed(){
    i*=2;
}
void seg_EPressed(){
    i=0;
}

void Setup_SevenSegment(){
    seg_buttonwatch.APressed = &seg_APressed;
    seg_buttonwatch.BPressed = &seg_BPressed;
    seg_buttonwatch.CPressed = &seg_CPressed;
    seg_buttonwatch.DPressed = &seg_DPressed;
    seg_buttonwatch._BoardPressed = &seg_EPressed;

    seg_buttonwatch.IgnoreRepeat = false;

    _sch.SetSchedule_ns(3,&seg_buttonCheck,200ns);
    _sch.SetSchedule_ns(4,&seg_changeSevenSeg,500ns);
}
#endif

#ifdef _LDRWatch
#include "Devices/LDRWatch.h"

void ldr_GoneHigh(float val){
    printf("Gone High %f \n",val);
}

void ldr_GoneLow(float val){
    printf("Gone Low %f \n",val);
}

void ldr_Changed(float val){
    printf("Changed %f \n",val);
}

LDRWatch ldrwatch(&LDR);

void ldr_ldrWatch(){
    ldrwatch.CheckAndRunEvents();
}

void Setup_LDRWatch(){
    ldrwatch.OnBecomeHigh = &ldr_GoneHigh;
    ldrwatch.OnBecomeLow = &ldr_GoneLow;
    ldrwatch.OnChange = &ldr_Changed;
    _sch.SetSchedule_ms(5,&ldr_ldrWatch,100ms);
}

#endif

BusIn SW(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);
void Setup(){
    SW.mode(PullDown);

    _sch.tickRate_ns = 100ns;
    
    #ifdef _LDRWatch
    Setup_LDRWatch();
    #endif

    #ifdef _GameOfLife
    Setup_GameOfLife();
    #endif

    #ifdef _SevenSegment
    Setup_SevenSegment();
    #endif
    
    #ifdef _Snake
    Setup_GameOfLife();
    #endif

    _sch.Start();
}