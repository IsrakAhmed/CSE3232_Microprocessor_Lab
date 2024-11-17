# CSE3232 :: Microprocessor Lab


## Experiments

### 1. LED Blink Using Loop Delay
- **Description**: This example toggles an LED connected to GPIO pin PC13 using a simple loop delay. It is a basic method that relies on software delay.

### 2. LED Blink Using SysTick
- **Description**: This example configures the SysTick timer to create a delay, allowing the LED to toggle periodically. SysTick provides a more reliable timing solution than a loop delay.

### 3. LED Blink Using Timer 2 (TIM2)
- **Description**: This example utilizes Timer 2 to control the LED blink timing. It shows how to configure TIM2 and use its update event to toggle the LED.

### 4. Register-Level Programming with SysTick
- **Description**: This example demonstrates direct register manipulation for configuring the SysTick timer, providing an in-depth look at SysTick's operation at the hardware level.

### 5. Register-Level Programming with TIM2
- **Description**: Similar to the previous example, this code directly accesses hardware registers to configure TIM2, offering low-level control over the timer and LED blinking.