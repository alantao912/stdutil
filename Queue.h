#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H

#include <stddef.h>

struct Queue {
	void** data;
	size_t front, size, capacity;
};

struct Queue create_Queue(size_t initialCapacity);

void enqueue(struct Queue *target, void *element);

void* dequeue(struct Queue *target);

void q_clear(struct Queue *target);

#endif