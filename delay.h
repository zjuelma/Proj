#ifndef __DELAY_H__
#define __DELAY_H__

#include <REG52.H>
#include <INTRINS.H>

#define Delay1Us() _nop_()

void DelayMs(unsigned int ms);
void LCD_Delay1ms(void);
void DelayUs2x(unsigned char t);

#endif
