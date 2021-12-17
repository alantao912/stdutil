#include "Set.h"
#include <math.h>
#include <stdlib.h>
#include "HashMap.h"

#include <stdio.h>

static void resize(struct Set *set);

struct Set create_Set(size_t initial_capacity) {
	struct Set set;
	set.data = (struct SetEntry*) calloc(initial_capacity, sizeof(struct SetEntry));
	for (size_t i = 0; i < initial_capacity; ++i) {
		set.data[i].data = NULL;
		set.data[i].removed = false;
	}
	set.cardinality = 0;
	set.capacity = initial_capacity;
	set.lf = 0.67f;
	set.hash_function = &default_hash_function;
	set.comparator = &default_comparator;
	return set;
}

bool set_add(struct Set *set, void *element) {
	if (!element) {
		return false;
	}
	
	if ((float) (set->cardinality + 1) / set->capacity > set->lf) {
		resize(set);
	}
	
	size_t i = 0, j = 0, index = set->hash_function(element) % set->capacity, removedIndex;
	bool foundRemoved = false;

	while (i < set->capacity && (!foundRemoved || j < set->cardinality)) {
		
		if (!set->data[index].data) {
			
			if (foundRemoved) {
				free(set->data[removedIndex].data);
				set->data[removedIndex].data = element;
				set->data[removedIndex].removed = false;
			} else {
				set->data[index].data = element;
			}
			++set->cardinality;
			return true;
		} else if (set->comparator(element, set->data[index].data)) {
			
			if (!set->data[index].removed) {
				return false;
			} else if (foundRemoved) {
				free(set->data[removedIndex].data);
				set->data[removedIndex].data = element;
				set->data[removedIndex].removed = false;
			} else {
				if (set->data[index].data != element) {
					free(set->data[index].data);
				}
				set->data[index].data = element;
				set->data[index].removed = false;
			}
			++set->cardinality;
			return true;
		} else if (set->data[index].removed) {
			removedIndex = index;
			foundRemoved = true;
		} else {
			++j;
		}
		++i;
		index = ++index % set->capacity;
	}
	return false;
}

bool set_remove(struct Set *set, void *element) {
	if (!element) {
		return false;
	}
	
	size_t i = 0, j = 0, index = set->hash_function(element) % set->capacity;

	while (i < set->capacity && j < set->cardinality) {
		if (!set->data[index].data) {
			return false;
		} else if (set->comparator(element, set->data[index].data)) {
			if (set->data[index].removed) {
				return false;
			} else {
				set->data[index].removed = true;
				--set->cardinality;
				return true;
			}
		} else if (!set->data[index].removed) {
			++j;
		}
		++i;
		index = ++index % set->capacity;
	}
	return false;
}

bool set_contains(struct Set *set, void *element) {
	if (!element) {
		return false;
	}
	
	size_t i = 0, j = 0, index = set->hash_function(element) % set->capacity;
	
	while (i < set->capacity && j < set->cardinality) {
		if (!set->data[index].data) {
			return false;
		} else if (set->comparator(element, set->data[index].data)) {
			return !set->data[index].removed;
		} else if (!set->data[index].removed) {
			++j;
		}
		++i;
		index = ++index % set->capacity;
	}
	return false;
}

static void resize(struct Set *set) {
	size_t new_capacity = 2 * set->capacity + 1;
	struct SetEntry *new_array = (struct SetEntry*) calloc(new_capacity, sizeof(struct SetEntry));

	for (size_t i = 0; i < new_capacity; ++i) {
		new_array[i].data = NULL;
		new_array[i].removed = false;
	}
	
	size_t i = 0, j = 0;
	while (i < set->capacity && j < set->cardinality) {
		if (set->data[i].data) {
			if (set->data[i].removed) {
				free(set->data[i].data);
			} else {
				size_t index = set->hash_function(set->data[i].data) % new_capacity;
				while (new_array[index].data) {
					index = ++index % new_capacity;
				}
				new_array[index].data = set->data[i].data;
				++j;
			}
		}
		++i;
	}
	free(set->data);
	set->data = new_array;
	set->capacity = new_capacity;
}
