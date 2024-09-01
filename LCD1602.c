/*
 hushmoon
 2024.8.31
 NATSU NO OWARI
*/
#include "LCD1602.h"

/*
    Name: LCD_Write_Command
    Function: Write command to LCD1602
    Parameter:
        _cmd -- the command
        _check -- whether to wait for availability or not
    Additional Descriptions:
        RS = 0->LCD implement instructions
        RS = 1->LCD display data
        RW = 0->write data TO LCD
        RW = 1->read data FROM LCD
        EN: enable.only when there is a level jump from 0 to 1, can LCD update the data displayed
*/
void LCD_Write_Command(uchar _cmd, uchar _check)
{

    // waiting for availability
    if (_check) WaitForEnable();

    CLR_RS;
    CLR_RW;
    CLR_EN;
    LCD_Delay1ms();

    DataPort = _cmd;
    LCD_Delay1ms();

    // send level pulse
    SET_EN; // EN = 1
    LCD_Delay1ms();
    CLR_EN; // EN = 0
    LCD_Delay1ms();
}

/*
    Name: LCD_Write_Data
    Function: Write data to LCD1602
    Parameter: _dat -- the data
*/
void LCD_Write_Data(uchar _dat)
{
    // waiting for availability
    WaitForEnable();

    SET_RS;
    CLR_RW;
    CLR_EN;
    LCD_Delay1ms();

    DataPort = _dat;
    LCD_Delay1ms();

    // send level pulse
    SET_EN; // EN = 1
    LCD_Delay1ms();
    CLR_EN; // EN = 0
    LCD_Delay1ms();
}

/*
    Name: LCD_Init
    Function: Initializing LCD1602
    Parameter: void
*/
void LCD_Init(void)
{
    LCD_Write_Command(0x38, 0);
    DelayMs(5);
    LCD_Write_Command(0x38, 0);
    DelayMs(5);
    LCD_Write_Command(0x38, 0);
    DelayMs(5);

    LCD_Write_Command(0x38, 1);
    LCD_Write_Command(0x08, 1);
    LCD_Write_Command(0x01, 1);
    LCD_Write_Command(0x06, 1);
    LCD_Write_Command(0x0C, 1);
}

/*
    Name: WaitForEnable
    Function: wait for lcd1602 being available
    Parameter: void
*/
void WaitForEnable(void)
{
    uint later = 0;
    DataPort   = 0xFF;
    CLR_RS;
    SET_RW;
    _nop_;
    SET_EN;
    _nop_;
    _nop_;

    while (((DataPIN & 0x80) != 0) && (later < 1000)) {
        _nop_;
        later++;
    }

    CLR_EN;
}