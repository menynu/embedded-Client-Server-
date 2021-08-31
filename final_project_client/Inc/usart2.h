#ifndef USART2_H_
#define USART2_H_




/******************************************************************************
Includes
******************************************************************************/
#include "types.h"




/******************************************************************************
Definitions
******************************************************************************/
#define USART2_SIZE_OF_PRINT_BUFFER 127
#define USART2_SIZE_OF_RX_BUFFER 127



/******************************************************************************
USART2_getBuffer
Description: Present usart 2 RX buffer
Return value: USART2 RX buffer to other classes.
******************************************************************************/
char* USART2_getBuffer(void);


/******************************************************************************
USART2_SetCommandReceivedFlag
Description: Present usart 2 RX buffer
note: this function made to sample if command received from usart2
Input: TRUE - command received, FALSE - command didn't received yet.
******************************************************************************/
void USART2_SetCommandReceivedFlag(BOOL cr);


/******************************************************************************
print
Description: Functions as the stdio printf function.
Note:
  This function uses a buffer, whose size is determined by USART2_SIZE_OF_
  PRINT_BUFFER. Therefore, it is not reentrant.
******************************************************************************/
void print(char *p_format, ...);

/******************************************************************************
USART2_commandReceived
Description:
  Returns TRUE if a '\n'-terminated command was received since the previous
  call.
Return value: TRUE if a command was received, FALSE if not.
******************************************************************************/
BOOL USART2_commandReceived(void);

/******************************************************************************
USART2_getCommand
Description:
  Copies the current command in the USART2 RX buffer.
  The '\n' at the end of the recieved command is replaced with a '\0'.
Input:
  p_command: Address to which to the command should be copied.
******************************************************************************/
void USART2_getCommand(char *p_command);

/******************************************************************************
USART2_init
Description: Initializes USART2 on GPIOs PA2 and PA3,
  with a baud rate of 9600.
******************************************************************************/
void USART2_init(void);

/******************************************************************************
USART2_print
Description: Prints a '\0'-terminated sequence of characters.
Input:
  p_data: The sequence to print.
******************************************************************************/
void USART2_print(const char *p_data);

/******************************************************************************
USART2_printCharacter
Description: Prints one character.
Input:
  c: The character to print.
******************************************************************************/
void USART2_printCharacter(char c);


/******************************************************************************
USART2_noprint
Description: create a delay without present to user.
Input:
  the data we want to print without show it.
******************************************************************************/
void USART2_noprint(const char *p_data);


#endif /* USART2_H_ */
