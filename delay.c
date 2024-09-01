#include "delay.h"
#include <INTRINS.H>

void DelayMs(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++) {
        // set the timer mode 1 (16-bits timer)
        // eliminate low 4 bits and set the mode to mode 1
        TMOD &= 0xF0;
        // timer 0 mode 1
        TMOD |= 0x01;

        // set the initial value
        TH0 = 0xFC;
        TL0 = 0x66;

        // start the timer
        TR0 = 1;

        // waiting for overflow
        while (TF0 == 0);

        // shut down the timer
        TR0 = 0;
        // clear the flag
        TF0 = 0;
    }
}