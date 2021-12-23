#ifndef UTIL_STACK_H
#define UTIL_STACK_H

#include "ArrayList.h"

struct Stack {
	struct ArrayList elements;
};

struct Stack create_Stack(size_t initial_capacity);

void push(struct Stack *target, void *element);

void* peek(struct Stack *target);

void* pop(struct Stack *target);

size_t s_size(struct Stack *target);

size_t s_capacity(struct Stack *target);

void s_ensure_capacity(struct Stack *target, size_t new_capacity);

void s_clear(struct Stack *target);

void s_delete(struct Stack *target);

#endif