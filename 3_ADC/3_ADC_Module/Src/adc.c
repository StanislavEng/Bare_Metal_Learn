#include "stm32l4xx.h"


#define GPIOCEN 		(1U<<2)
// enable ADC on RCC
#define ADCEN			(1U<<13)

// PC0 is ADC 1, 2 and 3 channel 1
#define ADC_CH1			(1U<<1)

#define ADC_SEQ_LEN1 	0x00

#define CR_ADON 		(1U<<0)
#define ADC_START		(1U<<2)
#define ADC_EOC 		(1U<<2)

void pc0_adc_init(void){

	ADC1->CR = 0x00;
	/*** Configure the ADC GPIO pin ***/
	ADC1->CR &=~(1U<<29);
	ADC1->CR |= (1U<<28);
	/* Enable clock access to GPIOC*/
	RCC->AHB2ENR |= GPIOCEN;

	/* Set the mode of PC0 to Analog*/
	GPIOC->MODER |= (1U<<2);
	GPIOC->MODER |= (1U<<3);

	/*** Configure the ADC Module ***/

	/* Enable clock access to ADC*/
	RCC->AHB2ENR |= ADCEN;


	/* Conversion Sequence Length */
	ADC1->SQR1 = ADC_SEQ_LEN1;

	/* Conversion sequence start */
	ADC1->SQR1  = ADC_CH1;

	/* Enable ADC module*/
	ADC1->ISR |= (1U<<0);
	ADC1->CR |= CR_ADON;
	while (!(ADC1->ISR & (1U<<0))){}

}

void start_conversion(void){
	/* Start ADC conversion */

	ADC1->CR |= ADC_START;

}

uint32_t adc_read(void){
	/* Wait for conversion to be complete */
	while(!(ADC1->ISR & ADC_EOC)){}

	/* Read converted result */
	return (ADC1->DR);

}




