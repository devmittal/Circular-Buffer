/*****************************************************************************
​ ​* ​ ​ @file​ ​  ring.h
​ * ​ ​ @brief​ ​ Contains the functions prototypes, structure and global
 *           variable declaration essential for ring.c
 *   @Tools_Used GCC
​ * ​ ​ @author​  ​​Souvik De, Devansh Mittal
​ * ​ ​ @date​ ​ November 27th, 2018
​ * ​ ​ @version​ ​ 1.0
*****************************************************************************/

#ifndef RING_H
#define RING_H

#define COMMAND_COUNT (8)	//Length of the array holding the commands for commandline

/* Structure for CIrcular Buffer */
typedef struct
{
	char *Buffer;
	int Length;
	int Ini;	//Rear (Insertion Marker)
	int Outi;	//Front (Deletion Marker)
} ring_t;

/* Variable which holds the current selected ring */
ring_t *ring;
/* To store the ring collection */
ring_t **ring_collector;

/**
* @Brief  This function creates a collection of FIFO Cicular
*         buffers as per user input.
*
* @Param  Number of Circular Buffers to be created
*
* @Return Circular Buffer Collection
*
**/
ring_t** create_buffers(unsigned int ring_count);

/**
* @Brief  This function initializes a FIFO Cicular
*         buffers of a given length.
*
* @Param  Lenght of the buffer
*         Index of Ring Buffer being initialized from the collection
*	  Size of the ring collection
*
* @Return Error Code
*
**/
int init(int length, unsigned int ring_tracker, unsigned int ring_count);

/**
* @Brief  This function selects a FIFO Cicular Buffer from the
*         Collection of buffers to be operated upon.
*
* @Param  Index of the buffer to be selected.
*
* @Return void
*
**/
void select_buffer(unsigned int present_ring);

/**
* @Brief  This function inserts data into the selected FIFO Cicular
*         buffer.
*
* @Param  Refernce of the circular buffer and, data to be inserted.
*
* @Return Error Code
*
**/
int insert_data(ring_t *ring, char data);

/**
* @Brief  This function removes data from the selected FIFO Cicular
*         buffer.
*
* @Param  Refernce of the circular buffer and, resfernce of data to be removed.
*
* @Return Error Code
*
**/
int remove_data(ring_t *ring, char *data);

/**
* @Brief  This function display the count and data from the selected FIFO Cicular
*         buffer.
*
* @Param  Refernce of the circular buffer.
*
* @Return Error Code
*
**/
int entries(ring_t *ring);

/**
* @Brief  This function resizes a FIFO Cicular
*         buffers to a given length.
*
* @Param  New Lenght of the buffer
*         Index of Ring Buffer being resized from the collection
*	  Size of the ring collection
*
* @Return void
*
**/
void resize(int length, unsigned int ring_tracker, unsigned int ring_count);

#endif

