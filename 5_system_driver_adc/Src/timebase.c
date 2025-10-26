#include "timebase.h"
#include "stm32f7xx.h"

#define CTRL_ENABLE    (1U<<0)
#define CTRL_TICKINT   (1U<<1)
#define CTRL_CLKSRC    (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

#define ONE_SEC_LOAD   16000000
#define TICK_FREQ      1
#define MAX_DELAY      0xFFFFFFFF

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

void timebase_init(void)
{
	__disable_irq();
	SysTick->LOAD = ONE_SEC_LOAD - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = CTRL_CLKSRC;
	SysTick->CTRL |= CTRL_TICKINT;
	SysTick->CTRL |= CTRL_ENABLE;
	__enable_irq();
}

void delay(uint32_t delay)
{
	uint32_t tickstart = get_ticks();
	uint32_t wait = delay;

	if (wait < MAX_DELAY)
	{
		wait += (uint32_t)TICK_FREQ;
	}

	while (get_ticks() - tickstart < wait)
	{
	}
}

uint32_t get_ticks(void)
{
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick_p;
}

static void tick_increment(void)
{
	g_curr_tick += TICK_FREQ;
}

void SysTick_Handler(void)
{
	tick_increment();
}
