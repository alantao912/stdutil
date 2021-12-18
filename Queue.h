#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

#include <stddef.h>

struct Queue {
	void** data;
	size_t front, size, capacity;
};

struct Queue create_Queue(size_t initialCapacity);

/*
	Adds an element to the back of the queue.
*/

void enqueue(struct Queue *target, void *element);

/*
	Removes an element from the front of the queue.
*/

void* dequeue(struct Queue *target);

/*
	Removes all data from queue.

*/

void q_clear(struct Queue *target);

/*
	Removes and frees all data from queue.
*/

void q_delete(struct Queue *target);

#endif