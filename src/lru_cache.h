#ifndef STDUTIL_LRUCACHE_H
#define STDUTIL_LRUCACHE_H

#include <stdio.h>
#include "hashmap.h"
#include "dlinked_list.h"
typedef struct lru_cache {
    hashmap *node_map;
    dlinked_list *dll;
    size_t capacity;
} lru_cache;

lru_cache *create_cache(size_t capacity);

void *cache_put(lru_cache *cache, void * element);

void *cache_get(lru_cache *cache, void *element);

void *cache_get_lru(lru_cache *cache);

void *cache_get_mru(lru_cache *cache);

#endif