#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<stdlib.h>
#include"ring.h"

#define COMMAND_COUNT (5)

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
	command_t commands[COMMAND_COUNT] = {{"init",1}, {"insert",1}, {"remove",0}, {"entries",0}, {"exit",0}}; 
	char* arguments[10] = {};
	char* arg = NULL;
	unsigned char arg_counter = 0, arg_parser = 0, command_parser = 0;

	ring_t *ring = NULL;
	unsigned int buffer_length = 0;

	printf("\nCircular Buffer");
	printf("\n***************");

	while(1)
	{
		arg_counter = 0;
		
		printf("\n\nInnitialize buffer - init <Buffer Size>");
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
						case 0:	if(ring == NULL)
							{
								buffer_length = atoi(arguments[arg_counter-1]);
								if(buffer_length <= 255)
								{
									if((ring = init(buffer_length)) != NULL)
										printf("\nCircular Buffer Allocate %p",ring);
									else
										printf("\nAllocation of buffer failed !");
								}
								else
									printf("\nBuffer size cannot exceed 255 !");
							}
							else
								printf("\nBuffer already initialized !");
							break;

						case 1:	insert_data(ring,*arguments[arg_counter-1]);
							break;

						case 3:	entries(ring);
							break;

						case 4:	quit();
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
