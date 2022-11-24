#ifndef STDUTIL_PRIORITYQUEUE_H
#define STDUTIL_PRIORITYQUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct priority_queue {
	void **data;
	size_t size, capacity;

	signed char (*comparator) (void *loperand, void *roperand);
} priority_queue;

priority_queue *create_priority_queue(size_t capacity, signed char (*comparator) (void *loperand, void *roperand));

priority_queue *heapify(void **data, size_t size, signed char (*comparator) (void *loperand, void *roperand));

bool pq_add(priority_queue *queue, void *data);

void *pq_remove(priority_queue *queue);

void *pq_peek(priority_queue *queue);

#endif