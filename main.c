/*
 hushmoon
 2024.9.3
 END
*/
#include <REG52.H>
#include "delay.h"
#include "LCD1602.h"
#include "MLX90614.h"
#include "main.h"

int Temp; // temperature

sbit SW = P1 ^ 2; // switch

/*
    @author hushmoon
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
    @author hushmoon
    Name: Get_Temperature
    Function: Get the temperature and display it
    Parameter: void
*/
void Get_Temperature(void)
{
    LCD_Display_Char(5, 0, ' ');
    LCD_Display_Char(6, 0, Temp / 10000 % 10 + 0x30); // the hundreds
    LCD_Display_Char(7, 0, Temp / 1000 % 10 + 0x30);  // the tens
    LCD_Display_Char(8, 0, Temp / 100 % 10 + 0x30);   // the units
    LCD_Display_Char(10, 0, Temp / 10 % 10 + 0x30);   // the decimal
    LCD_Display_Char(11, 0, Temp % 10 + 0x30);        // the fractional
}

void main(void)
{
    DelayMs(100);   // waiting for the chip to be ready
    LCD_Init();     // initialize the LCD
    Display_Main(); // display the main interface
    while (1) {
        if (SW == 0) {   // if the switch is pressed
            DelayMs(20); // debounce
            if (SW == 0) {
                Temp = Convert_T();
                Get_Temperature(); // get the temperature and display it
            }
        }
        while (SW == 0); // waiting for the switch to be released
        DelayMs(20);
    }
}
