#include <stdio.h>
#include "stm32f7xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"

uint32_t sensor_value;

bool btn_state;
int main(void)
{

	fpu_enable();
	debug_uart_init();

	timebase_init();

	led_init();

	button_init();

	pa3_adc_init();

	start_conversion();

	while (1)
    {
		btn_state = get_button_state();
		sensor_value = adc_read();
    }
}
