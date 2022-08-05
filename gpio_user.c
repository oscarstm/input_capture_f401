/*
 * gpio_user.c
 *
 *  Created on: Aug 4, 2022
 *      Author: oscar
 */

#include "gpio_user.h"

void GPIO_PC13_Init(void) {
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN);

	GPIOC->MODER &= ~(GPIO_MODER_MODE13);
	GPIOC->MODER |= (GPIO_MODER_MODER13_0);
	GPIOC->MODER &= ~(GPIO_MODER_MODER13_1);

	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT13);

	GPIOC->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR13);

	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR13);
}
