#ifndef STDUTIL_HASHMAP_H
#define STDUTIL_HASHMAP_H

#include <stdbool.h>
#include <stddef.h>

struct MapEntry {
	void* key;
	void* value;
	bool removed;
};

struct HashMap {
	struct MapEntry** table;
	size_t capacity;
	size_t size;
	const float load_factor;

	size_t (*hash_function)(void* key);

	bool (*comparator)(void* key0, void* key1);
};

void* put(struct HashMap* map, void* key, void* value);

void* remove(struct HashMap* map, void* key);

void* get(struct HashMap* map, void* key);

#endif