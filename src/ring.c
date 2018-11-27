/*****************************************************************************
​ ​* ​ ​ @file​ ​  ring.c
​ * ​ ​ @brief​ ​ Contains the functions essential for operating the
 *           circular buffer 
 *   @Tools_Used GCC
​ * ​ ​ @author​  ​​Souvik De, Devansh Mittal
​ * ​ ​ @date​ ​ November 27th, 2018
​ * ​ ​ @version​ ​ 1.0
*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"../inc/ring.h"

int flag = 0;

/* Create a collection of circular buffers as defined by user */
ring_t** create_buffers(unsigned int ring_count)
{
	/* Allocated ring buffers */
	ring_collector = malloc(ring_count * sizeof(*ring));
	return ring_collector;
}

/* Innitializes ring buffers one by one serially */
int init(int length, unsigned int ring_tracker, unsigned int ring_count)
{
	/* Proceed If ring index to be innitialize is less than the maximum number of cicular buffers in the ring collector */
	if(ring_count > ring_tracker)
	{
		/* Allocate memory for the structure and character array (buffer) dynamically and process if successfull */
		if((ring = malloc(length + sizeof(*ring))) != NULL)
		{
			/* Display initalized ring index and starting address */
			printf("\nCircular Buffer %u Allocate %p",ring_tracker,ring);
			/* Free ring collector redundant memory */
			free(ring_collector[ring_tracker]);
			/* Assign initialized ring to ring collector */
			ring_collector[ring_tracker] = ring;
			/* Inntialize all structure parameters */
			ring->Length = length;
			/* Set Rear (insertion - Ini) and Front (Deletion - Outi) Markers  to default */
			ring->Ini = 0;
			ring->Outi = 0;
			/* Point to sace reserved for buffer */
			ring->Buffer = (char *)(ring + 1);
			/* Reset ring to null for subsequent initializations */
			ring = NULL;
			return 1;	//Return Success
		}
		else
			return 0;	//Return DMA failure
	}
	else
		return -1;	//Return Out of bound ring index error code
}

/* To select a buffer from the ring collection */
void select_buffer(unsigned int present_ring)
{
	ring = ring_collector[present_ring];
	printf("\nBuffer %u selected",present_ring);
}

/* To insert data in the circular buffer */
int insert_data(ring_t *ring, char data)
{
	/* Check if buffer is full */
	if((ring->Ini-ring->Outi) == ring->Length)
	{
		/* Return Failure to insert */
		return 0;
	}
	else
	{
		/* Keep inserting until full and conform index within buffer length */
		ring->Buffer[ring->Ini++ % ring->Length] = data;	
		return 1;
	}		
}

/* To remove data from the FIFO Circular buffer */
int remove_data(ring_t *ring, char *data)
{
	/* Return failure to remove if buffer is empty */
	if(ring->Outi == ring->Ini)
	{
		*data = 255;
		return 0;			
	}
	else
	{
		/* Remove data until empty and conform the out marker within buffer length */
		*data = ring->Buffer[ring->Outi++ % ring->Length];	
		return 1;	//Return successS
	}	
}

/* Display Number of entries and contents of the buffer */
int entries(ring_t *ring)
{
	int i = 0;

	/* Display count of intems in the selected buffer */
	printf("\nNumber of elements in the buffer: %d", (ring->Ini - ring->Outi));

	/* Return Failure to read if buffer is empty */
	if(ring->Ini == ring->Outi)
	{
		return 0;
	}
	/* If the In marker exceeds the out marker */
	else if((ring->Ini % ring->Length) > (ring->Outi % ring->Length))
	{
		/* Display Table */		
		printf("\n\n-");
		for(i = ring->Outi; i < ring->Ini; i++)			
				printf("----");
		printf("\n|");
		/* Print entries from Out Marker to In Marker */
		for(i = ring->Outi; i < ring->Ini; i++)
		{			
			printf(" %c |",ring->Buffer[i%ring->Length]);
		}
		/* Display Table */
		printf("\n-");
		for(i = ring->Outi; i < ring->Ini; i++)			
				printf("----");
		return 1;	
	}
	/* if the Out marker exceeds the In marker */
	else
	{
		/* Display Table */
		printf("\n\n-");
		for(i = 0; i < (ring->Ini % ring->Length); i++)			
				printf("----");
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)			
				printf("----");
		printf("\n|");
		/* Print Entries from Inial Position (Zero index) to In Marker */
		for(i = 0; i < (ring->Ini % ring->Length); i++)
		{			
			printf(" %c |",ring->Buffer[i]);	
		}
		/* Print remaining entries from Out Marker until the penultimate index of selected buffer (Index of Length - 1) */
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)
		{			
			printf(" %c |",ring->Buffer[i]);	
		}
		/* Display Table */
		printf("\n-");
		for(i = 0; i < (ring->Ini % ring->Length); i++)			
				printf("----");
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)			
				printf("----");
		return 1;	//Return Success
	}
}

/* To resize a selected Circular Buffer */
void resize(int length, unsigned int ring_tracker, unsigned int ring_count)
{
	/* Fetch the ring to be resized from the collection */
	ring_t *temp_ring = ring_collector[ring_tracker];
	int i = 0, count = 0;
	/* Allocate an array of size equivaluent to the new length */
	int *data = (int*)malloc(length * sizeof(int));
	char c = 0;
	/* Extract data from the selected ring until it fills up the array */
	for(i = 0 ; i < length ; i++)
	{
		/* Extract data by removing it from the buffer and copying it to the array */
		if(remove_data(temp_ring,&c))
		{
			data[i] = c;
			count++;
		}
		else
			break;
	}
	/* Initialize the same buffer with the new size */
	init(length,ring_tracker,ring_count);
	/* Fetch the newly innitalized buffer */
	ring = ring_collector[ring_tracker];
	/* Insert old data into the resized buffer */ 
	for(i = 0 ; i < count; i++)
	{
		insert_data(ring,data[i]);
	}
	/* Free space allocated for temporary storage array */
	free(data);		
}
