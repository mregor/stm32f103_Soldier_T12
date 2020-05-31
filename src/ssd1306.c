#include "ssd1306.h"

void I2C1_SSD1306_Init()
{
    I2C1_Start();
	while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
    I2C1_SSD1306_SendCommand(0xA8);
    I2C1_SSD1306_SendCommand(0x3F);
    I2C1_SSD1306_SendCommand(0x81);
    I2C1_SSD1306_SendCommand(0x7F);
    I2C1_SSD1306_SendCommand(0xA1);    
    I2C1_SSD1306_SendCommand(0xC0);    
    I2C1_SSD1306_SendCommand(0xDA);    
    I2C1_SSD1306_SendCommand(0x12);    
    I2C1_SSD1306_SendCommand(0xD3);    
    I2C1_SSD1306_SendCommand(0x00);    
    I2C1_SSD1306_SendCommand(0x40);  
    I2C1_SSD1306_SendCommand(0xC8);  
    I2C1_SSD1306_SendCommand(0xAF);        
    I2C1_Stop();
}

void I2C1_SSD1306_SendCommand(uint8_t data)
{

	I2C1->DR = 0x80;

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

void I2C1_SSD1306_Clear()
{
    for(uint8_t PAGE=0; PAGE<8; PAGE++)
    {
    	I2C1_Start();
        while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
        I2C1_SSD1306_SendCommand(0x00);  
        I2C1_SSD1306_SendCommand(0x10);  
        I2C1_SSD1306_SendCommand(0xB0 | PAGE);  
        I2C1_SendData(0x40);
        for(uint8_t i=0;i<131;i++) 
	    {
            I2C1_SendData(0x00);
	    }
        I2C1_Stop();
    }    
}

void DrawThermometre(uint8_t column, uint8_t page)
{
    uint8_t num = 0, column_low = 0, column_high = 0;
    column_low = (column & 0x0F) + 2;
    column_high = 0x10 | (column >> 4);
    for(int i = 0; i < 3; i++)
    {
		I2C1_Start();
        while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
        I2C1_SSD1306_SendCommand(column_low);  
        I2C1_SSD1306_SendCommand(column_high);  
        I2C1_SSD1306_SendCommand(0xB0 | (page + i));  
        I2C1_SendData(0x40);
        for(int j=0; j<16; j++) 
	    {
			I2C1_SendData(thermometer[num]);
            num++;
		}
        I2C1_Stop();
    }    
}

void DrawFrame(void)
{
    for(uint8_t PAGE=0; PAGE<8; PAGE++)
    {
		I2C1_Start();
        while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
        I2C1_SSD1306_SendCommand(0x02);  
        I2C1_SSD1306_SendCommand(0x10);  
        I2C1_SSD1306_SendCommand(0xB0 | PAGE);  
        I2C1_SendData(0x40);
        for(uint8_t i=0; i<128; i++) 
	    {
            if(i==0 || i==127)
			{
				I2C1_SendData(0xFF);
			}
			else
			{
				if(PAGE==0) I2C1_SendData(0x01);
				if(PAGE==7) I2C1_SendData(0x80);
				if(PAGE>0 && PAGE<7) I2C1_SendData(0x00);
			}
	    }
        I2C1_Stop();
    }    
}