/*
 * adc.h
 *
 *  Created on: Mar 8, 2022
 *      Author:
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pc0_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
