#include "uart.h"
#include "stm32f7xx.h"

#define DBG_UART_BAUDRATE  115200
#define SYS_FREQ           16000000
#define APB1_CLK           SYS_FREQ

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);


int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void debug_uart_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //0x20000;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //0x01;

	GPIOD->MODER|=GPIO_MODER_MODER8_1; // TX (PIN8) set to AF
#define AF07 0x07
	GPIOD->AFR[1]|=(AF07<<0);

	GPIOD->MODER|=GPIO_MODER_MODER9_1;
	GPIOD->AFR[1]|=(AF07<<4);

	uart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);

	// control register enable TX and RX
	USART3->CR1    = 0;
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE; //0x000C;

	// enable uart
	USART3->CR1 |= USART_CR1_UE; //0x2000;
}

static void uart_write(int ch)
{
	while (!(USART3->ISR & USART_ISR_TXE_Msk));
	USART3->TDR = (ch & 0xFF);
}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART3->BRR = compute_uart_bd(periph_clk, baudrate);
}
