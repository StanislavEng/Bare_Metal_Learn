/*
 * Creating a UART driver for STM32L476RG
 * Using Nucleo Board, USB uses UART2 per the nucleo pin map
 * UART2 TX/RX are found on PA2/PA3
 * This is under AF7
 */

// Trying with printf
#include <stdio.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;

int main (void){

    uart2_tx_init();
    pc0_adc_init();


    while (1){
    		start_conversion();
    		sensor_value = adc_read();
    		printf("Sensor Value : %d \n\r", (int)sensor_value);

    		}



}



