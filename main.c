#include "stm32f4xx.h"
#include "clk_user.h"
#include "timer_pwm.h"
#include "timer_input.h"
#include "gpio_user.h"

volatile uint32_t pulse_width = 0;
volatile uint32_t last_captured = 0;
volatile uint32_t signal_polarity = 0;
volatile uint32_t distance = 0;

int main(void) {
	clk_user();
	TIM2_Init();
	TIM3_Init();
	GPIO_PC13_Init();

	while (1) {
		TIM2->CCR3 = 1; // 10%

		if (distance <= 20) {
			GPIOC->ODR |= (GPIO_ODR_ODR_13);
		} else {
			GPIOC->ODR &= ~(GPIO_ODR_ODR_13);
		}
	}

}

void TIM3_IRQHandler(void) {
	uint32_t current_captured;

	if ((TIM3->SR & (TIM_SR_CC3IF)) != 0) {
		current_captured = TIM3->CCR3;
		signal_polarity = 1 - signal_polarity;

		if (signal_polarity == 0) {
			pulse_width = current_captured - last_captured;
			distance = pulse_width / 58;
		}
		last_captured = current_captured;
	}

	if ((TIM3->SR & (TIM_SR_UIF)) != 0) {
		TIM3->SR &= ~(TIM_SR_UIF);
	}
}

