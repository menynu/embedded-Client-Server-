#include "stm32f303xe.h"
#include "led.h"
#include "scheduler.h"
#include "usart3.h"
#include "usart2.h"


static unsigned char led_status;


void LED_init(void)
{
	led_status = 0;
    // Enable the GPIOA clock.
    RCC->AHBENR |= 0x00020000;
    // Configure PA5 as output
    // (by default it will then be push pull, see p. 237 of the reference manual).
    GPIOA->MODER |= 0x00000400;
}




void LED_off(void)
{
	GPIOA->ODR &= ~0x00000020;
}




void LED_on(void)
{
    GPIOA->ODR |= 0x00000020;
}




void LED_toggle(void)
{
	GPIOA->ODR ^= 0x00000020;
}

void LED_action(){
	USART2_print("The blue button has pressed on Client side\n");
	led_status++;
	if (led_status == 0){ // led off
		SCHEDULER_stopBlinking();
		LED_off();
		print("The LED turn off \n");
	}
	else if(led_status == 1){ // led on
		LED_on();
		print("The led turn on \n");
	}
	else if(led_status == 2){ // led blinking
		SCHEDULER_blink(); // blink in rate of 0.5 hz
		print("The led is blinking \n");
		led_status = -1; // for the next time he get to the function he will be 0
	}
}
