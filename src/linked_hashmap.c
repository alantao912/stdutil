#include "linked_hashmap.h"

linked_hashmap *create_lhashmap(size_t initial_capacity, float lf) {
    linked_hashmap *lhm = (linked_hashmap *) malloc(sizeof(linked_hashmap));
    if (!lhm) {
        return NULL;
    }
    lhm->map = create_hashmap(initial_capacity, lf);
    if (!lhm->map) {
        free(lhm);
        return NULL;
    }
    lhm->list = create_dlinkedlist();
    if (!lhm->list) {
        free(lhm->map);
        free(lhm);
        return NULL;
    }
    return lhm;
}

void *lhm_put(linked_hashmap *lhm, void *key, void *value) {
    dlist_node *node = hm_get(lhm->map, key);
    if (node) {
        /* Key already exists in the hashmap */
        void *old_value = node->data;
        node->data = value;
        return old_value;
    }
    dll_add_last(lhm->list, value);
    hm_put(lhm->map, key, lhm->list->tail);
    return NULL;
}

void *lhm_remove(linked_hashmap *lhm, void *key) {
    dlist_node *node = hm_remove(lhm->map, key);

    void *data = NULL;
    if (node) {
        data = node->data;
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            lhm->list->head = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            lhm->list->tail = node->prev;
        }
        --lhm->list->size;
        data = node->data;
        free(node);
    }
    return data;
}

void *lhm_get(linked_hashmap *lhm, void *key) {
    dlist_node *node = hm_get(lhm->map, key);
    if (node) {
        return node->data;
    }
    return NULL;

}

bool lhm_contains_key(linked_hashmap *lhm, void *key) {
    return hm_get(lhm->map, key) != NULL;
}

arraylist *lhm_key_set(linked_hashmap *map) {
    return hm_key_set(map->map);
}

arraylist *lhm_values(linked_hashmap *map) {
    arraylist *ret = (arraylist *) malloc(sizeof(arraylist));
    if (!ret) {
        return NULL;
    }

    void **data = (void **) malloc(sizeof(void *) * map->list->size);
    if (!data) {
        free(ret);
        return NULL;
    }
    ret->elements = data;
    ret->capacity = map->list->size;
    ret->size = map->list->size;

    dlist_node *iterator = map->list->head;
    size_t i = 0;
    while (iterator) {
        data[i] = iterator->data;
        iterator = iterator->next;
        ++i;
    }
    return ret;
}

void lhm_clear(linked_hashmap *map) {
    hm_clear(map->map);
    dll_clear(map->list);
}

void lhm_delete(linked_hashmap *map) {
    hm_delete(map->map);
    dll_delete(map->list);
}

dlist_node *iterator(linked_hashmap *map) {
    return map->list->iterator;
}