#ifndef RING_H
#define RING_H

typedef struct
{
	char *Buffer;
	int Length;
	int Ini;	//Rear
	int Outi;	//front
} ring_t;

ring_t* init(int length);
int insert_data(ring_t *ring, char data);
int remove_data(ring_t *ring, char *data);
int entries(ring_t *ring);

#endif

