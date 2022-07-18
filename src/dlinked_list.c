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

bool dll_add_at(dlinked_list *target, size_t position, void *element) {
    if (position < 0 || position > target->size) {
        return false;
    }

    dlist_node *node = (dlist_node *) malloc(sizeof(dlist_node));
    if (!node) {
        return false;
    }
    node->data = element;

    dlist_node **iterator, *prev = NULL;
    if (position <= target->size / 2) {
        iterator = &(target->head);
        for (size_t i = 0; i < position; ++i) {
            prev = *iterator;
            iterator = &((*iterator)->next);
        }
        node->prev = prev;
        node->next = (*iterator);
        if (!target->tail) {
            target->tail = node;
        } else {
            (*iterator)->prev = node;
        }
    } else {
        iterator = &(target->tail);
        for (size_t i = target->size; i > position; --i) {
            prev = *iterator;
            iterator = &((*iterator)->prev);
        }
        node->next = prev;
        node->prev = (*iterator);
        (*iterator)->next = node;
    }
    *iterator = node;
    ++target->size;
    return true;
}

void *dll_set(dlinked_list *target, size_t position, void *element) {
    if (position < 0 || position >= target->size) {
        return NULL;
    }

    dlist_node *iterator;
    if (position <= target->size / 2) {
        iterator = target->head;
        for (size_t i = 0; i < position; ++i) {
            iterator = iterator->next;
        }
    } else {
        iterator = target->tail;
        for (size_t i = target->size - 1; i > position; --i) {
            iterator = iterator->prev;
        }
    }
    void *prev_data = iterator->data;
    iterator->data = element;
    return prev_data;
}

void *dll_get(dlinked_list *target, size_t position) {
    if (position < 0 || position >= target->size) {
        return NULL;
    }

    dlist_node *iterator;
    if (position <= target->size / 2) {
        iterator = target->head;
        for (size_t i = 0; i < position; ++i) {
            iterator = iterator->next;
        }
    } else {
        iterator = target->tail;
        for (size_t i = target->size - 1; i > position; --i) {
            iterator = iterator->prev;
        }
    }
    return iterator->data;
}

void *dll_next(dlinked_list *target) {
    void *ret = NULL;
    if (target->iterator) {
        ret = target->iterator->data;
        target->iterator = target->iterator->next;
    } else {
        target->iterator = target->head;
    }
    return ret;
}

bool dll_has_next(dlinked_list *target) {
    return target->iterator != NULL;
}

void dll_reset(dlinked_list *target) {
    target->iterator = target->head;
}

void *dll_remove(dlinked_list *target, size_t position) {
    dlist_node *removed_node = dll_remove_node(target, position);
    void *removed_data = removed_node->data;
    free(removed_node);
    return removed_data;
}

void *dll_remove_first(dlinked_list *target) {
    if (target->size == 0) {
        return NULL;
    }
    dlist_node *to_remove = target->head;
    target->head = target->head->next;
    if (!target->head) {
        target->tail = NULL;
    } else {
        target->head->prev = NULL;
    }
    void *removed_data = to_remove->data;
    free(to_remove);
    --target->size;
    return removed_data;
}

void *dll_remove_last(dlinked_list *target) {
    if (target->size == 0) {
        return NULL;
    }
    dlist_node *to_remove = target->tail;
    target->tail = target->tail->prev;
    if (!target->tail) {
        target->head = NULL;
    } else {
        target->tail->next = NULL;
    }
    void *removed_data = to_remove->data;
    free(to_remove);
    --target->size;
    return removed_data;
}

dlist_node *dll_remove_node(dlinked_list *target, size_t position) {
    if (position < 0 || position >= target->size) {
        return NULL;
    }

    dlist_node **iterator, *to_remove, *prev = NULL;
    if (position <= target->size / 2) {
        iterator = &(target->head);
        for (size_t i = 0; i < position; ++i) {
            prev = *iterator;
            iterator = &((*iterator)->next);
        }
        to_remove = *iterator;
        *iterator = to_remove->next;
        if (*iterator) {
            (*iterator)->prev = prev;
        } else {
            target->tail = prev;
        }
    } else {
        iterator = &(target->tail);
        for (size_t i = target->size; i > position + 1; --i) {
            prev = *iterator;
            iterator = &((*iterator)->prev);
        }
        to_remove = *iterator;
        *iterator = to_remove->prev;
        (*iterator)->next = prev;
    }
    --target->size;
    return to_remove;
}

void dll_clear(dlinked_list *target) {
    dlist_node *iterator = target->head, *prev = NULL;
    while (iterator) {
        prev = iterator;
        iterator = iterator->next;
        free(prev);
    }
    target->head = NULL;
    target->tail = NULL;
    target->iterator = NULL;
    target->size = 0;
}

void dll_delete(dlinked_list *target) {
    dlist_node *iterator = target->head, *prev = NULL;
    while (iterator) {
        prev = iterator;
        iterator = iterator->next;
        free(prev->data);
        free(prev);
    }
    target->head = NULL;
    target->tail = NULL;
    target->iterator = NULL;
    target->size = 0;
}