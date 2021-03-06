/*
 * uart.c
 *
 *  Created on: Mar 5, 2022
 *      Author: Stanislav
 */
#include "uart.h"

// PA2 and PA3 for USART2

#define GPIOAEN        	 	(1U<<0)
#define UART2EN            	(1U<<17)
// AF7
#define CR1_TE             	(1U<<3)
#define CR1_UE            	(1U<<0)

#define SR_TXE            	(1U<<7)

//#define SYS_FREQ         16000000 // this is default for F411 as found in data sheet

#define    APB1_CLK         SYS_FREQ



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);


//printf implementation
int __io_putchar(int ch){

	uart2_write(ch);
	return ch;
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
