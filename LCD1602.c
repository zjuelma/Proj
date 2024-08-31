/*
 hushmoon
 2024.8.31
 NATSU NO OWARI
*/
#include "LCD1602.h"
#include "delay.h"
#include <INTRINS.H>

// PIN MAPPING
sbit RS  = P2 ^ 7;
sbit RW  = P2 ^ 6;
sbit EN  = P2 ^ 5;
sbit DB0 = P0 ^ 0;
sbit DB1 = P0 ^ 1;
sbit DB2 = P0 ^ 2;
sbit DB3 = P0 ^ 3;
sbit DB4 = P0 ^ 4;
sbit DB5 = P0 ^ 5;
sbit DB6 = P0 ^ 6;
sbit DB7 = P0 ^ 7;

#define uchar    unsigned char
#define uint     unsigned int
#define DataPort P0

#define CLR_RS   (RS = 0)
#define SET_RS   (RS = 1)
#define CLR_RW   (RW = 0)
#define SET_RW   (RW = 1)
#define CLR_EN   (EN = 0)
#define SET_EN   (EN = 1)

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