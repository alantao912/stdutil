#include "queue.h"

queue *create_queue(size_t initialCapacity) {
	queue *q = (queue *) malloc(sizeof(queue));
	if (!q) {
		return NULL;
	}
	q->data = (void **) malloc(initialCapacity * sizeof(void *));
	if (!q->data) {
		free(q);
		return NULL;
	}
	memset(q->data, 0, initialCapacity * sizeof(void *));
	q->capacity = initialCapacity;
	q->size = 0;
	q->front = 0;
	return q;
}

static bool resize(queue *target) {
	void **new_mem = (void **) malloc(2 * target->capacity * sizeof(void *));
	if (!new_mem) {
		return false;
	}
	for (size_t i = 0; i < target->size; ++i) {
		new_mem[i] = target->data[(i + target->front) % target->capacity];
	}
	free(target->data);
	target->data = new_mem;
	target->capacity = 2 * target->capacity;
	return true;
}

bool enqueue(queue *target, void *element) {
	if (target->size >= target->capacity && !resize(target)) {
		return false;
	}
	target->data[(target->front + target->size) % target->capacity] = element;
	++target->size;
	return true;
}

void *dequeue(queue *target) {
	void *ret = NULL;
	if (target->size > 0) {
		ret = target->data[target->front];
		target->front = (++target->front) % target->capacity;
		--target->size;
	}
	return ret;
}

void q_clear(queue *target) {
	target->front = 0;
	target->size = 0;
}

void q_delete(queue *target) {
	for (size_t i = 0; i < target->size; ++i) {
		free(target->data[(i + target->front) % target->capacity]);
	}
	target->front = 0;
	target->size = 0;
}
