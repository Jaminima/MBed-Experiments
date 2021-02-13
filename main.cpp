/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//#include "mbed.h"
#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Devices/ButtonWatch.h"
#include "Devices/LDRWatch.h"
//#include "Devices/SevenSegment.h"
#include "Games/GameOfLife.h"
#include "Headers/Random.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     50ms
#define BUTTON_SLEEP     10

/*void GoneHigh(float val){
    printf("Gone High %f \n",val);
}

void GoneLow(float val){
    printf("Gone Low %f \n",val);
}

void Changed(float val){
    printf("Changed %f \n",val);
}

AnalogIn LDR(PC_0);

LDRWatch ldrwatch(&LDR);


void buttonCheck(){
    buttonwatch.CheckAndRunEvents();
}

void ldrWatch(){
    ldrwatch.CheckAndRunEvents();
}*/

#define _LDRWatch
#define _SevenSegment
#define _GameOfLife
#include "Headers/Setup.h"

int main()
{
    Setup();
}


