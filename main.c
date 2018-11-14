#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<stdlib.h>
#include"ring.h"

#define COMMAND_COUNT (4)

typedef struct
{
	ring_t ring_data;
	int int_data;
} data_t;

typedef struct
{
	char command[20];
	unsigned char arg_extraction_count;
} command_t;

int main()
{
	char response[50] = {};
	command_t commands[COMMAND_COUNT] = {{"init",1}, {"insert",1}, {"remove",0}, {"entries",0}}; 
	char* arguments[10] = {};
	char* arg = NULL;
	unsigned char arg_counter = 0, arg_parser = 0, command_parser = 0;
	ring_t *ring = NULL;

	while(1)
	{
		arg_counter = 0;
		
		printf("\nEnter a Command :");
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
						case 0:	ring = init(atoi(arguments[arg_counter-1]));
							printf("\nCircular Buffer Allocate %p\n",ring);
							break;

						case 1:	insert_data(ring,*arguments[arg_counter-1]);
							break;

						case 3:	entries(ring);
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
