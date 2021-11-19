#include "HashMap.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

void* put(struct HashMap* map, void* key, void* value) {
	size_t i = 0, j = 0, removedIndex;
	bool foundRemoved = false;
	while (i < map->capacity && j < map->size) {
		size_t index = (map->hash_function(key) + i) % map->capacity;
		if (!map->table[index]) {
			if (foundRemoved) {
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
			if (foundRemoved || !map->table[index]->removed) {
				void* value = map->table[index]->value;
				map->table[index]->value = value;
				free(map->table[index]->key);
				map->table[index]->key = key;
				return value;
			} else {
				map->table[index]->key = key;
				map->table[index]->value = value;
				map->table[index]->removed = false;
				++map->size;
				return NULL;
			}
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

void* remove(struct HashMap* map, void* key) {
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

void* get(struct HashMap* map, void* key) {
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