#include "stm32f303xe.h"
#include "watchdog.h"

// work by the instruction in p.759 at the reference manual
void WATCHDOG_init(void){
	IWDG->KR = 0xCCCC;	// Enable the WatchDog -> start the WD by p.761 at the reference manual
	// Enable register access -> enable access to the IWDG_PR, IWDG_RLR and IWDG_WINR registers
	IWDG->KR = 0x5555;
	IWDG->PR = 0x7;	// Configure the prescaler divider to divider/4
	IWDG->SR = 000; // Initialize the status register of the WatchDog
	IWDG->RLR = 0xAAA;	// Write the reload register
}


void WATCHDOG_pet(void){
	IWDG->KR = 0xAAAA;	//Refresh the counter value with IWDG_RLR
}

void WATCHDOG_infinite_loop(void){
	while(1); // Infinite loop
}
