#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

struct ArrayList create_ArrayList(size_t initial_capacity) {
	struct ArrayList new;
	new.elements = calloc(initial_capacity, sizeof(void*));
	for(size_t i = 0; i < initial_capacity; i++)
		new.elements[i] = NULL;
	new.size = 0;
	new.capacity = initial_capacity;
	return new;
}

void add(struct ArrayList* target, void* element) {
	if(target->size < target->capacity) {
		target->elements[target->size] = element;
		target->size++;
	} else {
		void** new = calloc(target->size + 1, sizeof(void*));
		for(size_t i = 0; i < target->size; i++)
			new[i] = target->elements[i];
		free(target->elements);
		new[target->size] = element;
		target->elements = new;		
		target->capacity++;
		target->size++;
	}	
}

void insert(struct ArrayList* target, size_t position, void* element) {
	if(target->size < target->capacity) {
		if(position >= target->size)
			return;
		for(size_t i = target->size;i > position;i--)
			target->elements[i] = target->elements[i - 1];
		target->elements[position] = element;
		target->size++;
	} else {
		void** new = calloc(target->capacity + 1, sizeof(void*));
		for(size_t i = 0; i < position; i++)
			new[i] = target->elements[i];
		new[position] = element;
		for(size_t i = position; i < target->size; i++)
			new[i + 1] = target->elements[i];
		free(target->elements);
		target->elements = new;
		target->size++;
		target->capacity++;
	}
}

size_t size(struct ArrayList* target) {
	return target->size;
}

size_t capacity(struct ArrayList* target) {
	return target->capacity;
}

void ensure_capacity(struct ArrayList* target, size_t new_capacity) {
	if(new_capacity > target->size) {
		void** new = calloc(new_capacity, sizeof(void*));		
		for(size_t i = 0; i < target->size; i++)
			new[i] = target->elements[i];
		for(size_t i = target->size; i < new_capacity; i++)
			new[i] = NULL;
		free(target->elements);
		target->elements = new;
		target->capacity = new_capacity;
	}
}

void set(struct ArrayList* target, size_t position, void* element) {
	if(element == NULL)
		return;
	if(position < target->size) {
		free(target->elements[position]);
		target->elements[position] = element;
	}
}

void* get(struct ArrayList* target, size_t position) {
	if(position < target->size)
		return target->elements[position];
	return NULL;
}

void* delete(struct ArrayList* target, size_t position) {
	void* ret = NULL;
	if(position < target->size) {
		void** new = calloc(target->capacity - 1, sizeof(void*));	
		size_t j = 0;
		for(size_t i = 0; i < target->size; i++)
			if(i != position) {
				new[j] = target->elements[i];
				j++;
			} else 
				ret = target->elements[i];
		for(;j < target->capacity - 1; j++)
			new[j] = NULL;
		free(target->elements);
		target->elements = new;
		target->size--;
		target->capacity--;
	}
	return ret;
}

void clear(struct ArrayList* target) {
	int i;
	for(i = 0; i < target->size; i++)
		free(target->elements[i]);
	free(target->elements);
	target->size = 0;
	target->capacity = 0;
}
