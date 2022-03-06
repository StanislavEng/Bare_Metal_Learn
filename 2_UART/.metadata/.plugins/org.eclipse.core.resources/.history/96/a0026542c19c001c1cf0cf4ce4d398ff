/*
 * Creating a UART driver for STM32L476RG
 * Using Nucleo Board, USB uses UART2 per the nucleo pin map
 * UART2 TX/RX are found on PA2/PA3
 * This is under AF7
 */

#include "stm32l4xx.h"

#define GPIOAEN				(1U<<0)
#define UART2EN				(1U<<17) // UART2 Enable on APB1





int main (void) {

	while(1){

	}

}

void uart2_tx_init(void){
	/************** Configure UART GPIO Pin ***************/
	/* Enable Clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to alternate function mode */
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &=~(1U<<4);

	/* Set PA2 alternate function type to UART_TX (A7) */
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/************** Configure UART module ***************/
	/* Enable Clock access to UART2 */
	RCC->APB1ENR |= UART2EN;

	/*configure baudrate */

	/* configure the transfer direction */

	/* Enable Uart Module */


}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate){

	return ((PeriphClk + (BaudRate/2U)/BaudRate)
}

