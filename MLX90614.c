/*
 hushmoon
 2024.9.1
 AKIE NO HAJIME
*/
#include "MLX90614.h"
#define MLX90614_ADDRESS 0x5A // MLX90614's I2C ADDRESS

bdata uchar flag;
sbit bit_out = flag ^ 7;
sbit bit_in  = flag ^ 0;

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

void send_byte(uchar _byte)
{
    char i, n, dat;
    dat               = _byte;
    int retry_counter = 10;

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
        stop_bit();
        start_bit();
        n--;
        dat = _byte;
    }
}

void receive_bit(void)
{
    SDA =
}
