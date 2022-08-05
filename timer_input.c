/*
 * timer_input.c
 *
 *  Created on: Aug 4, 2022
 *      Author: oscar
 */

#include "timer_input.h"

void TIM3_Init(void) {
	/*
	 * GPIO settings PB0
	 */
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN);

	GPIOB->MODER &= ~(GPIO_MODER_MODE0_0);
	GPIOB->MODER |= (GPIO_MODER_MODE0_1);

	GPIOB->AFR[0] &= ~(0xF);
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL0_0);
	GPIOB->AFR[0] |= (GPIO_AFRL_AFRL0_1);
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL0_2);
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL0_3);

	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0);

	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD0);
	/*
	 * Counter settings
	 */
	RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);

	TIM3->PSC = 84 - 1; // CK_CNT = 1 MHz
	TIM3->ARR = 65536 - 1;
	/*
	 * Input capture channel 3
	 */
	TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S);
	TIM3->CCMR2 |= (TIM_CCMR2_CC3S_0);
	TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S_1);
	TIM3->CCMR2 &= ~(TIM_CCMR2_IC3PSC);
	TIM3->CCMR2 &= ~(TIM_CCMR2_IC3F);

	TIM3->CCER |= (TIM_CCER_CC3P);
	TIM3->CCER |= (TIM_CCER_CC3NP);
	TIM3->CCER |= (TIM_CCER_CC3E);

	TIM3->DIER |= (TIM_DIER_CC3IE);

	TIM3->CR1 |= (TIM_CR1_CEN);

	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
}
