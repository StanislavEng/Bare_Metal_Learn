/*
 * Example 1 --> LED BLink
 *
 * Description:
 * After many attempts not working, I have found the source of my error
 * With now a working understanding starting the learning
 * Made this work on easier to use F429
 * Switching to L476 to match the family used by the IoT Dev Kit
 *
 * Nucleo LED on PA5
 *
 * Date: Feb 20, 2022
 *
 */

// LED on GPIOA Pin 5

#include <stdint.h>

#define PERIPH_BASE 		(0x40000000UL) // GPIOs are found in the peripheral memory area

// GPIO A memory location is found on AHB2
#define AHB2_OFFSET 		(0x08000000UL) // offset of AHB2 from peripheral base
#define AHB2_BASE			(PERIPH_BASE + AHB2_OFFSET)

// RCC memory location is found on AHB1
#define AHB1_OFFSET			(0x00020000UL) // offset of AHB1 from peripheral base
#define AHB1_BASE			(PERIPH_BASE + AHB1_OFFSET)

// RCC Register Location
#define RCC_OFFSET			(0x1000UL)
#define RCC_BASE			(AHB1_BASE + RCC_OFFSET)

// Enable register for AHB2 peripheral clock
#define AHB2EN_R_OFFSET		(0x4CUL) // AHB2EN offset for RCC
#define RCC_AHB2_EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB2EN_R_OFFSET))

// GPIOA Register Location
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB2_BASE + GPIOA_OFFSET)

// MODE register location
#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R 		(*(volatile unsigned int *)(AHB2_BASE + MODE_R_OFFSET))

// output direction register (ODR) location
#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(AHB2_BASE + OD_R_OFFSET))

/////////// Enable bits
#define GPIOA_EN			(1U<<0) // put bit 1 in array location 0 to enable GPIO A

#define PIN5				(1U<<5) // location of PIN5
#define LED_PIN				PIN5

#define __IO volatile

typedef struct {

	__IO uint32_t MODE_R;
	__IO uint32_t OTYPE_R;
	__IO uint32_t OSPEED_R;
	__IO uint32_t PUPD_R;
	__IO uint32_t ID_R;
	__IO uint32_t OD_R;
	__IO uint32_t BSR_R;
	__IO uint32_t LCK_R;
	__IO uint32_t AF_R[2];
	__IO uint32_t BR_R;
	__IO uint32_t ASC_R;

}GPIO_TypeDef ;

typedef struct {
	/*
	 * RCC_CR --> 0x00
	 * ICSCR  --> 0x04
	 * CFGR   --> 0x08
	 * PLLCFGR--> 0x0C
	 * PLLSAI1--> 0x10
	 * PLLSAI1--> 0x14
	 * CIER   --> 0x18
	 * CIFR   --> 0x1C
	 * CICR   --> 0x20
	 * RESERVE--> 0x24
	 * AHB1RE --> 0x28
	 * AHB2RE --> 0x2C
	 * AHB3RE --> 0x30
	 * RESERVE--> 0x34
	 * APB1RE1--> 0x38
	 * APB1RE2--> 0x3C
	 * APB2RE --> 0x40
	 * RESERVE--> 0x44
	 * AHB1EN --> 0x48
	 * AHB2EN --> 0x4C
	 */

	uint32_t DUMMY[19];
	__IO uint32_t AHB1EN_R;

}RCC_TypeDef;

#define RCC				((RCC_TypeDef *) 	 RCC_BASE)
#define GPIOA			((GPIO_TypeDef *) GPIOA_BASE)

/*
 * GPIO pin 5 is found at pins 10 and 11
 * output is set as 01
 * |= (1U<<10)
 * &=~(1U<<11)
 */

int main (void){
	// 1. Enable peripheral clock
	//RCC_AHB2_EN_R |= GPIOA_EN;
	RCC->AHB1EN_R |= GPIOA_EN;

	// 2. Enable output on GPIOA
	//GPIOA_MODE_R |= (1U<<10);
	//GPIOA_MODE_R &=~(1U<<11);
	GPIOA->MODE_R |= (1U<<10);
	GPIOA->MODE_R &=~(1U<<11);

	// 3. Enable bit on and off
	while(1){
//		 GPIOA_OD_R |= LED_PIN; // set pin 5
//		GPIOA_OD_R ^= LED_PIN; // toggle pin 5
		GPIOA->BSR_R |= PIN5; 			// set bit, bit 5 of BSR
		for(int i = 0; i<100000;i++){} // arbitrary delay
		GPIOA->BSR_R |= (PIN5<<16);		// reset bit, bit 21 (5 + 16) of BSR
		for(int i = 0; i<100000;i++){} // arbitrary delay
	}

}

