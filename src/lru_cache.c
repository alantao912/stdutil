#include "lru_cache.h"

lru_cache *create_cache(size_t capacity) {
    lru_cache *cache = (lru_cache *) malloc(sizeof(lru_cache));
    if (!cache) {
        return NULL;
    }
    cache->dll = create_dlinkedlist();
    if (!cache->dll) {
        free(cache);
        return NULL;
    }

    cache->node_map = create_hashmap(2 * capacity, 0.5f);
    if (!cache->node_map) {
        free(cache->dll);
        free(cache);
        return NULL;
    }
    cache->capacity = capacity;
    return cache;
}

void *cache_put(lru_cache *cache, void *element) {
    dlist_node *node = hm_get(cache->node_map, element);
    if (node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            return NULL;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            cache->dll->tail = node->prev;
        }
        node->next = cache->dll->head;
        node->prev = NULL;
        cache->dll->head->prev = node;
        cache->dll->head = node;
        return NULL;
    } else {
        void *removed_key = NULL;
        if (cache->dll->size + 1 > cache->capacity) {
            removed_key = dll_remove_last(cache->dll);
            hm_remove(cache->node_map, removed_key);
        }
        dll_add_first(cache->dll, element);
        hm_put(cache->node_map, element, cache->dll->head);
        return removed_key;
    }
}

void *cache_get(lru_cache *cache, void *element) {
    dlist_node *node = hm_get(cache->node_map, element);
    if (node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            return NULL;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            cache->dll->tail = node->prev;
        }
        node->next = cache->dll->head;
        node->prev = NULL;
        cache->dll->head->prev = node;
        cache->dll->head = node;
        return node->data;
    }
    return NULL;
}

void *cache_get_lru(lru_cache *cache) {
    return cache->dll->tail->data;
}

void *cache_get_mru(lru_cache *cache) {
    return cache->dll->head->data   ;
}