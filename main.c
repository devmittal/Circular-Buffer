#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include"ring.h"

int main()
{
	ring_t *ring = NULL;
	ring = init(10);
	printf("\nRing = %p ..... Success\n",ring);

	insert_data(ring,'a');
	insert_data(ring,'b');
	insert_data(ring,'c');
	insert_data(ring,'d');
	insert_data(ring,'e');
	insert_data(ring,'z');
	
	insert_data(ring,'f');
	insert_data(ring,'g');
	insert_data(ring,'h');
	insert_data(ring,'i');
	insert_data(ring,'j');
	insert_data(ring,'k');	

	insert_data(ring,'l');
	insert_data(ring,'m');
	insert_data(ring,'n');
	insert_data(ring,'o');
	insert_data(ring,'p');
	insert_data(ring,'q');
	
	printf("\nData Entries : ");
	entries(ring);
	printf("\n");

	return 0;
}
