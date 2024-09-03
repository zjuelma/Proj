#include <REG52.H>
#include "delay.h"
#include "LCD1602.h"
#include "MLX90614.h"
#include "main.h"

int Temp;

/*
    @zjuelma
    Name: Display_Main
    Function: Display the main interface
    Parameter: void
*/
void Display_Main(void)
{
    LCD_Clear();
    LCD_Display_String(0, 0, "Temp:    .   C");
    LCD_Display_Char(12, 0, 0xDF);
}

/*
    @zjuelma
    Name: Get_Temperature
    Function: Get the temperature and display it
    Parameter: void
*/
void Get_Temperature(void)
{
    LCD_Display_Char(5, 0, ' ');
    LCD_Display_Char(6, 0, Temp / 10000 % 10 + 0x30);
    LCD_Display_Char(7, 0, Temp / 1000 % 10 + 0x30);
    LCD_Display_Char(8, 0, Temp / 100 % 10 + 0x30);
    LCD_Display_Char(10, 0, Temp / 10 % 10 + 0x30);
    LCD_Display_Char(11, 0, Temp % 10 + 0x30);
}

void main(void)
{
    DelayMs(100);
    LCD_Init();
    Display_Main();
    while (1) {
        Temp = Convert_T();
        Get_Temperature();
        DelayMs(500);
    }
}
