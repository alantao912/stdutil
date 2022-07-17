#include "linked_list.h"

linked_list *array_to_linkedlist(void **array, size_t size) {
	linked_list *linked_list = create_linkedlist();
	if (!linked_list) {
		return NULL;
	}

	list_node **iterator = &(linked_list->head);
	for (size_t i = 0; i < size; ++i) {
		*iterator = (list_node*) malloc(sizeof(list_node));
		if (!iterator) {
			ll_clear(linked_list);
			free(linked_list);
			return NULL;
		}
		linked_list->tail = *iterator;
		(*iterator)->element = array[i];
		iterator = &((*iterator)->next);
	}
	*iterator = NULL;
	linked_list->iterator = linked_list->head;
	linked_list->size = size;
	return linked_list;
}

linked_list *create_linkedlist() {
	linked_list *ll = (linked_list *) malloc(sizeof(linked_list));
	memset(ll, 0, sizeof(linked_list));
	return ll;
}

void ll_add_first(linked_list *target, void *element) {
	list_node *node = (list_node*) malloc(sizeof(list_node));
	node->element = element;
	node->next = target->head;
	target->head = node;
	++target->size;
}

void ll_add_last(linked_list *target, void *element) {
	list_node *node = (list_node*) malloc(sizeof(list_node));
	node->element = element;
	node->next = NULL;
	target->tail->next = node;
	target->tail = node;
	++target->size;
}

void ll_add_at(linked_list *target, size_t position, void *element) {
	if (position > target->size) {
		return;
	}

	list_node **iterator = &(target->head);
	for (size_t i = 0; i < position; ++i) {
		iterator = &((*iterator)->next);
	}
	list_node *node = (list_node*) malloc(sizeof(list_node));
	node->element = element;
	node->next = *iterator;

	*iterator = node;

	if (position == 0) {
		target->head = node;
	} else if (position == target->size) {
		target->tail = node;
	}
	++target->size;
}

void *ll_set(linked_list *target, size_t position, void *element) {
	if (position >= target->size) {
		return NULL;
	}
	list_node *iterator = target->head;
	for (size_t i = 0; i < position; ++i) {
		iterator = iterator->next;
	}
	void *old_value = iterator->element;
	iterator->element = element;
	return old_value;
}

size_t ll_size(linked_list* target) {
	return target->size;
}

void *ll_get(linked_list *target, size_t index) {
	if (index >= target->size) {
		return NULL;
	}
	list_node *iterator = target->head;
	for (size_t i = 0; i < index; ++i) {
		iterator = iterator->next;
	}
	return iterator->element;
}

void *ll_next(linked_list *target) {
	void *ret = NULL;
	if (target->iterator) {
		ret = target->iterator->element;
		target->iterator = target->iterator->next;
	} else {
		target->iterator = target->head;
	}

	return ret;
}

bool ll_has_next(linked_list *target) {
	return target->iterator != NULL;
}

void ll_reset(linked_list *target) {
	target->iterator = target->head;
}

void *ll_remove(linked_list *target, size_t position) {
	if (position >= target->size) {
		return NULL;
	}

	list_node **iterator = &(target->head), *prev = NULL;
	for (size_t i = 0; i < position; ++i) {
		prev = *iterator;
		iterator = &((*iterator)->next);
	}

	if (position == target->size - 1) {
		target->tail = prev;
	}

	if (*iterator == target->iterator) {
		target->iterator = prev;
	}
	void *data = (*iterator)->element;
	list_node *toRemove = *iterator;
	*iterator = (*iterator)->next;
	free(toRemove);
	--target->size;
	return data;
}

list_node *ll_remove_node(linked_list *target, size_t position) {
	if (position >= target->size) {
		return NULL;
	}

	list_node **iterator = &(target->head), *prev = NULL;
	for (size_t i = 0; i < position; ++i) {
		prev = *iterator;
		iterator = &((*iterator)->next);
	}

	if (position == target->size - 1) {
		target->tail = prev;
	}

	if (*iterator == target->iterator) {
		target->iterator = prev;
	}
	list_node *to_remove = *iterator;
	*iterator = to_remove->next;
	to_remove->next = NULL;
	--target->size;
	return to_remove;
}

void ll_clear(linked_list *target) {
	list_node *iterator = target->head, *prev = NULL;
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

void ll_delete(linked_list *target) {
	list_node *iterator = target->head, *prev = NULL;
	while (iterator) {
		free(iterator->element);
		prev = iterator;
		iterator = iterator->next;
		free(prev);
	}
	target->head = NULL;
	target->tail = NULL;
	target->iterator = NULL;
	target->size = 0;
}

void join(linked_list* left_list, linked_list* right_list) {
	if (left_list->size != 0 && right_list->size != 0) {
		left_list->tail->next = right_list->head;
		left_list->tail = right_list->tail;
		left_list->size += right_list->size;
	} else if (right_list->size != 0) {
		left_list->head = right_list->head;
		left_list->tail = right_list->tail;
		left_list->size = right_list->size;
	}
}

linked_list *split(linked_list* target, size_t split) {
	linked_list *new = create_linkedlist();
	if (split >= target->size) {
		return new;
	}
	list_node *iterator = target->head, *prev = NULL;

	for (size_t i = 0; i < split; ++i) {
		prev = iterator;
		iterator = iterator->next;
	}
	target->tail = prev;
	if (split == 0) {
		target->head = NULL;
	}
	new->head = iterator;
	new->iterator = new->head;
	new->size = target->size - split;
	target->size -= new->size;

	iterator = new->head;
	while (iterator) {
		prev = iterator;
		iterator = iterator->next;
	}
	new->tail = prev;
	return new;
}