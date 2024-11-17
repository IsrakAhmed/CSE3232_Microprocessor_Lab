#define RCC_BASE			0x40021000
#define GPIOC_BASE		0x40011000
#define SysTick_BASE	0xE000E010

#define RCC_APB2ENR 	(*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR 	(*(volatile unsigned int *)(RCC_BASE + 0x1C))
#define RCC_CFGR        (*(volatile unsigned int*)(RCC_BASE+0x04))

#define GPIOC_CRH   	(*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR   	(*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define SysTick_LOAD  (*(volatile unsigned int *)(SysTick_BASE + 0x04))
#define SysTick_CTRL  (*(volatile unsigned int *)(SysTick_BASE + 0x00))


void configure_clock(){
	
	RCC_CFGR &= ~(3 << 0);
	
	while((RCC_CFGR & (3 << 2)) != (0 << 2));
	
}


void delay(int miliseconds){
	
	SysTick_LOAD = miliseconds;
	
	SysTick_CTRL |= 0x5;
	
	// while(!(SysTick->CTRL & (1<<15)));
	
	while((SysTick_CTRL & 0x10000) == 0);
	
	SysTick_CTRL &= 0;
	
}


int main(){
	
	configure_clock();
	
	RCC_APB2ENR |= (1<<4);
	GPIOC_CRH ^= (1<<22);
	GPIOC_CRH = (3<<20);
	
	while(1){
		
		GPIOC_ODR ^= (1<<13);
		
		int time = 1500;
		
		for(int i = 0; i < time; i++){
			delay(time);
		}
		
	}

}