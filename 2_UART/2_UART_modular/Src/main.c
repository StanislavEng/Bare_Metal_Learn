/*
 * Creating a UART driver for STM32L476RG
 * Using Nucleo Board, USB uses UART2 per the nucleo pin map
 * UART2 TX/RX are found on PA2/PA3
 * This is under AF7
 */

// Trying with printf
#include <stdio.h>
#include "uart.h"

int main (void){

    uart2_tx_init();

    while (1){
//        uart2_write('Y');
    	printf("Hello from STM32L4..........\n\r");
    	for (int i = 0; i < 100000; i++){
    		if (i == 50000){
    			printf("timer break\n\r");
    		}
    	}

    }

}



