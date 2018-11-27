/*****************************************************************************
​ ​* ​ ​ @file​ ​  main.c
​ * ​ ​ @brief​ ​ The main function of this program which contains the user menu,
 *	     function calls for each function and bound checking. 
 *   @Tools_Used GCC
​ * ​ ​ @author​  ​​Souvik De, Devansh Mittal
​ * ​ ​ @date​ ​ November 27th, 2018
​ * ​ ​ @version​ ​ 1.0
*****************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<stdlib.h>
#include"../inc/ring.h"

/* Structure to store the commands */
typedef struct
{
	char command[20]; //Store command name
	unsigned char arg_extraction_count; //Stores number of arguments with that command
} command_t;

/* Function to Exit Menu */
void quit(void)
{
	exit(0);
}

int main()
{
	char response[50] = {}; //Stores user input
	/* initializing structure with the different commands */
	command_t commands[COMMAND_COUNT] = {{"create",1}, {"init",1}, {"select",1}, {"insert",1}, {"remove",0}, 
						{"entries",0}, {"resize",1}, {"exit",0}}; 
	char* arguments[10] = {};
	char* arg = NULL;
	unsigned char arg_counter = 0, arg_parser = 0, command_parser = 0;
	char pop_data;

	unsigned int buffer_length = 0, ring_tracker = 0, selected_ring = 0, ring_count = 0, present_ring = 0;
	char deleted_data = 0;
	int init_status; 

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
		printf("\nResize buffer - resize <Resize Length for selected Buffer>");
		printf("\nExit program - exit");

		printf("\n\n>>");
		fgets(response, sizeof response, stdin); //Accepts user input
		arg = strtok(response," \n"); //Separates the command name from the arguments
				
		while(arg != NULL)
		{
			arguments[arg_counter++] = arg; //Stores the command name and corresponding argument in an array
			arg = strtok(NULL," ");
		} 

/* the following loops determine which command is input by the user and accordingly calls the function using switch statement */
		for(command_parser = 0 ;  command_parser < COMMAND_COUNT ; command_parser++)
		{
			if(strcmp(arguments[0],commands[command_parser].command) == 0)
			{
				if((arg_counter - 1) == commands[command_parser].arg_extraction_count)
				{
					switch(command_parser)
					{
						/*Allocates space for mulitple buffers as input by user */
						case 0:	if(ring_collector == NULL) //Checks if buffer is not already created
							{
								/* Converts number of buffers input by user to integer */
								ring_count = (unsigned int)atoi(arguments[arg_counter-1]); 
								ring_collector = create_buffers(ring_count); //Call function
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
						/* Initializes buffers created in the above function in a sequential manner with user inputted size */
						case 1:	if(ring_collector != NULL) //Checks if the circular buffers have been created
							{
								buffer_length = atoi(arguments[arg_counter-1]); //Converts buffer size to integer
								init_status = init(buffer_length, ring_tracker, ring_count); //Function call
								if(init_status == 1) //If successful, increment to the next buffer
									ring_tracker += 1;
								else if(init_status == 0)
									printf("\nAllocation of buffer failed !");
								else
									printf("\nAll the circular buffers have been allocated!");
							}
							else
								printf("\nNo circular buffers created!"); 
							break;
						/* Selects a buffer to carry out operations based on user input */
						case 2:	if(ring_tracker == 0) //Checks if circular buffer has been initialized
								printf("\nNo circular buffers innitialized !");
							else
							{
								selected_ring = atoi(arguments[arg_counter-1]);
								if(selected_ring < ring_tracker) //Bound Checking
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
						/* Insert Data */
						case 3:	if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(insert_data(ring,*arguments[arg_counter-1]) == 1) //Function call
									printf("\n%c inserted in buffer-%u", *arguments[arg_counter-1],present_ring);
								else
									printf("\nBuffer is full. Could not insert data");
							}
							break;
						/* Remove Data */
						case 4: if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(remove_data(ring,&pop_data) == 1) //Function call
									printf("\n%c removed from buffer-%u", pop_data,present_ring);
								else
									printf("\nBuffer is empty.");
							}
							break;
						/* Display entries in a buffer */
						case 5:	if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								if(entries(ring) == 0) //Function call
									printf("\nBuffer-%u is empty. Could not display data",present_ring);
							}
							break;
						/* Resize existing buffers */
						case 6:	if(ring == NULL)
							{
								if(ring_collector == 0)
									printf("\nNo circular buffers innitialized !");
								else
									printf("\nNo circular buffer selected !");
							}
							else
							{
								resize(atoi(arguments[arg_counter-1]),present_ring,ring_count); //Function call
							}
							break;

						case 7:	quit();
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
