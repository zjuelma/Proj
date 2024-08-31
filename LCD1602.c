/*
 hushmoon
 2024.8.31
 NATSU NO OWARI
*/
#include "LCD1602.h"

/*
    Name: LCD_Write_Command
    Function: Write command to LCD1602
    Parameter: cmd -- the command
    Additional Descriptions:
        RS = 0->LCD implement instructions
        RS = 1->LCD display data
        RW = 0->write data TO LCD
        RW = 1->read data FROM LCD
        EN:enable.only when there is a level jump from 0 to 1, can LCD update the data displayed
*/
void LCD_Write_Command(uchar cmd)
{
    // RS = 0
    CLR_RS;
    // RW = 0
    CLR_RW;
    _nop_;

    DataPort = cmd;
    DelayMs(5);

    // send level pulse
    SET_EN; // EN = 1
    _nop_;
    _nop_;
    CLR_EN; // EN = 0
}

/*
    Name: LCD_Write_Data
    Function: Write Data to LCD1602
    Parameter: dat -- the data
*/
void LCD_Write_Data(uchar dat)
{
    // RS = 1
    SET_RS;
    // RW = 0
    CLR_RW;
    _nop_;

    DataPort = dat;
    DelayMs(5);

    // send level pulse
    SET_EN; // EN = 1
    _nop_;
    _nop_;
    CLR_EN; // EN = 0
}