/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//#include "mbed.h"
#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Headers/ButtonWatch.h"
#include "Headers/LDRWatch.h"
#include "Headers/SevenSegment.h"
#include "Headers/Scheduler.h"
#include "Games/GameOfLife.h"
#include "Headers/Random.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     50ms
#define BUTTON_SLEEP     10

void GoneHigh(float val){
    printf("Gone High %f \n",val);
}

void GoneLow(float val){
    printf("Gone Low %f \n",val);
}

void Changed(float val){
    printf("Changed %f \n",val);
}

AnalogIn LDR(PC_0);

BusOut leds(PC_6, PC_3, PC_2, LED1, LED2, LED3);

BusIn SW(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);

ButtonWatch buttonwatch = ButtonWatch();

LDRWatch ldrwatch(&LDR);

GameOfLife gameOfLife = GameOfLife();

Random rnd(&LDR);

SevenSegment seg;
unsigned int i=0;
void changeSevenSeg(){
    seg.SetNumber(i);
}

void buttonCheck(){
    buttonwatch.CheckAndRunEvents();
}

void ldrWatch(){
    ldrwatch.CheckAndRunEvents();
}

void gameTick(){
    gameOfLife.DoTick();
}

void display(){
    gameOfLife.Draw();
}

void APressed(){
    i--;
}
void BPressed(){
    i/=2;
}
void CPressed(){
    i++;
}
void DPressed(){
    i*=2;
}
void EPressed(){
    i=0;
}

int main()
{
    Scheduler _sch(4);
    _sch.tickRate_ns = 100ns;

    SW.mode(PullDown);

    ldrwatch.OnBecomeHigh = &GoneHigh;
    ldrwatch.OnBecomeLow = &GoneLow;
    ldrwatch.OnChange = &Changed;

    buttonwatch.APressed = &APressed;
    buttonwatch.BPressed = &BPressed;
    buttonwatch.CPressed = &CPressed;
    buttonwatch.DPressed = &DPressed;
    buttonwatch._BoardPressed = &EPressed;

    buttonwatch.IgnoreRepeat=false;

    //gameOfLife._ledmatrix[1].matrixState[1][0]=0x8B;
    //gameOfLife._ledmatrix[1].matrixState[2][0]=0x2C;
    //gameOfLife._ledmatrix[1].matrixState[3][1]=0x2F;
    //gameOfLife._ledmatrix[1].matrixState[1][1]=0x8B;

    //printf("Hello %d\n",rnd.RandomBool());

    gameOfLife.SetRandom(&rnd);

    _sch.SetSchedule(0,&changeSevenSeg,210);
    _sch.SetSchedule(1,&buttonCheck,50);
    _sch.SetSchedule(2,&gameTick,1000);
    _sch.SetSchedule(3,&display,3);
    //_sch.SetSchedule(2,&ldrWatch,1000);
    _sch.Start();
}


