/*
 * timer_pwm.c
 *
 *  Created on: Jul 27, 2022
 *      Author: oscar
 */

#include "timer_pwm.h"

void TIM2_Init(void) {
	/*
	 * GPIO settings PA2
	 */
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);

	GPIOA->MODER &= ~(GPIO_MODER_MODE2_0);
	GPIOA->MODER |= (GPIO_MODER_MODE2_1);

	GPIOA->AFR[0] &= ~(0xF);
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL2_0);
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2_1);
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2_2);
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2_3);

	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR2);

	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2);
	/*
	 * Counter settings
	 */
	RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN);
	TIM2->CR1 &= ~(TIM_CR1_DIR);
	TIM2->PSC = 840 - 1; // 100 KHz = 0.1 MHz
	TIM2->ARR = 10 - 1; // 100 us
	/*
	 * PWM generation channel 3
	 */
	TIM2->CCMR2 &= ~(TIM_CCMR2_OC3M);
	TIM2->CCMR2 &= ~(TIM_CCMR2_OC3M_0);
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_1);
	TIM2->CCMR2 |= (TIM_CCMR2_OC3M_2);
	TIM2->CCMR2 |= (TIM_CCMR2_OC3PE);

	TIM2->CCER &= ~(TIM_CCER_CC3P);
	TIM2->CCER &= ~(TIM_CCER_CC3NP);
	TIM2->CCER |= (TIM_CCER_CC3E);

	TIM2->CR1 |= (TIM_CR1_CEN);
}
