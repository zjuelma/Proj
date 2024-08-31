/*
 hushmoon
 2024.8.31
 NATSU NO OWARI
*/
#include "LCD1602.h"

/*
    Name: LCD_Write
    Function: Write command OR data to LCD1602
    Parameter:
        _dat -- the command or the data
        _RS -- to determine whether to display data or implement instructions
    Additional Descriptions:
        RS = 0->LCD implement instructions
        RS = 1->LCD display data
        RW = 0->write data TO LCD
        RW = 1->read data FROM LCD
        EN: enable.only when there is a level jump from 0 to 1, can LCD update the data displayed
*/

void LCD_Write(uchar _dat, bit _RS)
{
    // waiting for availability
    DelayMs(2);
    RS = _RS;
    CLR_RW;
    CLR_EN;
    _nop_;

    DataPort = _dat;
    DelayMs(5);

    // send level pulse
    SET_EN; // EN = 1
    _nop_;
    _nop_;
    CLR_EN; // EN = 0
}

void LCD_Init(void)
{
    DelayMs(15);
    LCD_Write(0x38, 0);
    DelayMs(5);
}