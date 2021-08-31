#include "eventqueue.h"
#include "types.h"
#include "usart3.h"
#include "usart2.h"
#include <string.h>
#include "terminal.h"
#include "scheduler.h"

char* tmp ;
CyclicBuffer EQ;	// Event Queue

void EVENTQUEUE_init(void){
	for(int i=0;i<10;i++)
		EQ.cyclicBuffer[i] = 0;
	EQ.p_write = &EQ.cyclicBuffer[0]; // p_write pointer on the first cell in the event queue
	EQ.p_read = &EQ.cyclicBuffer[0];	// p_read pointer on the first cell in the event queue
}

void EVENTQUEUE_handler(void){
	char* tmp ;
	int status;
	switch (*EQ.p_read) { // switch case by interrupt_code
		case 1: // Button Press interrupt
			status = TERMINAL_getStatus();
			if (status == 1)
			{
				USART3_writeToModem("AT+CIPSEND=0,4\r\n",5);
				while (USART3_commandReceived()==FALSE);	// wait until response
				USART3_writeToModem("OK\r\n",7);
			}
			else if (status == 2)
			{
				USART2_print("Button is pressed but there's no connection\n");
			}
			else{
				USART2_print("Please finish to configure the project by enter '2'\n");
			}
			EVENTQUEUE_remove_event();
			break;
		case 2: // Get command interrupt from terminal
			TERMINAL_handleCommand();
			USART2_commandReceived();
			tmp = USART2_getBuffer();
			strcpy(tmp,"\0");
			EVENTQUEUE_remove_event();
			break;
		case 3: // received from modem usart RX BUFFER 3
			tmp =  USART3_getBuffer(); //will represent the usart3 rx buffer
			USART2_print(tmp);
			EVENTQUEUE_remove_event();
			USART2_printCharacter('\n');
			break;
		case 4:
			SCHEDULER_handle();
			EVENTQUEUE_remove_event();
		case 5:
			USART2_commandReceived();
			EVENTQUEUE_remove_event();
		default:
			break;
	}

}

void EVENTQUEUE_add_event(int interrupt_code){
	if(*EQ.p_write == 0) // the cell is empty
		*EQ.p_write = interrupt_code; // enter the interrupt code into the event queue
	else	//we can't to enter the interrupt code to the event queue -> error
		return; // TODO: need to add the error massage

	// promote the p_write to the next index
	if(*EQ.p_write != 0 && EQ.p_write == &EQ.cyclicBuffer[9]) // if the p_write in the cyclic buffer is in the last cell
		EQ.p_write = &EQ.cyclicBuffer[0]; // p_write pointer to the first cell of the event queue
	else
		EQ.p_write++;	//increment the pointer by 1
}

void EVENTQUEUE_remove_event(void){
	*EQ.p_read = 0; // reset the cell that taking care

	// promote the p_write to the next index
	if(EQ.p_read == EQ.p_write)
		return; // We Don't want to increment p_read if the p_read and p_write in the same place
	if(EQ.p_read == &EQ.cyclicBuffer[9]) // if the p_read in the cyclic buffer is in the last cell
		EQ.p_read = &EQ.cyclicBuffer[0]; // p_read pointer to the first cell of the event queue
	else
		EQ.p_read++; // increment the pointer by 1
}
