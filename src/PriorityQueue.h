#ifndef STDUTIL_PRIORITYQUEUE_H
#define STDUTIL_PRIORITYQUEUE_H

struct PriorityQueue {
	void **data;
	size_t size, capacity;

	signed char (*comparator)(void *loperand, void *roperand);
};

struct PriorityQueue create_PriorityQueue(size_t capacity);

struct PriorityQueue heapify(void **data, size_t size);

void pq_add(struct PriorityQueue *queue, void *data);

void* pq_remove(struct PriorityQueue *queue);

void* pq_peek(struct PriorityQueue queue);

#endif