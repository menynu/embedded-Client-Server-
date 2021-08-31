#include "usart3.h"
#include "usart2.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "stm32f303xe.h"
#include "types.h"
#include "eventqueue.h"
#include "led.h"

int rowsNum; // the rows of the answer - const by function
int rows; 	// the rows of the answer - counter
static char A_Rx_Buffer3[USART3_SIZE_OF_RX_BUFFER];
static char A_Tx_Buffer3[USART3_SIZE_OF_PRINT_BUFFER];
static BOOL Command_Received;
static char *P_Loc_In_Rx_Buffer3 = A_Rx_Buffer3;
static char * const P_End_Of_Rx_Buffer3 = A_Tx_Buffer3 + USART3_SIZE_OF_RX_BUFFER - 1;
BOOL flag = FALSE;

BOOL USART3_commandReceived(void)
{

    if(Command_Received)
    {
    	Command_Received = FALSE;
        while (USART3->ISR & 0x00000020);
    	return TRUE;
    }
    else
    {
    	return FALSE;
    }
}

char* USART3_getBuffer(void)
{
	return A_Rx_Buffer3;
}

void USART3_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable port b clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // enable usart3 clock


    //enable bits 17 & 19 so PB8 & PB9 enabled as AF (required for usart3 RX & TX) p.237
    GPIOB->MODER |= (1<<19 | 1<<17); //PB8 = RX, PB9 = TX
    GPIOB->AFR[1] |= 0x00000077; //enable AF for PB8, PB9

    USART3->BRR = 8000000/115200;
    USART3->CR1 = USART_CR1_TXEIE; // maybe need also TX interrupt
    //Enable USART, RX and TX bits, also enable RX and TX interrupt
    USART3->CR1 = (USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE  );
    //enable interrupt for USART3
    NVIC_EnableIRQ(USART3_IRQn);
}



//will get the actual word from modem response
void USART3_getCMD()
{

	char* tmp = A_Rx_Buffer3; // point to the start of the RX buffer
	if (tmp[0] == '+')
	{
		LED_action();
	}

}

//interrupt to receive from modem to USART3 on 115200 Baud Rate
void USART3_EXTI28_IRQHandler(void)
{

	char rx_byte;
	// if RX bit flag is on status register, the interrupt for receive is flagged. // Read Data Register Not Empty
	 if( (USART3->CR1 & USART_CR1_RXNEIE) && (USART3->ISR & USART_ISR_RXNE))
	 {
		// Read the received byte into the buffer.
		// This also clears the interrupt request flag.
		rx_byte = USART3->RDR;
		if (rx_byte == '\n'  )  // stop to insert if you see \n because the response end
		{
			rows++;
			if (rowsNum == rows)
			{
				*P_Loc_In_Rx_Buffer3 = '\0';
				P_Loc_In_Rx_Buffer3 = A_Rx_Buffer3;
				rows=0;

				if (rowsNum == 1) //if there's a command line received from client
				{
					USART2_printCharacter('\n');
					USART3_getCMD();

				}
				rowsNum=1;
				Command_Received = TRUE;
				EVENTQUEUE_add_event(3);
				return;
			}
			Command_Received = TRUE;
		}

		*P_Loc_In_Rx_Buffer3 = rx_byte;
		// If the buffer is full, we don't advance the pointer.
		if(P_Loc_In_Rx_Buffer3 >= P_End_Of_Rx_Buffer3)
		{

			return;
		}
		P_Loc_In_Rx_Buffer3++;
	 }

}


//sends the data from USART2 terminal RX buffer to modem on 115200 BR
void USART3_writeToModem(const char *p_data,int answerRowNum)
{
	rowsNum = answerRowNum;
	while(*p_data != '\0')
	{
		USART3->TDR = *p_data;
        p_data++;
        while(!(USART3->ISR & 0x00000080));
	}
	while(USART3_commandReceived());
}


