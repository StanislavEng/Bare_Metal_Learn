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

#define PERIPH_BASE 		(0x40000000UL) // GPIOs are found in the peripheral memory area

// GPIO A memory location is found on AHB2
#define AHB2_OFFSET 		(0x08000000UL) // offset of AHB2 from peripheral base
#define AHB2_BASE			(PERIPH_BASE + AHB2_OFFSET)

// RCC memory location is found on AHB1
#define AHB1_OFFSET			(0x00020000UL) // offset of AHB1 from peripheral base
#define AHB1_BASE			(PERIPH_BASE + AHB1_OFFSET)

// RCC Register Location
#define RCC_OFFSET			(0x1000UL)
#define RCC					(AHB1_BASE + RCC_OFFSET)

// Enable register for AHB2 peripheral clock
#define AHB2EN_R_OFFSET		(0x4CUL) // AHB2EN offset for RCC
#define RCC_AHB2_EN_R		(*(volatile unsigned int *)(RCC + AHB2EN_R_OFFSET))

// GPIOA Register Location
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA				(AHB2_BASE + GPIOA_OFFSET)

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

/*
 * GPIO pin 5 is found at pins 10 and 11
 * output is set as 01
 * |= (1U<<10)
 * &=~(1U<<11)
 */

int main (void){
	// 1. Enable peripheral clock
	RCC_AHB2_EN_R |= GPIOA_EN;

	// 2. Enable output on GPIOA
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~(1U<<11);

	// 3. Enable bit on and off
	while(1){
//		 GPIOA_OD_R |= LED_PIN; // set pin 5
		GPIOA_OD_R ^= LED_PIN; // toggle pin 5
		for(int i = 0; i<300000;i++){} // arbitrary delay
	}

}
