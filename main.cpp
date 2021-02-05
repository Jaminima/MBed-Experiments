/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//#include "mbed.h"
#include "lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#include "Headers/BusInOutWatch.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     50ms
#define BUTTON_SLEEP     10

int main()
{
    BusOut leds(PC_6, PC_3, PC_2, LED1, LED2, LED3);

    BusIn SW(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);

    BusInOutWatch watch(&SW,&leds);

    while (true) {

        SW.mode(PullDown);

        watch.UpdateOutput();

        ThisThread::sleep_for(BLINKING_RATE);
    }
}


