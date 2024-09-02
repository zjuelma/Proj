/*
 hushmoon
 2024.9.1
 AKIE NO HAJIME
*/
#include "MLX90614.h"

bdata uchar flag;
sbit bit_out = flag ^ 7;
sbit bit_in  = flag ^ 0;

uchar Data_High, Data_Low, PEC;

/*
    @author hushmoon
    @brief delay for 1us approximately
    @param us: how many us you wanna delay
*/
void I2C_Delay_Us(uint us)
{
    while (us--) {
        Delay1Us();
    }
}

// I2C MODULE

/*
    @author hushmoon
    @name I2C_Start
    @brief start bit
    @param void
*/
void I2C_Start(void)
{
    SDA = 1;
    I2C_Delay_Us(5);
    SCL = 1;
    I2C_Delay_Us(5);
    SDA = 0;
    I2C_Delay_Us(5);
    SCL = 0;
    I2C_Delay_Us(5);
}

/*
    @author hushmoon
    @name I2C_Stop
    @brief end bit
    @param void
*/
void I2C_Stop(void)
{
    SCL = 0;
    I2C_Delay_Us(5);
    SDA = 0;
    I2C_Delay_Us(5);
    SCL = 1;
    I2C_Delay_Us(5);
    SDA = 1;
    I2C_Delay_Us(5);
}

/*
    @author hushmoon
    @name send_bit
    @brief send one bit
    @param void
*/
void send_bit(void)
{
    if (bit_out == 0)
        SDA = 0;
    else
        SDA = 1;
    Delay1Us();
    SCL = 1;
    I2C_Delay_Us(10);
    SCL = 0;
    I2C_Delay_Us(10);
}

/*
    @author hushmoon
    @name send_byte
    @brief send one byte
    @param _byte -- the byte you wanna send
*/
void send_byte(uchar _byte)
{
    char i, dat;
    int retry_counter;
    dat           = _byte;
    retry_counter = 10;

    while (retry_counter > 0) {
        for (i = 0; i < 8; i++) {
            bit_out = (dat & 0x80) ? 1 : 0;
            send_bit();
            dat <<= 1;
        }
        receive_bit();
        if (bit_in == 0) {
            return;
        }
        I2C_Stop();
        I2C_Start();
        retry_counter--; // Decrement retry counter
        dat = _byte;     // Reset data for retransmission
    }
}

/*
    @author hushmoon
    @name receive_bit
    @brief receive one bit
    @param void
*/
void receive_bit(void)
{
    SDA    = 1;
    bit_in = 1;
    SCL    = 1;
    I2C_Delay_Us(10);
    bit_in = SDA;
    I2C_Delay_Us(2);
    SCL = 0;
    I2C_Delay_Us(10);
}

/*
    @author hushmoon
    @name receive_byte
    @brief receive one byte
    @param void
    @return dat -- the byte you received
*/
uchar receive_byte(void)
{
    uchar i, dat;
    dat = 0;
    for (i = 0; i < 8; i++) {
        dat = dat << 1;
        receive_bit();
        if (bit_in == 1)
            dat = dat + 1;
    }
    send_bit(); // acknowledgement
    return dat;
}

/*
    @author hushmoon
    @name Rrad_T
    @brief read temperature through mlx90614
    @param void
    @return T -- the temperature you read but in kevin
*/
uint Read_T(void)
{
    I2C_Start();
    send_byte(0x00);
    send_byte(0x07);

    I2C_Start();
    send_byte(0x01);
    bit_out   = 0;
    Data_Low  = receive_byte();
    bit_out   = 0;
    Data_High = receive_byte();
    bit_out   = 1;
    PEC       = receive_byte();
    I2C_Stop();
    return (Data_High * 256 + Data_Low);
}

/*
    @author hushmoon
    @name Display_Temperature
    @brief display the temperature on lcd1602
    @param void
    @return none
*/
void Display_Temperature(void)
{
    int temp, T, a, b;
    temp = Read_T();
    T    = temp * 2;

    if (T >= 27315) {
        T = T - 27315;
        a = T / 100;
        b = T % 100;
    } else {
        T = 27315 - T;
        a = T / 100;
        b = T - a * 100;
        LCD_Display_Char(1, 1, '-');
    }
    LCD_Display_Number(1, 2, a, 3);
    LCD_Display_Char(1, 5, '.');
    LCD_Display_Number(1, 6, (unsigned long)b % 100, 2);
    LCD_Display_Char(1, 8, 0xDF);
    LCD_Display_Char(1, 9, 'C');
}
