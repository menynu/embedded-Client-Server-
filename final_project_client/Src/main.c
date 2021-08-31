#include "stm32f303xe.h"
#include "types.h"
#include "button.h"
#include "led.h"
#include "scheduler.h"
#include "watchdog.h"
#include "eventqueue.h"
#include "terminal.h"
#include "timer2.h"
#include "usart2.h"
#include "usart3.h"


int main(void)
{
	WATCHDOG_init(); // configure the IWDG - WATCHDOG
    BUTTON_init(); // configure the blue button
    LED_init(); // configure the led
    TIMER2_init(); // configure the timer2
    USART3_init(); // configure USART3
    USART2_init(); // configure USART2
    EVENTQUEUE_init();

    for(int i=0;i<200000;i++); // delay for show on the screen the print
    print("The STM connect to source power\n");
	print("This is the client side\n");

    LED_off(); // by requirement when we start the program the led will be off

    while(1)
    {
    	EVENTQUEUE_handler(); // cyclic buffer to handle events
    	WATCHDOG_pet(); // pet the WatchDog to prevent infinite loop
    }
}
