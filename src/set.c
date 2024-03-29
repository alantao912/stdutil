#include "set.h"

static bool resize(struct set *set) {
	size_t new_capacity = 2 * set->capacity + 1;
	struct set_entry *new_array = (struct set_entry*) malloc(new_capacity * sizeof(struct set_entry));

	if (!new_array) {
		return false;
	}

	for (size_t i = 0; i < new_capacity; ++i) {
		new_array[i].data = NULL;
		new_array[i].removed = false;
	}

	size_t i = 0, j = 0;
	while (i < set->capacity && j < set->cardinality) {
		if (set->data[i].data) {
			if (!set->data[i].removed) {
				size_t index = set->hash_function(set->data[i].data) % new_capacity;
				while (new_array[index].data) {
					++index;
					index = index % new_capacity;
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
	return true;
}

struct set *create_set(size_t initial_capacity) {
	struct set *set = (struct set *) malloc(sizeof(struct set));
	if (!set) {
		return NULL;
	}
	set->data = (struct set_entry *) malloc(initial_capacity * sizeof(struct set_entry));

	if (!set->data) {
		free(set);
		return NULL;
	}

	for (size_t i = 0; i < initial_capacity; ++i) {
		set->data[i].data = NULL;
		set->data[i].removed = false;
	}
	set->cardinality = 0;
	set->capacity = initial_capacity;
	set->lf = 0.67f;
	set->hash_function = &default_hash_function;
	set->comparator = &default_comparator;
	return set;
}

bool set_add(struct set *set, void *element) {
	if (!element) {
		return false;
	}

	if ((float) (set->cardinality + 1) / set->capacity > set->lf && !resize(set)) {
		/* OOM returns false */
		return false;
	}

	size_t i = 0, j = 0, index = set->hash_function(element) % set->capacity, removedIndex;
	bool foundRemoved = false;
	while (i < set->capacity && (!foundRemoved || j < set->cardinality)) {
		if (!set->data[index].data) {
			if (foundRemoved) {
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
				index = removedIndex;
			}
			set->data[index].data = element;
			set->data[index].removed = false;
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

void *set_remove(struct set *set, void *element) {
	if (!element) {
		return NULL;
	}

	size_t i = 0, j = 0, index = set->hash_function(element) % set->capacity;
	while (i < set->capacity && j < set->cardinality) {
		if (!set->data[index].data) {
			return false;
		} else if (set->comparator(element, set->data[index].data)) {
			if (set->data[index].removed) {
				return NULL;
			} else {
				set->data[index].removed = true;
				--set->cardinality;
				return set->data[index].data;
			}
		} else if (!set->data[index].removed) {
			++j;
		}
		++i;
		++index;
		index = index % set->capacity;
	}
	return NULL;
}

bool set_contains(struct set *set, void *element) {
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
		++index;
		index = index % set->capacity;
	}
	return false;
}

void set_clear(struct set *set) {
	for (size_t i = 0; i < set->capacity; ++i) {
		set->data[i].data = NULL;
		set->data[i].removed = false;
	}
	set->cardinality = 0;
}

void set_delete(struct set *set) {
	for (size_t i = 0; i < set->capacity; ++i) {
		free(set->data[i].data);
		set->data[i].data = NULL;
		set->data[i].removed = false;
	}
	set->cardinality = 0;
}
