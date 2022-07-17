#include "dlinked_list.h"

dlinked_list *array_to_dlinkedlist(void **array, size_t size) {
    dlinked_list *dll = (dlinked_list *) malloc(sizeof(dlinked_list));
    if (!dll) {
        return NULL;
    }
    dll->head = NULL;
    dll->iterator = NULL;

    dlist_node **iterator = &(dll->head), *prev = NULL;
    for (size_t i = 0; i < size; ++i) {
        dlist_node *node = (dlist_node *) malloc(sizeof(dlist_node));
        if (!node) {
            dll_clear(dll);
            free(dll);
            return NULL;
        }
        node->data = array[i];
        *iterator = node;
        node->prev = prev;

        iterator = &((*iterator)->next);
        prev = node;
    }
    *iterator = NULL;
    dll->tail = prev;
    dll->iterator = dll->head;
    dll->size = size;
    return dll;
}

dlinked_list *create_dlinkedlist() {
    dlinked_list *dll = (dlinked_list *) malloc(sizeof(dlinked_list));
    if (!dll) {
        return NULL;
    }
    dll->size = 0;
    dll->head = NULL;
    dll->tail = NULL;
    dll->iterator = NULL;
    return dll;
}

bool dll_add_first(dlinked_list *target, void* element) {
    dlist_node *node = (dlist_node *) malloc(sizeof(dlist_node));
    if (!node) {
        return false;
    }
    node->data = element;
    node->prev = NULL;
    node->next = target->head;

    if (target->head) {
        target->head->prev = node;
        target->head = node;
    } else {
        target->head = node;
        target->tail = node;
    }
    ++target->size;
    return true;
}

bool dll_add_last(dlinked_list *target, void* element) {
    dlist_node *node = (dlist_node *) malloc(sizeof(dlist_node));
    if (!node) {
        return false;
    }
    node->data = element;
    node->next = NULL;
    node->prev = target->tail;

    if (target->tail) {
        target->tail->next = node;
        target->tail = node;
    } else {
        target->head = node;
        target->tail = node;
    }
    ++target->size;
    return true;
}

bool dll_addAt(dlinked_list *target, size_t position, void *element) {

}

void* dll_set(dlinked_list *target, size_t position, void *element) {

}

size_t dll_size(dlinked_list *target) {

}

void* dll_get(dlinked_list *target, size_t index) {

}

void* next(dlinked_list *target) {

}

bool hasNext(dlinked_list *target) {

}

void reset(dlinked_list *target) {

}

void* dll_remove(dlinked_list *target, size_t position) {

}

dlist_node *dll_remove_node(dlinked_list *target, size_t position) {

}

void dll_clear(dlinked_list *target) {

}

void dll_delete(dlinked_list *target) {

}