#ifndef TYPES_H_
#define TYPES_H_




/******************************************************************************
Definitions
******************************************************************************/
typedef enum
{
	FALSE,
	TRUE
} BOOL;

typedef struct CyclicBuffer{
	int cyclicBuffer[10];	/* Event Queue with the events	*/
	int* p_write;	/* Pointer to write	*/
	int* p_read;	/* Pointer to read 	*/
}CyclicBuffer;




#endif /* TYPES_H_ */
