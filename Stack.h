#ifndef UTIL_STACK_H
#define UTIL_STACK_H

#include "ArrayList.h"

struct Stack {
	struct ArrayList elements;
};

struct Stack create_Stack(size_t initial_capacity);

void push(struct Stack* target, void* element);

void* peek(struct Stack* target);

void* pop(struct Stack* target);

size_t ssize(struct Stack* target);

size_t scapacity(struct Stack* target);

void guarantee_capacity(struct Stack* target, size_t new_capacity);

void empty(struct Stack* target);

#endif