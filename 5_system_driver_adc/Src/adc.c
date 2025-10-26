#include <adc.h>
#include "stm32f7xx.h"

#define GPIOAEN        (1U << 0)
#define ADC1EN         (1U << 8)
#define ADC_CH3	       3U
#define ADC_SEQ_LEN_1  0x00
#define CR2_ADCON      (1U << 0)
#define CR2_CONT 	   (1U << 1)
#define CR2_SWSTART    (1U << 30)
#define SR_EOC         (1U << 1)


void pa3_adc_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U << 6);
	GPIOA->MODER |= (1U << 7);
	RCC->APB2ENR |= ADC1EN;
	ADC1->SQR3 = ADC_CH3;
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->CR2 |= CR2_ADCON;
}

void start_conversion(void)
{
	ADC1->CR2 |= CR2_CONT;
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	while (!(ADC1->SR & SR_EOC))
	{}

	return ADC1->DR;
}


