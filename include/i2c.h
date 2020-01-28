/* Настраиваем следующие ноги:
PB8 - SCL I2C1 Для экрана
PB9 - SDA I2C1
*/
#ifndef __I2C_H 
#define __I2C_H 

typedef enum {
	I2C_STANDARD,
	I2C_FAST
} I2C_Mode_Type;


void I2C_Init(I2C_Mode_Type mode);

#endif