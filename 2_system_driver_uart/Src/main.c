#include <stdio.h>
#include "stm32f7xx.h"
#include "fpu.h"
#include "uart.h"


int main(void)
{

	fpu_enable();
	debug_uart_init();

	while (1)
    {
		printf("Staring up ...\n\r");

		for (int i = 0; i < 9000; ++i)
		{

		}
    }
}
