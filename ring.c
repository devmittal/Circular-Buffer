#include<stdio.h>
#include<stdlib.h>
#include"ring.h"

ring_t* init(int length)
{
	ring_t *ring = malloc(length + sizeof(*ring));
	ring->Length = length;
	ring->Ini = -1;
	ring->Outi = -1;
	ring->Buffer = (char *)(ring + 1);
	return ring;
}

int insert_data(ring_t *ring, char data)
{
	if(((ring->Outi == 0) && (ring->Ini == ring->Length-1)) || (ring->Ini == (ring->Outi - 1)))	//Limit Reached - Wrap Arround
	{
		ring->Outi = 0;
		ring->Ini = 0;
		ring->Buffer[ring->Ini] = data;
	}
	else if(ring->Outi == -1)
	{
		ring->Outi = 0;
		ring->Ini = 0;
		ring->Buffer[ring->Ini] = data;	//First Data
	}
	else if((ring->Ini == (ring->Length - 1)) && (ring->Outi != 0))
	{
		ring->Ini = 0;
		ring->Buffer[ring->Ini] = data;
	}
	else
	{
		ring->Ini++;
		ring->Buffer[ring->Ini] = data;
	}
	return 1;
}

int remove_data(ring_t *ring, char *data)
{
	if(ring->Outi == -1)
	{
		return -1;
	}
	
	*data = ring->Buffer[ring->Outi];
	ring->Buffer[ring->Outi] = 0;

	if(ring->Outi == ring->Ini)
	{
		ring->Outi = -1;
		ring->Ini = -1;
	}
	else if(ring->Outi == (ring->Length - 1))
		ring->Outi = 0;
	else
		ring->Outi++;
	return 1;
}

int entries(ring_t *ring)
{
	int i = 0, j = 0;
	
	if(ring->Outi == -1)
		return -1;

	if(ring->Ini >= ring->Outi)
	{
		printf("\n-");
		for(j = ring->Outi ; j < ring->Length ; j++)			
				printf("----");
		printf("\n|");
		for(i = ring->Outi ; i < ring->Length ; i++)
		{			
			printf(" %c |",ring->Buffer[i]);	
		}
		printf("\n-");
		for(j = ring->Outi ; j < ring->Length ; j++)			
				printf("----");
	}
	else
	{
		for(i = ring->Outi ; i < ring->Length ; i++)
			printf("%c ",ring->Buffer[i]);

		for(i = 0 ; i <= ring->Ini ; i++)
			printf("%c ",ring->Buffer[i]);
	}
}
