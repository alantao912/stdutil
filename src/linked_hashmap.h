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

/**
 * @brief Returns an arraylist of keys not guaranteed to be in any particular order. 
 */

arraylist *lhm_key_set(linked_hashmap *map);

/**
 * @brief Returns an arraylist with values of the hashmap in the order they were inserted. 
 */

arraylist *lhm_values(linked_hashmap *map);

void lhm_clear(linked_hashmap *map);

void lhm_delete(linked_hashmap *map);

dlist_node *iterator(linked_hashmap *map);

#endif