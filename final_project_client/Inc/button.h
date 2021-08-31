#ifndef BUTTON_H_
#define BUTTON_H_




/******************************************************************************
Includes
******************************************************************************/
#include "types.h"




/******************************************************************************
BUTTON_init
Description: Initializes the button GPIO (PC13) and its interrupt.
******************************************************************************/
void BUTTON_init(void);

/******************************************************************************
BUTTON_pressed
Description:
  Returns TRUE if the button was pressed (i.e., PC13 went from 1 to 0) since
  the last call.
Return value: TRUE if the button was pressed, FALSE if not.
******************************************************************************/
BOOL BUTTON_pressed(void);




#endif /* BUTTON_H_ */
