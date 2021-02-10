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

SevenSegment seg;
unsigned int i=0;
void changeSevenSeg(){
    seg.SetSegmentNum(i, false);
    seg.SetSegmentNum(i+1, true);
    i = (i+1)%9;
}

void APressed(){
    seg.SetSegmentNum(0, false);
}
void BPressed(){
    seg.SetSegmentNum(1, false);
}
void CPressed(){
    seg.SetSegmentNum(2, false);
}
void DPressed(){
    seg.SetSegmentNum(3, false);
}
void EPressed(){
    seg.SetSegmentNum(4, false);
}

void buttonCheck(){
    buttonwatch.CheckAndRunEvents();
}

void ldrWatch(){
    ldrwatch.CheckAndRunEvents();
}

int main()
{
    Scheduler _sch(3);

    SW.mode(PullDown);

    ldrwatch.OnBecomeHigh = &GoneHigh;
    ldrwatch.OnBecomeLow = &GoneLow;
    ldrwatch.OnChange = &Changed;

    buttonwatch.APressed = &APressed;
    buttonwatch.BPressed = &BPressed;
    buttonwatch.CPressed = &CPressed;
    buttonwatch.DPressed = &DPressed;
    buttonwatch._BoardPressed = &EPressed;

    //_sch.SetSchedule(0,&changeSevenSeg,1000);
    _sch.SetSchedule(1,&buttonCheck,5);
    _sch.SetSchedule(2,&ldrWatch,1000);
    _sch.Start();
}


