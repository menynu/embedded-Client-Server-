#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

/******************************************************************************
EVENTQUEUE_init
Description: Initializes an Cyclic buffer to present each "cell" as interrupt handler such as event.
note: Buffer size 10.
******************************************************************************/
void EVENTQUEUE_init(void);


/******************************************************************************
EVENTQUEUE_handler
Description: Fetches the command of each interrupt occurrence to the Event Queue buffer
Accepted input (Cases) :
	1: Button interrupt:
		Description:
			(*)If pressed and there's connection to modem (formal IP): send message to server
			(*)If pressed and No IP (0.0.0.0) give message and don't pass to server.
			(*)If user didn't press (2) - configure with AT+CIFSR -> Give the proper error message.
	2: USART2 interrupt:
		Description: whenever there's a command received call (message we want to show on terminal)
		then present it on terminal.
	3: USART3 interrupt:
		Description: whenever there's full command\message received from modem then we want to send it to terminal
		on usart2.
	4: TIM2 interrupt:
		Description: configure the scheduler for the blink timing of the LED.

******************************************************************************/
void EVENTQUEUE_handler(void);


/******************************************************************************
EVENTQUEUE_add_event
Description: Fetches each event interrupt to the next cell on the even queue
note: when the cell reach to max size it return to start cell (cyclic) if possible (already executed).
******************************************************************************/
void EVENTQUEUE_add_event(int interrupt_code);


/******************************************************************************
EVENTQUEUE_remove_event
Description: Remove the event\interrupt from the even queue so new event can come in its cell.
******************************************************************************/
void EVENTQUEUE_remove_event(void);


#endif /* EVENTQUEUE_H_ */
