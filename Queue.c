#include "Queue.h"
#include <stdlib.h>

struct Queue create_Queue(size_t initialCapacity) {
	struct Queue queue = {.data = NULL, .front = 0, .size = 0, .capacity = initialCapacity};
	queue.data = (void**) calloc(queue.capacity, sizeof(void*));
	for(int i = 0; i < queue.capacity; ++i)
		queue.data[i] = NULL;
	return queue;
}

void enqueue(struct Queue* target, void* element) {
	if(target->size < target->capacity)
		target->data[(target->front + target->size) % target->capacity] = element;
	else {
		void** new = (void**) calloc(target->capacity * 2 ,sizeof(void*));
		size_t i;
		for(i = 0; i < target->size; ++i)
			new[i] = target->data[(target->front + i) % target->capacity];
		new[i] = element;
		free(target->data);
		target->data = new;
		target->front = 0;
		target->capacity *= 2;
	}
	++target->size;
}

void* dequeue(struct Queue* target) {
	void* ret = NULL;
	if(target->size > 0) {
		ret = target->data[target->front];
		target->data[target->front] = NULL;
		target->front = (++target->front) % target->capacity;
		--target->size;
	}
	return ret;
}