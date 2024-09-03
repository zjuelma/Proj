#include <REG52.H>
#include "delay.h"
#include "LCD1602.h"
#include "MLX90614.h"
#include "main.h"

void main(void)
{
    DelayMs(500);
    LCD_Init();
    while (1) {
        Read_T();
        Display_Temperature();
        DelayMs(50);
    }
}
