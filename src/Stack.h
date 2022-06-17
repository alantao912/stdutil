#ifndef UTIL_STACK_H
#define UTIL_STACK_H

#include <stdbool.h>
#include <string.h>
#include "arraylist.h"

typedef struct stack {
	void **elements;
	size_t size, capacity;
} stack;

stack *create_stack(size_t initial_capacity);

bool push(stack *target, void *element);

void* peek(stack *target);

void* pop(stack *target);

size_t s_size(stack *target);

size_t s_capacity(stack *target);

bool s_ensure_capacity(stack *target, size_t new_capacity);

void s_clear(stack *target);

void s_delete(stack *target);

#endif