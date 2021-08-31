#include <string.h>
#include "terminal.h"
#include "led.h"
#include "scheduler.h"
#include "usart2.h"
#include "usart3.h"
#include "stm32f303xe.h"
#include "types.h"


static char A_Command_Buffer[TERMINAL_SIZE_OF_COMMAND_BUFFER];	// the input of the user

static char A_WIFI_Name[SIZE];	// symbol the WIFI name
static char A_WIFI_Pass[SIZE];	// symbol the WIFI password
static char A_WIFIDATA[WIFI_SIZE];		// The Command that pass to the modem
static char IP[SIZE];				// IP address of this side -> only for server
static int wifi_status = 0;
BOOL wifi_name_flag = FALSE;	// symbol if the user input the name of the network
BOOL wifi_pass_flag = FALSE;	// symbol if the user input the password of the network



void TERMINAL_handleCommand(void)
{
    // get the command from terminal and insert to A_Command_Buffer
	USART2_getCommand(A_Command_Buffer);

    if (strcmp(A_Command_Buffer, "0") == 0)
  	{
  		USART3_writeToModem("AT+RST\r\n",29);	// send command to the modem
  		while (USART3_commandReceived()==FALSE);	// wait until response
  	}
	// Type command "1" in the terminal to ask user to give WIFI details and connect to WIFI
    else if (strcmp(A_Command_Buffer, "1") == 0)
	{
		USART2_print("Closing previous WIFI connection (if there is)\n...\ncreating new connection\n");
		USART3_writeToModem("AT+CWQAP\r\n", 3);
		while(USART2_commandReceived() == FALSE);
		// get from the user the WIFI name
		USART2_print("Please enter WIFI host name\n");
		USART2_SetCommandReceivedFlag(FALSE);
		while(USART2_commandReceived() == FALSE);
		USART2_getCommand(A_Command_Buffer); // insert the input to the user
		strcpy(A_WIFIDATA,"AT+CWJAP=\""); // insert the AT+CWJAP to A_WIFIDATA
		strcpy(A_WIFI_Name,A_Command_Buffer);	// copy A_Command_Buffer to A_WIFI_Pass
		strcat(A_WIFIDATA,A_WIFI_Name); // concatenate the wifi name to the A_WIFIDATA
		strcat(A_WIFIDATA,"\","); // concatenate the ',' to the A_WIFIDATA

		// get from the user the WIFI password
		USART2_print("Please enter WIFI password\n");
		USART2_SetCommandReceivedFlag(FALSE);
		while(USART2_commandReceived() == FALSE);
		USART2_getCommand(A_Command_Buffer); // put the name the user enter into the buffer
		strcat(A_WIFIDATA,"\""); 				// add " to A_WIFIDATA
		strcpy(A_WIFI_Pass,A_Command_Buffer);	// copy A_Command_Buffer to A_WIFI_Pass
		strcat(A_WIFIDATA,A_WIFI_Pass); 		// concatenate A_WIFI_Pass to A_WIFIDATA
		strcat(A_WIFIDATA,"\"");				// add " to A_WIFIDATA
		strcat(A_WIFIDATA, "\r\n");				// add /r/n to the A_WIFIDATA
		USART3_writeToModem(A_WIFIDATA,5);

		while(USART3_commandReceived()==FALSE);

	}

	else if (strcmp(A_Command_Buffer, "2") == 0)
  	{
  		USART3_writeToModem("AT+CIFSR\r\n",5);	// send command to the modem
  		while (USART3_commandReceived()==FALSE);	// wait until response
  		TERMINAL_getIP();
  	}
    else if (strcmp(A_Command_Buffer, "3") == 0)
	{
		USART3_writeToModem("AT+CWMODE=1\r\n",3);
		while (USART3_commandReceived()==FALSE);	// wait until response
	}
    else if (strcmp(A_Command_Buffer, "4") == 0)
  	{
  		USART3_writeToModem("AT+CIPMUX=0\r\n",3);
  		while (USART3_commandReceived()==FALSE);	// wait until response
  	}

    else if (strcmp(A_Command_Buffer, "5") == 0)
	{
		USART2_print("Please enter Server IP\n");
		USART2_SetCommandReceivedFlag(FALSE);
		while(USART2_commandReceived() == FALSE);	// wait until the user fill WIFI name
		USART2_getCommand(A_Command_Buffer);		// get the WIFI name
		strcpy(A_WIFIDATA,"AT+CIPSTART=\"TCP\",\"");
		strcat(A_WIFIDATA,A_Command_Buffer);
		strcat(A_WIFIDATA,"\",80\r\n");
		USART3_writeToModem(A_WIFIDATA,3);		// write to the modem the full command
		while  (USART3_commandReceived()==FALSE);	// wait until response
	}

   	else if (strcmp(A_Command_Buffer, "6") == 0)
	{
		USART3_writeToModem("AT+CIPMODE=0\r\n",3);
		while (USART3_commandReceived()==FALSE);	// wait until response
	}
   	else if (strcmp(A_Command_Buffer, "L") == 0)
	{
		USART2_print("infinite loop activated\n");
		while(1);
	}
   	else
   	{
   		USART2_print("Command not supported, read the user manual for command list\n");
   	}

}


int TERMINAL_getStatus(void)
{
	return wifi_status;
}

void TERMINAL_getIP(void)
{
	char* tmp = USART3_getBuffer(); // get the response from the modem for AT+CIFSR command
	USART2_noprint(tmp); // instead of delay, represent the buffer so it prints normally.
	int i=0;
	int j=0;
	while (tmp[i++] != '"');
	while (tmp[i] != '"') // get the IP from the response and save it in the IP array
	{
		IP[j++] = tmp[i++]; // Increment the i and j by 1 after the insert
	}
	if (IP[0] == '0')
	{
		USART2_print("NOT CONNECTED\n");
		wifi_status = 2;
	}
	else
	{
		USART2_print("WIFI CONNECTED\n");
		wifi_status = 1;
	}
}
