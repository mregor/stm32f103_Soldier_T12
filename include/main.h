/* Настраиваем следующие ноги:
PB8 - SCL I2C1 Для экрана
PB9 - SDA I2C1
PA6 - CH1 TIM3 Для энкодера
PA7 - CH2 TIM3 ------
*/


#ifndef __MAIN_H 
#define __MAIN_H 

void TIM3_Init(void);

#endif