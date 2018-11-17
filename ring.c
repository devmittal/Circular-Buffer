#include<stdio.h>
#include<stdlib.h>
#include"ring.h"

int flag = 0;

ring_t** create_buffers(unsigned int ring_count)
{
	ring_collector = malloc(ring_count * sizeof(*ring));
	return ring_collector;
}

int init(int length, unsigned int ring_tracker)
{
	if((ring = malloc(length + sizeof(*ring))) != NULL)
	{
		free(ring_collector[ring_tracker]);
		ring_collector[ring_tracker] = ring;
		ring->Length = length;
		ring->Ini = 0;
		ring->Outi = 0;
		ring->Buffer = (char *)(ring + 1);
		return 1;
	}
	else
		return 0;
}

void select_buffer(unsigned int present_ring)
{
	ring = ring_collector[present_ring];
	printf("\nBuffer %u selected",present_ring);
}

int insert_data(ring_t *ring, char data)
{
	
	if((ring->Ini-ring->Outi) == ring->Length)
	{
		return 0;
	}

	else
	{
		ring->Buffer[ring->Ini++ % ring->Length] = data;	//First Data
		return 1;
	}		
}

int remove_data(ring_t *ring, char *data)
{
	if(ring->Outi == ring->Ini)
	{
		*data = 255;
		return 0;			
	}
	
	else
	{
		*data = ring->Buffer[ring->Outi++ % ring->Length];	
		return 1;
	}	
}

int entries(ring_t *ring)
{
	int i = 0;

	printf("\nNumber of elements in the buffer: %d", (ring->Ini - ring->Outi));

	if(ring->Ini == ring->Outi)
	{
		return 0;
	}

	else if((ring->Ini % ring->Length) > (ring->Outi % ring->Length))
	{
		printf("\n\n-");
		for(i = ring->Outi; i < ring->Ini; i++)			
				printf("----");
		printf("\n|");
		for(i = ring->Outi; i < ring->Ini; i++)
		{			
			printf(" %c |",ring->Buffer[i%ring->Length]);
		}
		printf("\n-");
		for(i = ring->Outi; i < ring->Ini; i++)			
				printf("----");
		return 1;	
	}

	else
	{
		printf("\n\n-");
		for(i = 0; i < (ring->Ini % ring->Length); i++)			
				printf("----");
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)			
				printf("----");
		printf("\n|");
		for(i = 0; i < (ring->Ini % ring->Length); i++)
		{			
			printf(" %c |",ring->Buffer[i%ring->Length]);	
		}
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)
		{			
			printf(" %c |",ring->Buffer[i%ring->Length]);	
		}
		printf("\n-");
		for(i = 0; i < (ring->Ini % ring->Length); i++)			
				printf("----");
		for(i = (ring->Outi % ring->Length); i < ring->Length; i++)			
				printf("----");
		return 1;
	}
}
