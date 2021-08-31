#include "led.h"
#include "scheduler.h"
#include "types.h"
#include "usart2.h"




static BOOL Blink = FALSE;
static unsigned char Blink_Counter = 0;




void SCHEDULER_blink(void)
{
    Blink = TRUE;
}




void SCHEDULER_handle(void)
{
	if(Blink)
	{
        Blink_Counter++;
        if(Blink_Counter == SCHEDULER_BLINK_HALF_PERIOD_IN_SEC)
        {
        	Blink_Counter = 0;
        	LED_toggle();
        }
	}
}




void SCHEDULER_stopBlinking(void)
{
    Blink = FALSE;
}
