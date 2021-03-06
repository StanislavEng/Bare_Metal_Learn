/*
 * Creating a UART driver for STM32L476RG
 * Using Nucleo Board, USB uses UART2 per the nucleo pin map
 * UART2 TX/RX are found on PA2/PA3
 * This is under AF7
 */

// Trying with printf
#include <stdio.h>
#include "uart.h"

#define GPIOAEN 			(1U<<0)
#define GPIOA_5				(1U<<5)

#define LED_PIN				GPIOA_5

char key;

int main (void){

	/* Enable Clock Access to GPIOA */
	RCC->AHB2ENR |= GPIOAEN;

	/* Set PA5 (LED) as output */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

    uart2_rx_tx_init();

    while (1){

    	key = uart2_read();
    	if (key == '1'){
    		GPIOA->ODR |= LED_PIN;
    	}
    	else{
    		GPIOA->ODR &=~LED_PIN;
    	}

    		}



}



