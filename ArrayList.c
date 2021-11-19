#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArrayList.h"

static const int DEFAULT_CAPACITY = 10;

struct ArrayList create_ArrayList(size_t initial_capacity) {
	if (initial_capacity == 0) {
		initial_capacity = DEFAULT_CAPACITY;
	}
	struct ArrayList new;
	new.elements = calloc(initial_capacity, sizeof(void*));
	for (size_t i = 0; i < initial_capacity; i++) {
		new.elements[i] = NULL;
	}
	new.size = 0;
	new.capacity = initial_capacity;
	return new;
}

bool al_append(struct ArrayList* target, void* element) {
	if (target->size < target->capacity) {
		target->elements[target->size] = element;
		target->size++;
	} else {
		void** new = calloc(target->capacity * 2, sizeof(void*));
		if (!new) {
			return false;
		}
		for (size_t i = 0; i < target->size; i++) {
			new[i] = target->elements[i];
		}
		free(target->elements);
		new[target->size] = element;
		target->elements = new;		
		target->capacity *= 2;
		target->size++;
	}
	return true;	
}

bool al_addAt(struct ArrayList* target, size_t position, void* element) {

	if (position >= target->size) {
		return false;
	}
	if (target->size < target->capacity) {
		for(size_t i = target->size; i > position; --i) {
			target->elements[i] = target->elements[i - 1];
		}
		target->elements[position] = element;
	} else {
		void** new = calloc(target->capacity * 2, sizeof(void*));
		if (!new) {
			return false;
		}
		for (size_t i = 0; i < position; ++i) {
			new[i] = target->elements[i];
		}
		new[position] = element;
		for (size_t i = position; i < target->size; ++i) {
			new[i + 1] = target->elements[i];
		}
		free(target->elements);
		target->elements = new;
		target->capacity *= 2;
	}
	++target->size;
	return true;
}

size_t al_size(struct ArrayList* target) {
	return target->size;
}

size_t al_capacity(struct ArrayList* target) {
	return target->capacity;
}

bool al_ensure_capacity(struct ArrayList* target, size_t new_capacity) {
	if (new_capacity > target->capacity) {
		void** new = calloc(new_capacity, sizeof(void*));
		if (!new) {
			return false;
		}
		for (size_t i = 0; i < target->size; ++i) {
			new[i] = target->elements[i];
		}
		for (size_t i = target->size; i < new_capacity; ++i) {
			new[i] = NULL;
		}
		free(target->elements);
		target->elements = new;
		target->capacity = new_capacity;
		return true;
	}
	return false;
}

void* al_set(struct ArrayList* target, size_t position, void* element) {
	if (position >= target->size) {
		return NULL;
	}
	void* ret = target->elements[position];
	target->elements[position] = element;
	return ret;
}

void* al_get(struct ArrayList* target, size_t position) {
	if (position < target->size) {
		return target->elements[position];
	}
	return NULL;
}

void* al_delete(struct ArrayList* target, size_t position) {
	void* ret = NULL;
	if (position < target->size) {
		ret = target->elements[position];
		size_t i;
		for (i = position; i < target->size - 1; ++i) {
			target->elements[i] = target->elements[i + 1];
		}
		target->elements[i] = NULL;
		--target->size;
	}
	return ret;
}

static void quicksort(struct ArrayList* arr, size_t start, size_t end, int (*comparator)(const void* cmpl, const void* cmpr)) {
	if (end - start <= 1) {
		return;
	}
	size_t pivot = rand() % (end - start) + start;
	void* swap = arr->elements[pivot];
	arr->elements[pivot] = arr->elements[start];
	arr->elements[start] = swap;

	size_t i = start + 1, j = end - 1;

	while (i <= j) {
		while (i <= j && (*comparator)(arr->elements[start], arr->elements[i]) > 0) {
			++i;
		}

		while (i <= j && (*comparator)(arr->elements[start], arr->elements[j]) < 0) {
			--j;
		}

		if (i <= j) {
			swap = arr->elements[j];
			arr->elements[j] = arr->elements[i];
			arr->elements[i] = swap;

			++i;
			--j;
		}
	}
	swap = arr->elements[j];
	arr->elements[j] = arr->elements[start];
	arr->elements[start] = swap;
	
	quicksort(arr, start, j, comparator);
	quicksort(arr, j + 1, end, comparator);	
}

void sort(struct ArrayList* target, int (*comparator)(const void* cmpl, const void* cmpr)) {
	time_t t;
	srand((unsigned) time(&t));
	quicksort(target, 0, target->size, comparator);
}

void al_clear(struct ArrayList* target) {
	for (size_t i = 0; i < target->size; i++) {
		free(target->elements[i]);
	}
	free(target->elements);
	target->elements = (void**)calloc(DEFAULT_CAPACITY, sizeof(void*));
	target->size = 0;
	target->capacity = DEFAULT_CAPACITY;
}
