#include "arraylist.h"

static const int DEFAULT_CAPACITY = 10;

static bool resize(arraylist *target, size_t new_capacity) {
	void **new_mem = (void **) malloc(new_capacity * sizeof(void *));
	if (!new_mem) {
		return false;
	}
	memcpy(new_mem, target->elements, sizeof(void *) * new_capacity);
	free(target->elements);
	target->elements = new_mem;
	target->capacity = new_capacity;
	return true;
}

arraylist *create_arraylist(size_t initial_capacity) {
	if (initial_capacity == 0) {
		initial_capacity = DEFAULT_CAPACITY;
	}
	arraylist *new = (arraylist *) malloc(sizeof(arraylist));

	if (!new) {
		return NULL;
	}

	new->elements = (void **) malloc(initial_capacity * sizeof(void *));

	if (!new->elements) {
		free(new);
		return NULL;
	}
	memset(new->elements, 0, sizeof(void *) * initial_capacity);
	new->size = 0;
	new->capacity = initial_capacity;
	return new;
}

bool al_add(arraylist *target, void *element) {
	if (target->size >= target->capacity && !resize(target, 2 * target->capacity)) {
		return false;
	}
	target->elements[target->size] = element;
	++(target->size);
	return true;
}

bool al_addAt(arraylist *target, size_t position, void *element) {
	if (position > target->size || (target->size >= target->capacity && !resize(target, 2 * target->capacity))) {
		return false;
	}

	for (size_t i = target->size; i > position; --i) {
		target->elements[i] = target->elements[i - 1];
	}
	target->elements[position] = element;
	++target->size;
	return true;
}

bool al_ensure_capacity(arraylist* target, size_t new_capacity) {
	if (new_capacity < target->size) {
		return false;
	} else if (resize(target, new_capacity)) {
		return true;
	} else {
		return false;
	}
}

void *al_set(arraylist *target, size_t position, void *element) {
	void *ret = NULL;
	if (position < target->size) {
		ret = target->elements[position];
		target->elements[position] = element;
	}
	return ret;
}

void *al_get(arraylist *target, size_t position) {
	if (position < target->size) {
		return target->elements[position];
	}
	return NULL;
}

void *al_remove(arraylist *target, size_t position) {
	void *ret = NULL;
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

static void quicksort(arraylist *arr, size_t start, size_t end, int (*comparator)(const void* cmpl, const void* cmpr)) {
	if (end - start <= 1) {
		return;
	}
	size_t pivot = rand() % (end - start) + start;
	void *swap = arr->elements[pivot];
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

void sort(arraylist *target, int (*comparator)(const void *cmpl, const void *cmpr)) {
	time_t t;
	srand((unsigned) time(&t));
	quicksort(target, 0, target->size, comparator);
}

void al_delete(arraylist *target) {
	for (size_t i = 0; i < target->size; ++i) {
		free(target->elements[i]);
	}
	al_clear(target);
}

void al_clear(arraylist *target) {
	memset(target->elements, 0, target->size * sizeof(void *));
	target->size = 0;
}
