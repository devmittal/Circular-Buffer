#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<stdlib.h>
#include"../inc/ring.h"

#define COMMAND_COUNT (7)

typedef struct
{
	char command[20];
	unsigned char arg_extraction_count;
} command_t;

void quit(void)
{
	exit(0);
}

int main()
{
	char response[50] = {};
	command_t commands[COMMAND_COUNT] = {{"create",1}, {"init",1}, {"select",1}, {"insert",1}, {"remove",0}, {"entries",0}, {"exit",0}}; 
	char* arguments[10] = {};
	char* arg = NULL;
	unsigned char arg_counter = 0, arg_parser = 0, command_parser = 0;
	char pop_data;

	unsigned int buffer_length = 0, ring_tracker = 0, selected_ring = 0, ring_count = 0, present_ring = 0;
	char deleted_data = 0;

	printf("\nCircular Buffer");
	printf("\n***************");

	while(1)
	{
		arg_counter = 0;

		printf("\n\nCreate N buffers - create <No. of Buffers>");
		printf("\nInnitialize buffer - init <Buffer Size>");
		printf("\nSelect a buffer - select <#Buffer>");
		printf("\nInsert data in buffer - insert <Character Data>");
		printf("\nRemove first data from buffer - remove");
		printf("\nDisplay data in buffer - entries");
		printf("\nExit program - exit");

		printf("\n\n>>");
		fgets(response, sizeof response, stdin);
		arg = strtok(response," \n");
				
		while(arg != NULL)
		{
			arguments[arg_counter++] = arg;
			arg = strtok(NULL," ");
		} 


		for(command_parser = 0 ;  command_parser < COMMAND_COUNT ; command_parser++)
		{
			if(strcmp(arguments[0],commands[command_parser].command) == 0)
			{
				if((arg_counter - 1) == commands[command_parser].arg_extraction_count)
				{
					switch(command_parser)
					{
						case 0:	if(ring_collector == NULL)
							{
								ring_count = (unsigned int)atoi(arguments[arg_counter-1]);
								ring_collector = create_buffers(ring_count);
								if(ring_collector != 0)
								{
									printf("\n%u Buffers successfully created !",ring_count);
								}
								else
									printf("\nFailed to create %u buffers !",ring_count);
							}
							else
								printf("\n%u Buffers have already been created !",ring_count);
							break;

						case 1:	if(ring_collector != NULL)
							{
								if(ring_count > ring_tracker)
								{
									buffer_length = atoi(arguments[arg_counter-1]);
									if(init(buffer_length, ring_tracker) == 1)
									{
										printf("\nCircular Buffer %u Allocate %p",ring_tracker,ring);
										ring_tracker += 1;
										ring = NULL;
									}
									else
										printf("\nAllocation of buffer failed !");
								}
								else
									printf("\nAll the circular buffers have been allocated!");
							}
							else
								printf("\nNo circular buffers created!"); 
							break;

						case 2:	if(ring_tracker == 0)
								printf("\nNo circular buffers innitialized !");
							else
							{
								selected_ring = atoi(arguments[arg_counter-1]);
								if(selected_ring < ring_tracker)
								{
									present_ring = selected_ring;
									select_buffer(present_ring);
								}
								else
								{
									printf("\nSelection does not exist! Previous selected buffer active!");
								}
							}
							break;

						case 3:	if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(insert_data(ring,*arguments[arg_counter-1]) == 1)
									printf("\n%c inserted in buffer-%u", *arguments[arg_counter-1],present_ring);
								else
									printf("\nBuffer is full. Could not insert data");
							}
							break;

						case 4: if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(remove_data(ring,&pop_data) == 1)
									printf("\n%c removed from buffer-%u", pop_data,present_ring);
								else
									printf("\nBuffer is empty. Could not remove data");
							}
							break;

						case 5:	if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(entries(ring) == 0)
									printf("\nBuffer-%u is empty. Could not display data",present_ring);
							}
							break;

						case 6:	quit();
							break;
							
					}
				}
				else
				{
					printf("\nInvalid Arguments!\n");
				}
				break;
			}
		}	
		
		if(command_parser == COMMAND_COUNT)
		{
			printf("\nInvalid Command!\n");
		}
	}
	return 0;
}
