#include "ssd1306.h"

void SSD1306_Init()
{
    I2C1_Start();
	if(I2C1_SendAddress(I2C_ADDRESS, I2C_RECEIVER) == I2C_ERROR) {for(;;);}
    I2C1_SendData(0X80);
	I2C1_SendData(0xA8);
    I2C1_SendData(0X80);
	I2C1_SendData(0x3F);
    I2C1_SendData(0X80);
	I2C1_SendData(0xD3);
    I2C1_SendData(0X80);
	I2C1_SendData(0x00);
    I2C1_SendData(0X80);
	I2C1_SendData(0x40);
    I2C1_SendData(0X80);
	I2C1_SendData(0xA1);
    I2C1_SendData(0X80);
	I2C1_SendData(0xC8);
    I2C1_SendData(0X80);
	I2C1_SendData(0xDA);
    I2C1_SendData(0X80);
	I2C1_SendData(0x12);
    I2C1_SendData(0X80);
	I2C1_SendData(0x81);
    I2C1_SendData(0X80);
	I2C1_SendData(0x7F);
    I2C1_SendData(0X80);
	I2C1_SendData(0xA4);
    I2C1_SendData(0X80);
	I2C1_SendData(0xA6);
    I2C1_SendData(0X80);
	I2C1_SendData(0xD5);
    I2C1_SendData(0X80);
	I2C1_SendData(0x80);
    I2C1_SendData(0X80);
	I2C1_SendData(0x8D);
    I2C1_SendData(0X80);
	I2C1_SendData(0x14);
    I2C1_SendData(0X80);
	I2C1_SendData(0xAF);
    I2C1_Stop();
}
