#include "hashmap.h"

static bool resize(hashmap *map) {
	size_t new_capacity = 2 * map->capacity + 1;
	map_entry *new_table = (map_entry *) calloc(new_capacity, sizeof(map_entry));
	if (!new_table) {
		return false;
	}
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i].key) {
			if (!map->table[i].removed) {
				size_t index = map->hash_function(map->table[i].key) % new_capacity;
				while (new_table[index].key) {
					++index;
					index = index % new_capacity;
				}
				new_table[index] = map->table[i];
				++j;
			}
		}
	}
	free(map->table);
	map->table = new_table;
	map->capacity = new_capacity;
	return true;
}

hashmap *create_hashmap(size_t initial_capacity, float lf) {
	hashmap *hm = (hashmap *) malloc(sizeof(hashmap));
	if (!hm) {
		return NULL;
	}

	hm->table = (map_entry **) calloc(initial_capacity, sizeof(map_entry*));
	if (!(hm->table)) {
		free(hm);
		return NULL;
	}
	hm->capacity = initial_capacity;
	hm->size = 0;
	hm->load_factor = lf;
	hm->hash_function = &default_hash_function;
	hm->comparator = &default_comparator;
	return hm;
}

void *hm_put(hashmap *map, void *key, void *value) {
	if ((((float) (map->size + 1)) / map->capacity > map->load_factor) && !resize(map)) {
		return NULL;
	}

	size_t i = 0, j = 0, index = map->hash_function(key) % map->capacity, removedIndex;
	bool foundRemoved = false;
	while (i < map->capacity && (!foundRemoved || j < map->size)) {
		if (!map->table[index].key) {
			if (foundRemoved) {
				index = removedIndex;
			}
			map->table[index].key = key;
			map->table[index].value = value;
			map->table[index].removed = false;
			++map->size;
			return NULL;
		} else if (map->comparator(key, map->table[index].key)) {
			if (!map->table[index].removed) {
				void *value = map->table[index].value;
				map->table[index].value = value;
				return value;
			} else if (foundRemoved) {
				index = removedIndex;
			}
			map->table[index].key = key;
			map->table[index].value = value;
			map->table[index].removed = false;
			++map->size;
			return NULL;
		} else if (map->table[index].removed) {
			removedIndex = index;
			foundRemoved = true;
		} else {
			++j;
		}
		++i;
		index = ++index % map->capacity;
	}
	return NULL;
}

map_entry *hm_remove(hashmap *map, void *key) {
	size_t i = 0, j = 0, index = map->hash_function(key) % map->capacity;
	while (i < map->capacity && j < map->size) {
		if (!map->table[index].key) {
			return NULL;
		} else if (map->comparator(key, map->table[index].key)) {
			if (map->table[index].removed) {
				return NULL;
			} else {
				map->table[index].removed = true;
				--map->size;
				return &(map->table[index]);
			}
		} else if (!map->table[index].removed) {
			++j;
		}
		++i;
		++index;
		index = index % map->capacity;
	}
	return NULL;
}

void* hm_get(hashmap *map, void *key) {
	size_t i = 0, j = 0, index = map->hash_function(key) % map->capacity;
	while (i < map->capacity && j < map->size) {
		if (!map->table[index].key) {
			return NULL;
		} else if (map->comparator(key, map->table[index].key)) {
			if (map->table[index].removed) {
				return NULL;
			} else {
				return map->table[index].value;
			}
		} else if (!map->table[index].removed) {
			++j;
		}
		++i;
		++index;
		index = index % map->capacity;
	}
	return NULL;
}

bool hm_contains_key(hashmap *map, void *key) {
	return hm_get(map, key) != NULL;
}

arraylist *hm_key_set(hashmap *map) {
	arraylist *keySet = create_arraylist(map->size);
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i].key && !map->table[i].removed) {
			al_add(keySet, map->table[i].key);
			++j;
		}
		++i;
	}
	return keySet;
}

arraylist *hm_values(hashmap *map) {
	arraylist *valueSet = create_arraylist(map->size);
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i].key && !map->table[i].removed) {
			al_add(valueSet, map->table[i].value);
			++j;
		}
		++i;
	}
	return valueSet;
}

static const unsigned int a = 48339, W = 97, M = UINT_MAX;

size_t default_hash_function(const void *key) {
	unsigned long hash = (unsigned long) key;
	return (size_t) floor(((a * hash) % W) * (M / W));
}

bool default_comparator(const void *key0, const void *key1) {
	return key0 == key1;
}

void hm_clear(hashmap *map) {
	for (size_t i = 0; i < map->capacity; ++i) {
		void *key = map->table[i].key;
		if (key && !map->table[i].removed) {
			free(key);
			map->table[i].key = NULL;
		}
	}
	map->size = 0;
}

void hm_delete(hashmap *map) {
	for (size_t i = 0; i < map->capacity; ++i) {
		void *key = map->table[i].key;
		if (key && !map->table[i].removed) {
			free(key);
			free(map->table[i].value);
			map->table[i].key = NULL;
		}
	}
	map->size = 0;
}
