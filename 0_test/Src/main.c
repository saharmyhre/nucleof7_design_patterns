#include "stm32f7xx.h"

#define LED_PORT GPIOB
#define LED_PORT_CLOCK (1U << 1)

#define LED_RED_PIN (1U<<14)
#define LED_GREEN_PIN (1U<<0)
#define LED_BLUE_PIN (1U<<7)

#define LED_RED_MODE_BIT (1U<<28)
#define LED_GREEN_MODE_BIT (1U<<0)
#define LED_BLUE_MODE_BIT (1U<<14)

int main(void)
{
    RCC->AHB1ENR |= LED_PORT_CLOCK;

    LED_PORT->MODER |= LED_RED_MODE_BIT;
    LED_PORT->MODER |= LED_GREEN_MODE_BIT;

	while (1)
    {
		LED_PORT->ODR ^= LED_RED_PIN;
		for (int i = 0; i < 100000; ++i)
		{}
		LED_PORT->ODR ^= LED_GREEN_PIN;
    }
}
