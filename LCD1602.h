#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REG52.H>
#include <INTRINS.H>
#include "delay.h"

/*
    DESCRIPTION:
        The location of LCD1602:
            _X: 0 1 2 3 4 5 6 7 8 9 A B C D E F (16Characters in total)
            _Y: 0 1 (2 ROWS)
            that means 2 ROWS & 16 COLUMNS
        EG.
        +-----------------------------------+
        +  0 1 2 3 4 5 6 7 8 9 A B C D E F  +
        +  0 1 2 3 4 5 6 7 8 9 A B C D E F  +
        +-----------------------------------+
*/
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

// functions
void LCD_Init(void);
void LCD_Clear(void);
void LCD_LocateXY(uchar _X, uchar _Y);
void LCD_Write_Command(uchar cmd);
void LCD_Write_Data(uchar dat);

#endif
