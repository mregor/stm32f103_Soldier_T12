#ifndef __SSD1306_H 
#define __SSD1306_H 

#ifndef __STM32F10x_H
#include "stm32f10x.h"
#endif

#ifndef __I2C_H
#include "i2c.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define I2C_ADDRESS     ((uint8_t)0x3C)

void SSD1306_Init();
void I2C1_SendCommand(uint8_t data);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SSD1306_H*/