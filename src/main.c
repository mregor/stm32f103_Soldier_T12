#include "stm32f10x.h"
#include "main.h"
#include "i2c.h"

int main(void)
{
    TIM3_Init(); // Настраиваем таймер TIM3 в режиме энкодера
	I2C_Init(I2C_STANDARD);  // Настраиваем I2C1 как мастер для SH1106
    while (1){}
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

	TIM3->ARR = 40;		// До скольки считать
	TIM3->CNT = 0;		// Счетчик регистра
	TIM3->CR1 |= TIM_CR1_CEN;	//Включаем счет TIM3
}	