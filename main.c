#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include"ring.h"

int main()
{
	char response[50] = {};
	char* arguments[10] = {};
	char* arg = NULL;
	unsigned char arg_counter = 0, arg_parser = 0;
	ring_t *ring = NULL;

	printf("\nEnter a Command :");
	scanf("%s",response);
	
	arg = strtok(response,"-");
	while(arg != NULL)
	{
		arguments[arg_counter++] = arg;
		arg = strtok(NULL,"-");
	} 

	for(arg_parser = 0 ; arg_parser < arg_counter ; arg_parser++)
		printf("%s\n",arguments[arg_parser]);	

	return 0;
}
