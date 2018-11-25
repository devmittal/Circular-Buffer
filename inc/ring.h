#ifndef RING_H
#define RING_H


typedef struct
{
	char *Buffer;
	int Length;
	int Ini;	//Rear
	int Outi;	//front
} ring_t;

ring_t *ring;
ring_t **ring_collector;

ring_t** create_buffers(unsigned int ring_count);
int init(int length, unsigned int ring_tracker, unsigned int ring_count);
void select_buffer(unsigned int present_ring);
int insert_data(ring_t *ring, char data);
int remove_data(ring_t *ring, char *data);
int entries(ring_t *ring);
void report(unsigned int ring_count);

#endif

