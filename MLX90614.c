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
    DelayUs2x(4);
    SCL = 1;
    DelayUs2x(4);
    SDA = 0;
    DelayUs2x(4);
    SCL = 0;
    DelayUs2x(4);
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
    DelayUs2x(4);
    SDA = 0;
    DelayUs2x(4);
    SCL = 1;
    DelayUs2x(4);
    SDA = 1;
    DelayUs2x(4);
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
    DelayUs2x(1);
    SCL = 1;
    DelayUs2x(4);
    SCL = 0;
    DelayUs2x(4);
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
    DelayUs2x(4);
    bit_in = SDA;
    DelayUs2x(2);
    SCL = 0;
    DelayUs2x(4);
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
    send_byte(0x00); // address
    send_byte(0x07); // command

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
    @name Convert_T
    @brief Convert the temperature from kelvin to celsius
    @param void
    @return T -- the temperature you read but in celsius
*/
int Convert_T(void)
{
    int temp, T;
    temp = Read_T();
    T    = ((float)temp * 0.02f - 273.15f) * 100;
    return T;
}
