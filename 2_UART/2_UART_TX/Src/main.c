/*
 * Creating a UART driver for STM32L476RG
 * Using Nucleo Board, USB uses UART2 per the nucleo pin map
 * UART2 TX/RX are found on PA2/PA3
 * This is under AF7
 */
//#include <stdint.h>
//#include "stm32l4xx.h"
//
//#define GPIOAEN				(1U<<0)
//#define UART2EN				(1U<<17) // UART2 Enable on APB1
//
//
//
//
//
//int main (void) {
//
//	while(1){
//
//	}
//
//}
//
//void uart2_tx_init(void){
//	/************** Configure UART GPIO Pin ***************/
//	/* Enable Clock access to GPIOA */
//	RCC->AHB1ENR |= GPIOAEN;
//
//	/* Set PA2 mode to alternate function mode */
//	GPIOA->MODER |= (1U<<5);
//	GPIOA->MODER &=~(1U<<4);
//
//	/* Set PA2 alternate function type to UART_TX (A7) */
//	GPIOA->AFR[0] |= (1U<<8);
//	GPIOA->AFR[0] |= (1U<<9);
//	GPIOA->AFR[0] |= (1U<<10);
//	GPIOA->AFR[0] &=~(1U<<11);
//
//	/************** Configure UART module ***************/
//	/* Enable Clock access to UART2 */
//	RCC->APB1ENR1 |= UART2EN;
//
//	/*configure baudrate */
//
//	/* configure the transfer direction */
//
//	/* Enable Uart Module */
//
//
//}
//
//static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate){
//
//	return ((PeriphClk + (BaudRate/2U))/BaudRate);
//}

#include <stdint.h>
#include "stm32l4xx.h"

// Trying with printf
#include <stdio.h>

// PA2 and PA3 for USART2

#define GPIOAEN        	 	(1U<<0)
#define UART2EN            	(1U<<17)
// AF7
#define CR1_TE             	(1U<<3)
#define CR1_UE            	(1U<<0)

#define SR_TXE            	(1U<<7)

//#define SYS_FREQ         16000000 // this is default for F411 as found in data sheet
#define SYS_FREQ			4000000 // default for L476 as found in the reference manual
#define    APB1_CLK         SYS_FREQ

#define UART_BAUDRATE     	115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init (void);
void uart2_write(int ch);

//printf implementation
int __io_putchar(int ch){

	uart2_write(ch);
	return ch;
}


int main (void){

    uart2_tx_init();

    while (1){
        //uart2_write('Y');
    	printf("Hello from STM32L4..........\n\r");
    }

}

void uart2_tx_init (void){

    /*************** Configure UART GPIO PIN **************/

    /* Enable Clock Access to GPIOA */
    RCC->AHB2ENR |= GPIOAEN;

    /* Set PA2 mode to alternate function mode */
    GPIOA->MODER &=~(1<<4);
    GPIOA->MODER |= (1<<5);

    /* Set PA2 alternate function type to UART_TX (AF07)*/
    GPIOA->AFR[0] |= (1<<8);
    GPIOA->AFR[0] |= (1<<9);
    GPIOA->AFR[0] |= (1<<10);
    GPIOA->AFR[0] &=~(1<<11);

    /*************** Configure UART Module **************/
    /* Enable clock access to UART */
    RCC->APB1ENR1 |= UART2EN;

    /* Configure UART Baud Rate */
    uart_set_baudrate(USART2, APB1_CLK,UART_BAUDRATE);

    /* Configure the transfer direction */
    USART2->CR1 = CR1_TE;

    /* Enable UART Module */
    USART2->CR1 |= CR1_UE;

}

void uart2_write(int ch){
    /* Make sure transmit register is empty */
    while(!(USART2->ISR & SR_TXE)){}

    /* Write to transmit data register */
    USART2->TDR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){

    USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){

    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
