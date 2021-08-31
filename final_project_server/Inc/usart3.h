#ifndef USART3_H_
#define USART3_H_

/******************************************************************************
Includes
******************************************************************************/
#include "types.h"



/******************************************************************************
Definitions
******************************************************************************/
#define USART3_SIZE_OF_PRINT_BUFFER 136
#define USART3_SIZE_OF_RX_BUFFER 136


/******************************************************************************
USART3_init
Description: Initializes USART3 on GPIOs PB8 and PB9,
  with a baud rate of 115200.
  enables USART3 to accept transmit and receive with its interrupts.
******************************************************************************/
void USART3_init(void);


/******************************************************************************
USART3_writeToModem
Description: Send the data from terminal to modem through Transfer Data Register
Input: The data we want to transfer, The accepted number of rows the modem should return.
******************************************************************************/
void USART3_writeToModem(const char *p_data,int answerRowNum);

/******************************************************************************
USART3_commandReceived
Description: Determine when command received from modem
Output:
	TRUE: Command finished to received
	FALSE: There is not command from modem
******************************************************************************/
BOOL USART3_commandReceived(void);


/******************************************************************************
USART3_getBuffer
Description: Get function of usart3 RX buffer
Output: Returns the buffer with the response data from modem.
******************************************************************************/
char * USART3_getBuffer(void);


/******************************************************************************
USART3_getCMD
Description: Determine if there is button pressed from server,
if RX buffer has 1 line this function is executed and check for '+' as start of button click word.
******************************************************************************/
void USART3_getCMD(void);

#endif /* USART3_H_ */
