#ifndef STDUTIL_LINKED_HASHMAP_H
#define STDUTIL_LINKED_HASHMAP_H

#include <stdbool.h>
#include "arraylist.h"
#include "hashmap.h"
#include "dlinked_list.h"

typedef struct linked_hashmap {
    hashmap *map;
    dlinked_list *list;
} linked_hashmap;

linked_hashmap *create_lhashmap(size_t initial_capacity, float lf);

void *lhm_put(linked_hashmap *lhm, void *key, void *value);

void *lhm_remove(linked_hashmap *lhm, void *key);

void *lhm_get(linked_hashmap *lhm, void *key);

bool lhm_contains_key(linked_hashmap *lhm, void *key);

arraylist *lhm_key_set(linked_hashmap *map);

arraylist *lhm_values(linked_hashmap *map);

void lhm_clear(linked_hashmap *map);

void lhm_delete(linked_hashmap *map);

#endif