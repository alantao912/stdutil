#ifndef STDUTIL_DLINKEDLIST_H
#define STDUTIL_DLINKEDLIST_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct dlist_node {
    struct dlist_node *next, *prev;
    void *data;
} dlist_node;

typedef struct dlinked_list {
    struct dlist_node *head, *tail, *iterator;
    size_t size;
} dlinked_list;

dlinked_list *array_to_dlinkedlist(void **array, size_t size);

dlinked_list *create_dlinkedlist();

bool dll_add_first(dlinked_list *target, void* element);

bool dll_add_last(dlinked_list *target, void* element);

bool dll_add_at(dlinked_list *target, size_t position, void *element);

void* dll_set(dlinked_list *target, size_t position, void *element);

size_t dll_size(dlinked_list *target);

void* dll_get(dlinked_list *target, size_t index);

void* next(dlinked_list *target);

bool hasNext(dlinked_list *target);

void reset(dlinked_list *target);

void* dll_remove(dlinked_list *target, size_t position);

dlist_node *dll_remove_node(dlinked_list *target, size_t position);

void dll_clear(dlinked_list *target);

void dll_delete(dlinked_list *target);

#endif