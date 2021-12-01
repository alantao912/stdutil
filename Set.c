#include "Set.h"
#include <math.h>
#include "HashMap.h"

static void resize(struct Set *set);

struct Set create_Set(size_t initial_capacity) {
	struct Set set;
	set.set = (void**) calloc(initial_capacity, sizeof(void*));
	for (size_t i = 0; i < initial_capacity; ++i) {
		set.set[i] = NULL;
	}
	set.cardinality = 0;
	set.capacity = initial_capacity;
	set.iterator = 0;
	set.hash_function = &default_hash_function;
	set.comparator = &default_comparator;
	return set;
}

bool set_add(struct Set *set, void *element) {
	
	return false;
}

bool set_remove(struct Set *set, void *element) {
	
	
}

bool set_contains(struct Set *set, void *element) {
	
}

void* set_next(struct Set* set) {
	
}

static void resize(struct Set *set) {
	
}
