/* Настраиваем следующие ноги:
PB6 - SCL I2C1 Для экрана
PB7 - SDA I2C1
PA6 - CH1 TIM3 Для энкодера
PA7 - CH2 TIM3 ------
*/
#include "main.h"
#include "i2c.h"
#include "ssd1306.h"

int main(void)
{
    TIM3_Init(); 				// Настраиваем таймер TIM3 в режиме энкодера
	I2C1_Init(I2C_FAST);		// Настраиваем I2C1 как мастер для SH1106 400KHz
	I2C1_SSD1306_Init();		// Инициализируем дисплей
    I2C1_SSD1306_Clear();		// Очищаем дисплей от мусора

// Рисуем рамку
	DrawFrame();
// Рисуем термометр
	DrawThermometre(2, 1);	
    while (1)
	{
		int num = 0;
		for (int sym = 0; sym<10; sym++)
		{
			num = 0;
		for(int i = 0; i < 5; i++)
   		{
			I2C1_Start();
			while (I2C1_SendAddress(I2C_ADDRESS, I2C_TRANSMITTER) == I2C_ERROR) {}
			I2C1_SSD1306_SendCommand(0x06);  
	        I2C1_SSD1306_SendCommand(0x12);  
			I2C1_SSD1306_SendCommand(0xB0 | (1 + i));  
			I2C1_SendData(0x40);
			for(int j=0; j<24; j++) 
			{
				I2C1_SendData(MegaNumbers[sym][num]);
			num++;
			}
			I2C1_Stop();
		}    
		for(uint32_t k=0; k<9000000; k++){__NOP();}
		}
		}
	return 1;
	}

void TIM3_Init()
{
	// Настраиваем выводы для входа энкодера PA6 - CH1 TIM3, PA7 - CH2 TIM3
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		         	//Включаем порт A
	GPIOA->CRL &= ~(GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0);	//Выводы PA6, PA7 - как вход
	GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1;	//Выводы PA6, PA7 - pull-up
	GPIOA->ODR |= GPIO_ODR_ODR6 | GPIO_ODR_ODR7;		//Согласно таблице на стр.161 RM0008

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;					// Включаем TIM3
	TIM3->CCMR1 |= TIM_CCMR1_IC1F | TIM_CCMR1_IC2F; 	// Включаем фильтр дребезга контактов
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;	// Включаем канал 1 и 2 TIM3 как входы
	TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);		// Счёт по фронту сигнала (можно не делать, это по умолчанию)
	TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;		// Счет по фронту канала 1 и 2

	TIM3->ARR = 450;			// До скольки считать
	TIM3->CNT = 0;				// Счетчик регистра
	TIM3->CR1 |= TIM_CR1_CEN;	//Включаем счет TIM3
}