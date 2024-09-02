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
    Name: LCD_Clear
    Function: clear the screen
    Parameter: void
*/
void LCD_Clear(void)
{
    LCD_Write_Command(0x01, 1);
    DelayMs(5);
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
    Delay1Us();
    SET_EN;
    Delay1Us();
    Delay1Us();

    while (((DataPort & 0x80) != 0) && (later < 1000)) {
        Delay1Us();
        later++;
    }

    CLR_EN;
}

/*
    Name: LCD_LocateXY
    Function: locating the display address
    Parameter:
        _X: display column
        _Y: display row
*/
void LCD_LocateXY(uchar _X, uchar _Y)
{
    uchar temp;

    temp = _X & 0x0F; // preserve the last 4bits of x
    _Y &= 0x01;       // only preserve the last bit of y

    if (_Y) temp |= 0x40; // if it is on the second row
    temp |= 0x80;         // When writing the display address, the highest bit D7 is required to be constant at high level 1

    LCD_Write_Command(temp, 1);
}

/*
    Name: LCD_Display_Char
    Function: LCD display a single char
    Parameter:
        x: the culumn
        y: the row
        _char: the char
*/
void LCD_Display_Char(uchar x, uchar y, uchar _char)
{
    LCD_LocateXY(x, y);
    LCD_Write_Data(_char);
}

/*
    Name: LCD_Display_String
    Function: LCD display a string
    Parameter:
        x: the culumn
        y: the row
        *string: the string
*/
void LCD_Display_String(uchar x, uchar y, uchar *string)
{
    uchar i;
    LCD_LocateXY(x, y);
    for (i = 0; string[i] != '\0'; i++) {
        LCD_Write_Data(string[i]);
    }
}

/*
    Name: LCD_Display_Number
    Function: LCD display a number
    Parameter:
        x: the culumn
        y: the row
        _dat: the number
        _len: the number's length
*/
void LCD_Display_Number(uchar x, uchar y, uint _dat, uchar _len)
{
    uchar i;
    uint divisor = 1;

    LCD_LocateXY(x, y);

    for (i = 1; i < _len; i++) {
        divisor *= 10;
    }

    for (i = 0; i < _len; i++) {
        uchar digit = (_dat / divisor) % 10;
        LCD_Write_Data(digit + '0');
        divisor /= 10;
    }
}

/*
    Name: LCD_Display_LCD_Display_SignedNumber
    Function: LCD display a signed number
    Parameter:
        x: the culumn
        y: the row
        _dat: the number
        _len: the number's length
*/
void LCD_Display_SignedNumber(uchar x, uchar y, int _dat, uchar _len)
{
    uchar i;
    uint divisor = 1;
    uint number;

    LCD_LocateXY(x, y);

    if (_dat < 0) {
        LCD_Write_Data('-');
        number = -_dat;
    } else {
        number = _dat;
    }

    for (i = 1; i < _len; i++) {
        divisor *= 10;
    }

    for (i = 0; i < _len; i++) {
        uchar digit = (number / divisor) % 10;
        LCD_Write_Data(digit + '0');
        divisor /= 10;
    }
}
