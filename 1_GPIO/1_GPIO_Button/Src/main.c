#include "stm32l4xx.h"

/*
 * LED pin on PA5
 * Button pin on PC13
 */

#define GPIOAEN				(1U<<0)
#define GPIOCEN				(1U<<2)

#define PIN5				(1U<<5)
#define LED_PIN				PIN5

#define PIN13				(1U<<13)
#define PB_PIN				PIN13


int main (void){

	RCC->AHB2ENR |= GPIOAEN;
	RCC->AHB2ENR |= GPIOCEN;

	GPIOA->MODER |= (1<<10);
	GPIOA->MODER &=~(1<<11);

	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while(1){
		//Version 1 --> Push button to turn LED ON, else off
		if(GPIOC->IDR & PB_PIN){
			GPIOA->BSRR |= (LED_PIN<<16);
		}
//		GPIOA->BSRR |= LED_PIN;
//		GPIOA->ODR ^= LED_PIN;
//		for(int i = 0;i<50000;i++){}
		else {
			GPIOA->BSRR |= (LED_PIN);
		}
//		GPIOA->BSRR |= (LED_PIN<<16);
//		for(int i = 0;i<50000;i++){}


/*		// Version 2 --> Push button to change speed of LED // I think this only works using interrupt

		if (GPIOC->IDR & PB_PIN){
			GPIOA->BSRR |= LED_PIN;
			for(int i = 0;i<50000;i++){}
//			for(int i =0; i < speed; i++){}
			GPIOA->BSRR |= (LED_PIN<<16);
			for(int i = 0;i<50000;i++){}
//			for(int i =0; i < speed; i++){}
		}
		else{
			if (speed == 100000){
				speed = 10000;
			}
			else
				speed = 100000;
		}
*/	}

}


