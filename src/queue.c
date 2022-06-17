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

void enqueue(queue *target, void *element) {
	if (target->size < target->capacity) {
		target->data[(target->front + target->size) % target->capacity] = element;
	} else {
		void **new = (void **) malloc(2 * target->capacity * sizeof(void *));
		size_t i;
		for (i = 0; i < target->size; ++i) {
			new[i] = target->data[(target->front + i) % target->capacity];
		}
		new[i] = element;
		free(target->data);
		target->data = new;
		target->front = 0;
		target->capacity *= 2;
	}
	++target->size;
}

void *dequeue(queue *target) {
	void *ret = NULL;
	if (target->size > 0) {
		ret = target->data[target->front];
		target->data[target->front] = NULL;
		target->front = (++target->front) % target->capacity;
		--target->size;
	}
	return ret;
}

void q_clear(queue *target) {
	for (size_t i = 0; i < target->size; ++i) {
		target->data[(i + target->front) % target->capacity] = NULL;
	}
	target->front = 0;
	target->size = 0;
}

void q_delete(queue *target) {
	for (size_t i = 0; i < target->size; ++i) {
		free(target->data[(i + target->front) % target->capacity]);
		target->data[(i + target->front) % target->capacity] = NULL;
	}
	target->front = 0;
	target->size = 0;
}
