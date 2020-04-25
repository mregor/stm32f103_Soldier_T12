#ifndef __I2C_H 
#define __I2C_H 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __STM32F10x_H
#include "stm32f10x.h"
#endif

typedef enum {
	I2C_STANDARD,	/*!< Стандартный режим 100 KHz  */
	I2C_FAST		/*!< Быстрый режим 400 KHz */
} I2C_Mode_Type;

typedef enum {
	I2C_TRANSMITTER,
	I2C_RECEIVER
} I2C_Direction_Type;

typedef enum {
	I2C_ACK,
	I2C_NACK
} I2C_Acknowledge_Type;

typedef enum {
	I2C_ERROR = 0x0,
	I2C_OK
} I2C_Status_Type;

void I2C1_Init(I2C_Mode_Type mode);
void I2C1_Start(void);
void I2C1_Stop(void);
I2C_Status_Type I2C1_SendAddress(uint8_t address, I2C_Direction_Type direction);
void I2C1_SendData(uint8_t data);
uint8_t I2C1_ReceiveData(I2C_Acknowledge_Type acknowledge);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_H*/