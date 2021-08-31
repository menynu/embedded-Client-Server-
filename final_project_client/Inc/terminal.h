#ifndef TERMINAL_H_
#define TERMINAL_H_


/******************************************************************************
Definitions
******************************************************************************/
//  Maximum allowed size of a command (including the terminating '\n').
#define TERMINAL_SIZE_OF_COMMAND_BUFFER 128
#define SIZE 30  //size for buffers
#define WIFI_SIZE 50  //size for wifi buffer


/******************************************************************************
TERMINAL_handleCommand
Description: Fetches a command from the USART2 RX buffer and executes it.
Accepted input:
	0: Reset the modem info without harming the WIFI status. (reconnect if connected)
		Command executed: AT+RST
	1: Disconnect from previous WIFI and connects to new wifi.
		input: WIFI name & WIFI password.
		Command executed: AT+CWQAP
		Command executed: AT+CWJAP="wifi name","wifi pass"
	2: Present the current IP and determine if connected to wifi.
		Command executed: AT+CIFSR
	3: Set WIFI mode to Station mode/
		Command executed: AT+CWMODE=1
	4: As client, CIPMUX must be 0, so it disables multiple connections.
		Command executed: AT+CIPMUX=0
	5: Connect to server.
		input: Server's IP.
		Command executed: AT+CIPSTART="TCP","server IP"
	6: Set to single connection
		Command executed: AT+CIPMODE=0
	L: Enters infinite loop
******************************************************************************/
void TERMINAL_handleCommand(void);


/******************************************************************************
TERMINAL_getIP
Description: Get the current IP from modem and save it on IP buffer.
Note:
  This function uses a buffer, whose size is determined by SIZE. Therefore, it is not reentrant.
******************************************************************************/
void TERMINAL_getIP(void);


/******************************************************************************
TERMINAL_getStatus
Description: Present the status of button.
Return:
	0: User hasn't configure the IP yet, need to press '2' to check IP (determine if connected)
	1: Button was pressed and connected to WIFI.
	2: Button was pressed and not connected to WIFI
Note:
  This function is used in Eventqueue button interrupt.
******************************************************************************/
int TERMINAL_getStatus(void);


#endif /* TERMINAL_H_ */
