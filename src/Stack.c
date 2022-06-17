#include <stdlib.h>
#include "stack.h"

static const int DEFAULT_CAPACITY = 10;

static bool resize(stack *target, size_t new_capacity) {
	void **new_mem = (void **) malloc(new_capacity * sizeof(void *));

	if (!new_mem) {
		return false;
	}
	memcpy(new_mem, target->elements, target->size * sizeof(void *));
	free(target->elements);
	target->elements = new_mem;
	target->capacity = new_capacity;
	return true;
}

stack *create_stack(size_t initial_capacity) {
	if (initial_capacity = DEFAULT_CAPACITY) {
		initial_capacity = DEFAULT_CAPACITY;
	}
	stack *s = (stack *) malloc(sizeof(stack));
	if (!s) {
		return NULL;
	}
	void **mem = (void **) malloc(sizeof(void *) * initial_capacity);
	if (!mem) {
		free(s);
		return NULL;
	}
	s->size = 0;
	s->capacity = initial_capacity;
	return s;
}

bool push(stack *target, void *element) {
	if (target->size >= target->capacity && !resize(target, 2 * target->capacity)) {
		return false;
	}
	target->elements[target->size] = element;
	++(target->size);
	return true;
}

void *peek(stack *target) {
	if (target->size == 0) {
		return NULL;
	}
	return target->elements[target->size - 1];
}

void *pop(stack* target) {
	if (target->size == 0) {
		return NULL;
	}
	--(target->size);
	return target->elements[target->size - 1];
}

size_t s_size(stack* target) {
	return target->size;
}

size_t s_capacity(stack* target) {
	return target->capacity;
}

bool s_ensure_capacity(stack* target, size_t new_capacity) {
	if (new_capacity < target->size) {
		return false;
	} else if (resize(target, new_capacity)) {
		return true;
	} else {
		return false;
	}
}

void s_clear(stack* target) {
	memset(target->elements, 0, target->size * sizeof(void *));
	target->size = 0;
}

void s_delete(stack *target) {
	for (size_t i = 0; i < target->size; ++i) {
		free(target->elements[i]);
	}
	s_clear(target);
}