#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000
#define TIM2_BASE       0x40000000

/*
	RCC_APB1ENR: Register that enables clocks for peripherals connected to the APB1 bus (includes TIM2).
*/
#define RCC_APB1ENR     (*(volatile unsigned long *)(RCC_BASE + 0x1C))

/*
	RCC_APB2ENR: Register that enables clocks for peripherals connected to the APB2 bus (includes GPIOC).
*/
#define RCC_APB2ENR     (*(volatile unsigned long *)(RCC_BASE + 0x18))

/*
	GPIOC_CRH: Register that controls the configuration (input/output, speed, etc.) of the higher GPIO pins (8-15) on Port C.
*/
#define GPIOC_CRH       (*(volatile unsigned long *)(GPIOC_BASE + 0x04))

/*
	GPIOC_ODR: Register that controls the output data for GPIO Port C pins.
*/
#define GPIOC_ODR       (*(volatile unsigned long *)(GPIOC_BASE + 0x0C))

/*
	TIM2_CR1: Control register 1 for TIM2, used to enable or disable the timer.
*/
#define TIM2_CR1        (*(volatile unsigned long *)(TIM2_BASE + 0x00))

/*
	TIM2_SR: Status register for TIM2. It contains flags like the update flag (UIF) to indicate timer events.
*/
#define TIM2_SR         (*(volatile unsigned long *)(TIM2_BASE + 0x10))

/*
	TIM2_PSC: Prescaler register for TIM2. This divides the clock frequency to create a slower clock for the timer.
*/
#define TIM2_PSC        (*(volatile unsigned long *)(TIM2_BASE + 0x28))

/*
	TIM2_ARR: Auto-reload register for TIM2. This defines the period of the timer (when it resets).
*/
#define TIM2_ARR        (*(volatile unsigned long *)(TIM2_BASE + 0x2C))



void delay(volatile unsigned int ms){

	
		/*
			TIM2_PSC = 8000: This sets the prescaler to 8000, which means the timer will count every 8000 clock cycles.
			Assuming the clock is running at 8 MHz, this will reduce the frequency to 1 kHz (1 ms per tick).
		*/
    TIM2_PSC = 8000;				// Set the prescaler to 8000, slowing down the timer clock.

    TIM2_ARR = ms;					// Set the auto-reload value to the delay time in milliseconds.
	
    TIM2_SR &= ~(1);				// Clear the update flag (UIF) to ensure it's ready to count.
	
    TIM2_CR1 |= 1;					// Enable the timer by setting the CEN (counter enable) bit.
	
    while(!(TIM2_SR & 1));	// Wait until the update flag (UIF) is set (indicating the timer has reached the count).
	
    TIM2_CR1 &= ~(1);				// Disable the timer by clearing the CEN bit.


}


int main(){

	/*
		RCC_APB2ENR |= 0x10; Enables the clock for GPIOC by setting the 4th bit (0x10) in the APB2 peripheral enable register.
	*/
	RCC_APB2ENR |= 0x10;  // Enable GPIOC clock
	
	
	/*
		RCC_APB1ENR |= 1; Enables the clock for TIM2 by setting the first bit (0x1) in the APB1 peripheral enable register.
	*/
	RCC_APB1ENR |=  1 ;  // Enable TIM2 clock


	/*
		GPIOC_CRH &= 0x0FFFFF; Clears the bits for configuring pin PC13 (bits 23 to 20) by ANDing with a mask.
		This ensures the configuration for PC13 is ready to be set without affecting other bits.
	*/
	GPIOC_CRH &= 0x0FFFFF;
	
	
	/*
		GPIOC_CRH |= 0x300000; Configures PC13 as a general-purpose output, push-pull mode,
		by setting bits 21 and 20 to 0b11 (binary) and the speed to 2 MHz.
	*/
	GPIOC_CRH |= 0x300000;


	while(1){

		/*
			GPIOC_ODR ^= (1<<13); Toggles the output data register bit for pin PC13.
			This bitwise XOR operation changes the state of the pin, turning the LED on or off.
		*/
		GPIOC_ODR ^= (1<<13);
		
		
		/*
			delay(5000); Waits for 5000 ms (5 second) by using Timer 2.
		*/
		delay(5000);
		
	}

	return 0;

}












