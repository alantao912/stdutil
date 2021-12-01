#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "HashMap.h"

static void resize(struct HashMap* map);

struct HashMap create_HashMap(size_t initial_capacity, float lf) {
	struct HashMap hm;
	hm.table = (struct MapEntry**) calloc(initial_capacity, sizeof(struct MapEntry*));
	hm.capacity = initial_capacity;
	hm.size = 0;
	hm.load_factor = lf;
	hm.hash_function = &default_hash_function;
	hm.comparator = &default_comparator;
	return hm;
}

void* hm_put(struct HashMap* map, void* key, void* value) {
	
	if (((float) map->size + 1) / map->capacity > map->load_factor) {
		resize(map);
	}

	size_t i = 0, j = 0, removedIndex;
	bool foundRemoved = false;
	while (i < map->capacity && j < map->size) {
		size_t index = (map->hash_function(key) + i) % map->capacity;
		if (!map->table[index]) {
			if (foundRemoved) {
				// free this line
				void* value = map->table[removedIndex]->value;
				map->table[removedIndex]->value = value;
				free(map->table[removedIndex]->key);
				map->table[removedIndex]->key = key;
				++map->size;
			} else {
				map->table[index] = (struct MapEntry*) malloc(sizeof(struct MapEntry));
				map->table[index]->key = key;
				map->table[index]->value = value;
			}
			return NULL;
		} else if (map->comparator(key, map->table[index]->key)) {
			if (!map->table[index]->removed) {
				void* value = map->table[index]->value;
				map->table[index]->value = value;
				free(map->table[index]->key);
				map->table[index]->key = key;
				return value;
			} else if (foundRemoved) {
				free(map->table[removedIndex]->key);
				map->table[removedIndex]->key = key;
				free(map->table[removedIndex]->value);
				map->table[removedIndex]->value = value;
				map->table[removedIndex]->removed = false;
			} else {
				free(map->table[index]->key);
				map->table[index]->key = key;
				free(map->table[index]->value);
				map->table[index]->value = value;
				map->table[index]->removed = false;
			}
			++map->size;
			return NULL;
		} else if (map->table[index]->removed) {
			removedIndex = index;
			foundRemoved = true;
		} else {
			++j;
		}
		++i;
	}
	return NULL;
}

void* hm_remove(struct HashMap* map, void* key) {
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		size_t index = (map->hash_function(key) + i) % map->capacity;
		if (!map->table[index]) {
			return NULL;
		} else if (map->comparator(key, map->table[index]->key)) {
			if (map->table[index]->removed) {
				return NULL;
			} else {
				map->table[index]->removed = true;
				--map->size;
				return map->table[index]->value;
			}
		} else if (!map->table[index]->removed) {
			++j;
		}
		++i;
	}
	return NULL;	
}

void* hm_get(struct HashMap* map, void* key) {
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		size_t index = (map->hash_function(key) + i) % map->capacity;
		if (!map->table[index]) {
			return NULL;
		} else if (map->comparator(key, map->table[index]->key)) {
			if (map->table[index]->removed) {
				return NULL;
			} else {
				return map->table[index]->value;
			}
		} else if (!map->table[index]->removed) {
			++j;
		}
		++i;
	}
	return NULL;
}

bool hm_containsKey(struct HashMap* map, void* key) {
	return hm_get(map, key) != NULL;
}

struct ArrayList keySet(struct HashMap* map) {
	struct ArrayList keySet = create_ArrayList(map->size);
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i] && !map->table[i]->removed) {
			al_append(&keySet, map->table[i]->key);
			++j;
		}
		++i;
	}
	return keySet;
}

struct ArrayList values(struct HashMap* map) {
	struct ArrayList valueSet = create_ArrayList(map->size);
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i] && !map->table[i]->removed) {
			al_append(&valueSet, map->table[i]->value);
			++j;
		}
		++i;
	}
	return valueSet;
}

static const unsigned int a = 48339, W = 97, M = UINT_MAX;

size_t default_hash_function(void* key) {
	unsigned int hash = (unsigned int)key;
	return (size_t) floor(((a * hash) % W) * (M / W));
}

bool default_comparator(void *key0, void *key1) {
	return key0 == key1;
}

static void resize(struct HashMap* map) {
	size_t new_capacity = 2 * map->capacity + 1;
	struct MapEntry** new_table = (struct MapEntry**) calloc(new_capacity, sizeof(struct MapEntry*));
	size_t i = 0, j = 0;
	while (i < map->capacity && j < map->size) {
		if (map->table[i] && !map->table[i]->removed) {
			for (size_t k = 0; k < map->capacity; ++k) {
				size_t index = (map->hash_function(map->table[i]->key) + k) % new_capacity;
				if (!map->table[index]) {
					new_table[index] = (struct MapEntry*) malloc(sizeof(struct MapEntry));
					new_table[index]->key = map->table[i]->key;
					new_table[index]->value = map->table[i]->value;
					free(map->table[i]);
					break;
				}
			}
			++j;
		}
	}
	free(map->table);
	map->table = new_table;
	map->capacity = new_capacity;
}