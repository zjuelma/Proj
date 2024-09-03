#ifndef __MLX90614_H__
#define __MLX90614_H__

#include <REG52.H>
#include <INTRINS.H>
#include "delay.h"
#include "LCD1602.h"

#define uchar unsigned char
#define uint  unsigned int

sbit SCL = P1 ^ 0; // CLOCK stream
sbit SDA = P1 ^ 1; // DATA stream

// I2C MODULE
void I2C_Start(void);
void I2C_Stop(void);
void send_bit(void);
void send_byte(uchar _byte);
void receive_bit(void);
uchar receive_byte(void);

uint Read_T(void);
int Convert_T(void);

#endif