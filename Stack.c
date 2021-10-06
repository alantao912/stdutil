#include <stdlib.h>
#include "Stack.h"

struct Stack create_Stack(size_t initial_capacity) {
	struct Stack new;
	new.elements = create_ArrayList(initial_capacity);
	return new;
}

void push(struct Stack* target, void* element) {
	al_append(&(target->elements), element);
}

void* peek(struct Stack* target) {
	return al_get(&(target->elements), target->elements.size - 1);
}

void* pop(struct Stack* target) {
	if(target->elements.size == 0)
		return NULL;
	return al_delete(&(target->elements), target->elements.size - 1);
}

size_t s_size(struct Stack* target) {
	return target->elements.size;
}

size_t s_capacity(struct Stack* target) {
	return target->elements.capacity;
}

void s_ensure_capacity(struct Stack* target, size_t new_capacity) {
	al_ensure_capacity(&(target->elements), new_capacity);	
}

void s_clear(struct Stack* target) {
	al_clear(&(target->elements));	
}