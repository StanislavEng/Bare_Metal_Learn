/*
 * uart.h
 *
 *  Created on: Mar 5, 2022
 *      Author: Stanislav
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32l4xx.h"

#define SYS_FREQ			4000000 // default for L476 as found in the reference manual

#define UART_BAUDRATE		115200
//void uart2_write(int ch);

void uart2_tx_init (void);
void uart2_write(int ch);


#endif /* UART_H_ */

