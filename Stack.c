#include <stdlib.h>
#include "Stack.h"
#include "ArrayList.h"

struct Stack create_Stack(size_t initial_capacity) {
	struct Stack new;
	new.elements = create_ArrayList(initial_capacity);
	return new;
}

void push(struct Stack* target, void* element) {
	add(&(target->elements), element);
}

void* peek(struct Stack* target) {
	return get(&(target->elements), target->elements.size - 1);
}

void* pop(struct Stack* target) {
	if(target->elements.size == 0)
		return NULL;
	return delete(&(target->elements), target->elements.size - 1);
}

size_t ssize(struct Stack* target) {
	return target->elements.size;
}

size_t scapacity(struct Stack* target) {
	return target->elements.capacity;
}

void guarantee_capacity(struct Stack* target, size_t new_capacity) {
	ensure_capacity(&(target->elements), new_capacity);	
}

void empty(struct Stack* target) {
	clear(&(target->elements));	
}