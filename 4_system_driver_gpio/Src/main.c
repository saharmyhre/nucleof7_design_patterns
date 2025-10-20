#include <stdio.h>
#include "stm32f7xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"

bool btn_state;
int main(void)
{

	fpu_enable();
	debug_uart_init();

	timebase_init();

	led_init();

	button_init();

	while (1)
    {
		btn_state = get_button_state();
    }
}
