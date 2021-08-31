#ifndef TIMER2_H_
#define TIMER2_H_




/******************************************************************************
Includes
******************************************************************************/
#include "types.h"




/******************************************************************************
TIMER2_expired
Description:
  Returns TRUE if Timer 2 was updated since last call.
Return value: TRUE if the timer was updated, FALSE if not.
******************************************************************************/
BOOL TIMER2_expired(void);

/******************************************************************************
TIMER2_init
Description: Initializes Timer 2 to expire once every second.
******************************************************************************/
void TIMER2_init(void);




#endif /* TIMER2_H_ */
