#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue {
	void **data;
	size_t front, size, capacity;
} queue;

queue *create_queue(size_t initialCapacity);

/*
	Adds an element to the back of the queue.
*/

void enqueue(queue *target, void *element);

/*
	Removes an element from the front of the queue.
*/

void* dequeue(queue *target);

/*
	Removes all data from queue.

*/

void q_clear(queue *target);

/*
	Removes and frees all data from queue.
*/

void q_delete(queue *target);

#endif