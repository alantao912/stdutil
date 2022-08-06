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

<<<<<<< HEAD
/**
 * @brief Returns an arraylist of keys not guaranteed to be in any particular order. 
 */

arraylist *lhm_key_set(linked_hashmap *map);

/**
 * @brief Returns an arraylist with values of the hashmap in the order they were inserted. 
 */

=======
arraylist *lhm_key_set(linked_hashmap *map);

>>>>>>> 4697ad243efe13f964b952275e6c694423c00be7
arraylist *lhm_values(linked_hashmap *map);

void lhm_clear(linked_hashmap *map);

void lhm_delete(linked_hashmap *map);

<<<<<<< HEAD
dlist_node *iterator(linked_hashmap *map);

=======
>>>>>>> 4697ad243efe13f964b952275e6c694423c00be7
#endif