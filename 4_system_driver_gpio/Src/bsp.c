#include "bsp.h"
#include "stm32f7xx.h"

#define LED_PORT GPIOB
#define LED_PORT_CLOCK (1U << 1)
#define LED_BLUE_PIN (1U << 7)
#define LED_BLUE_MODE_BIT (1U << 14)
#define LED_BLUE_PIN (1U << 7)

#define PUSH_BTN_PORT GPIOC
#define PUSH_BTN_CLOCK (1U << 2)
#define PUSH_BTN_PIN (1U << 13)


void led_init(void)
{
	RCC->AHB1ENR |= LED_PORT_CLOCK;
	LED_PORT->MODER |= LED_BLUE_MODE_BIT;
}


void led_on(void)
{
	LED_PORT->ODR |= LED_BLUE_PIN;
}

void led_off(void)
{
	LED_PORT->ODR &= ~LED_BLUE_PIN;
}

void button_init(void)
{
	RCC->AHB1ENR |= PUSH_BTN_CLOCK;
	PUSH_BTN_PORT->MODER &= ~(1U << 26); // Set PC13 as input
	PUSH_BTN_PORT->MODER &= ~(1U << 27); // Set PC13 as input
	PUSH_BTN_PORT->PUPDR &= ~(3U << 26);
}

bool get_button_state(void)
{
	if (PUSH_BTN_PORT->IDR & PUSH_BTN_PIN)
	{
		return false;
	}
	else
	{
		return true;
	}
}
