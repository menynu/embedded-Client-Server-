#ifndef WATCHDOG_H_
#define WATCHDOG_H_

/******************************************************************************
WATCHDOG_init
Description: Initializes the WatchDog, enable access to the IWDG_PR, IWDG_RLR
 and IWDG_WINR registers, configure the IWDG_PR, IWDG_RLR registers
******************************************************************************/
void WATCHDOG_init(void);

/******************************************************************************
WATCHDOG_pet
Description: kick the WATCHDOG function ,Refresh the counter value with IWDG_RLR
******************************************************************************/
void WATCHDOG_pet(void);

/******************************************************************************
WATCHDOG_infinite_loop
Description: Stack the program in infinite loop
******************************************************************************/
void WATCHDOG_infinite_loop(void);

#endif /* WATCHDOG_H_ */
