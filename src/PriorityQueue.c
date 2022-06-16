#include <stddef.h>
#include <stdlib.h>
#include "PriorityQueue.h"

struct PriorityQueue create_PriorityQueue(size_t capacity) {
	struct PriorityQueue pq = {.data = (void**) calloc(capacity, sizeof(void*)), .size = 0, .capacity = capacity};
	return pq;
}

static void downheap(struct PriorityQueue pq, size_t index);

static void downheap(struct PriorityQueue pq, size_t index) {
	if (index > pq.size / 2) {
		return;
	}
	
	void *current = pq.data[index], *leftChild = pq.data[2 * index], *rightChild = pq.data[2 * index + 1];
	int leftDifference = pq.comparator(current, leftChild), rightDifference = 0;

	if (rightChild) {
		rightDifference = pq.comparator(current, rightChild);
	}

	if (leftDifference > 0 && rightDifference > 0) {
		// Both leftchild and rightchild are smaller than parent
		if (pq.comparator(leftChild, rightChild) < 0) {
			// left child is smaller than rightchild
			pq.data[2 * index] = current;
			pq.data[index] = leftChild;
			downheap(pq, 2 * index);
		} else {
			pq.data[2 * index + 1] = current;
			pq.data[index] = rightChild;
			downheap(pq, 2 * index + 1);
		}
	} else if (leftDifference > 0) {
		pq.data[2 * index] = current;
		pq.data[index] = leftChild;
		downheap(pq, 2 * index);
	} else if (rightDifference > 0) {
		pq.data[2 * index + 1] = current;
		pq.data[index] = rightChild;
		downheap(pq, 2 * index + 1);
	}
}

struct PriorityQueue heapify(void **data, size_t size) {
	struct PriorityQueue pq = {.data = (void**) calloc(2 * size + 1, sizeof(void*)), .size = 0, .capacity = 2 * size + 1};
	size_t j = 1;
	for (size_t i = 0; i < size; ++i) {
		if (data[i]) {
			pq.data[j] = data[i];
			++j;
		}
	}
	pq.size = j - 1;
	for (size_t i = pq.size / 2; i > 0; --i) {
		downheap(pq, i);
	}
}

static void upheap(struct PriorityQueue pq, size_t index);

static void upheap(struct PriorityQueue pq, size_t index) {
	if (index <= 1) {
		return;
	}

	void *parent = pq.data[index / 2];
	if (pq.comparator(pq.data[index], parent) < 0) {
		pq.data[index / 2] = pq.data[index];
		pq.data[index] = parent;
		upheap(pq, index / 2);
	}
}

void pq_add(struct PriorityQueue *queue, void *data) {
	if (queue->size + 1 >= queue->capacity) {
		queue->capacity *= 2;
		void **new_array = (void**) calloc(queue->capacity, sizeof(void*));
		
		size_t i;
		
		for (i = 1; i <= queue->size; ++i) {
			new_array[i] = queue->data[i];
		}
		
		for (; i < queue->capacity; ++i) {
			new_array[i] = NULL;
		}
		queue->data = new_array;
	}
	++queue->size;
	queue->data[queue->size] = data;
	upheap(*queue, queue->size);
}

void* pq_remove(struct PriorityQueue *queue) {
	void *value = queue->data[1];
	queue->data[1] = queue->data[queue->size];
	queue->data[queue->size] = NULL;
	--queue->size;
	downheap(*queue, 1);
	return value;
}

void* pq_peek(struct PriorityQueue queue) {
	return queue.data[1];
}