#include "stm32l4xx.h"


#define GPIOCEN 		(1U<<2)
// enable ADC on RCC
#define ADCEN			(1U<<13)

// PC0 is ADC 1, 2 and 3 channel 1
#define ADC_CH0			(1U<<0)

#define ADC_SEQ_LEN1 	0x00

#define CR_ADON 		(1U<<0)


void pc0_adc_init(void){

	/*** Configure the ADC GPIO pin ***/

	/* Enable clock access to GPIOC*/
	RCC->AHB2ENR |= GPIOCEN;

	/* Set the mode of PC0 to Analog*/
	GPIOC->MODER |= (1U<<0);
	GPIOC->MODER |= (1U<<1);

	/*** Configure the ADC Module ***/

	/* Enable clock access to ADC*/
	RCC->AHB2ENR |= ADCEN;

	/* Conversion sequence start */
	ADC1->SQR1  =~ADC_CH0;

	/* Conversion Sequence Length */
	ADC1->SQR1 |= ADC_SEQ_LEN1;

	/* Enable ADC module*/
	ADC->CR |= CR_ADON;

}