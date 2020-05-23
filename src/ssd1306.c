#include "ssd1306.h"

void SSD1306_Init()
{
    I2C1_Start();
	while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
    I2C1_SendCommand(0xA8);
    I2C1_SendCommand(0x3F);
    I2C1_SendCommand(0xD3);
    I2C1_SendCommand(0x00);
    I2C1_SendCommand(0x40);    
    I2C1_SendCommand(0xA1);    
    I2C1_SendCommand(0xC8);    
    I2C1_SendCommand(0xDA);    
    I2C1_SendCommand(0x12);    
    I2C1_SendCommand(0x81);    
    I2C1_SendCommand(0x7F);    
    I2C1_SendCommand(0xA4);    
    I2C1_SendCommand(0xA6);    
    I2C1_SendCommand(0xD5);    
    I2C1_SendCommand(0x80);    
    I2C1_SendCommand(0x8D);    
    I2C1_SendCommand(0x14);    
    I2C1_SendCommand(0xAF);    
/*    I2C1_SendCommand(0xA5);
    I2C1_SendCommand(0xAE);*/
    I2C1_Stop();
}

void I2C1_SendCommand(uint8_t data)
{

	I2C1->DR = 0x80U;

	while ( !(I2C1->SR1 & I2C_SR1_BTF)  ||			// 0: Data byte transfer not done
			!(I2C1->SR1 & I2C_SR1_TXE)  ||			// 0: Data register not empty
			!(I2C1->SR2 & I2C_SR2_MSL)  ||			// 0: Slave Mode
			!(I2C1->SR2 & I2C_SR2_BUSY) ||			// 0: No communication on the bus
			!(I2C1->SR2 & I2C_SR2_TRA)				// 0: Data bytes received
	);

    I2C1->DR = data;

	while ( !(I2C1->SR1 & I2C_SR1_BTF)  ||			// 0: Data byte transfer not done
			!(I2C1->SR1 & I2C_SR1_TXE)  ||			// 0: Data register not empty
			!(I2C1->SR2 & I2C_SR2_MSL)  ||			// 0: Slave Mode
			!(I2C1->SR2 & I2C_SR2_BUSY) ||			// 0: No communication on the bus
			!(I2C1->SR2 & I2C_SR2_TRA)				// 0: Data bytes received
	);
}