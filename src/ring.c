#include<stdio.h>
#include<stdlib.h>
#include"../inc/ring.h"

int flag = 0;

ring_t** create_buffers(unsigned int ring_count)
{
	ring_collector = malloc(ring_count * sizeof(*ring));
	return ring_collector;
}

int init(int length, unsigned int ring_tracker, unsigned int ring_count)
{
	if(ring_count > ring_tracker)
	{
		if((ring = malloc(length + sizeof(*ring))) != NULL)
		{
			printf("\nCircular Buffer %u Allocate %p",ring_tracker,ring);
			free(ring_collector[ring_tracker]);
			ring_collector[ring_tracker] = ring;
			ring->Length = length;
			ring->Ini = 0;
			ring->Outi = 0;
			ring->Buffer = (char *)(ring + 1);
			ring = NULL;
			return 1;
		}
		else
			return 0;
	}
	else
		return -1;
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
		ring->Buffer[ring->Ini++ % ring->Length] = data;	
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

void resize(int length, unsigned int ring_tracker, unsigned int ring_count)
{
	ring_t *temp_ring = ring_collector[ring_tracker];
	int i = 0, count = 0;
	int *data = (int*)malloc(length * sizeof(int));
	char c = 0;

	for(i = 0 ; i < length ; i++)
	{
		if(remove_data(temp_ring,&c))
		{
			data[i] = c;
			count++;
		}
		else
			break;
	}
	init(length,ring_tracker,ring_count);
	ring = ring_collector[ring_tracker];
	for(i = 0 ; i < count; i++)
	{
		insert_data(ring,data[i]);
	}
	free(data);		
}

void report(unsigned int ring_count)
{
	unsigned int ring_parser = 0, character_parser = 0, buffer_parser = 0, occurance_counter = 0;
	ring_t *temp_ring = 0;	
	
	for(character_parser = 0 ; character_parser < 256 ; character_parser++)
	{
		for(ring_parser = 0 ; ring_parser < ring_count ; ring_parser++)
		{
			temp_ring = ring_collector[ring_parser];
		
			if((temp_ring->Ini % temp_ring->Length) > (temp_ring->Outi % temp_ring->Length))
			{
				for(buffer_parser = temp_ring->Outi; buffer_parser < temp_ring->Ini; buffer_parser++)
				{			
					if((unsigned int)temp_ring->Buffer[buffer_parser % temp_ring->Length] == character_parser)
					{
						occurance_counter++;
					}
				}
			}
			else
			{
				for(buffer_parser = 0; buffer_parser < (temp_ring->Ini % temp_ring->Length); buffer_parser++)
				{			
					if((unsigned int)temp_ring->Buffer[buffer_parser % temp_ring->Length] == character_parser)
					{
						occurance_counter++;
					}
				}
				for(buffer_parser = (temp_ring->Outi % temp_ring->Length); buffer_parser < temp_ring->Length; buffer_parser++)
				{			
					if((unsigned int)temp_ring->Buffer[buffer_parser % temp_ring->Length] == character_parser)
					{
						occurance_counter++;
					}
				}
			}
			buffer_parser = 0;		
		}
		
		if(occurance_counter != 0)
		{
			printf("\n%c - %u",(char)character_parser , occurance_counter);
			occurance_counter = 0;
		}
	}
}
