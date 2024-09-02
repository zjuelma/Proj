#include "delay.h"

/*
    Tips:
        1 _nop_() for delaying 2us
*/

/*
    Name: DelayMs
    Function: Delay for ms
    Parameter: ms -- the total ms you wanna delay
*/
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

/*
    Name: LCD_Delay1ms
    Function: delay 1 ms
    Parameter: none
*/
void LCD_Delay1ms(void) //@11.0592MHz
{
    unsigned char data i, j;

    _nop_();
    i = 2;
    j = 199;
    do {
        while (--j);
    } while (--i);
}