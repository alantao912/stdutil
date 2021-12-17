#include <stdlib.h>
#include "LinkedList.h"

struct LinkedList array_to_linkedlist(void **array, size_t size) {
	struct LinkedList linked_list = {.head = NULL, .iterator = NULL, .tail = NULL, .size = 0};
	struct ListNode **iterator = &linked_list.head;
	for (size_t i = 0; i < size; ++i) {
		*iterator = (struct ListNode*) malloc(sizeof(struct ListNode));
		linked_list.tail = *iterator;
		(*iterator)->element = array[i];
		iterator = &((*iterator)->next);
	}
	*iterator = NULL;
	linked_list.iterator = linked_list.head;
	linked_list.size = size;
	return linked_list;
}

struct LinkedList create_linkedlist() {
	struct LinkedList ll = {.head = NULL, .iterator = NULL, .tail = NULL, .size = 0};
	return ll;
}

void add_first(struct LinkedList* target, void* element) {
	struct ListNode *node = (struct ListNode*) malloc(sizeof(struct ListNode));
	node->element = element;
	node->next = target->head;
	target->head = node;
	++target->size;
}

void add_last(struct LinkedList* target, void* element) {
	struct ListNode *node = (struct ListNode*) malloc(sizeof(struct ListNode));
	node->element = element;
	node->next = NULL;
	target->tail->next = node;
	target->tail = node;
	++target->size;
}

void ll_addAt(struct LinkedList* target, size_t position, void* element) {
	if (position > target->size) {
		return;
	}

	struct ListNode **iterator = &(target->head);
	for (size_t i = 0; i < position; ++i) {
		iterator = &((*iterator)->next);
	}
	struct ListNode *node = (struct ListNode*) malloc(sizeof(struct ListNode));
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

void* ll_set(struct LinkedList* target, size_t position, void* element) {
	if (position >= target->size) {
		return NULL;
	}
	struct ListNode *iterator = target->head;
	for (size_t i = 0; i < position; ++i) {
		iterator = iterator->next;
	}
	void* old_value = iterator->element;
	iterator->element = element;
	return old_value;
}

size_t ll_size(struct LinkedList* target) {
	return target->size;
}

void* ll_get(struct LinkedList* target, size_t index) {
	if (index >= target->size) {
		return NULL;
	}
	struct ListNode *iterator = target->head;
	for (size_t i = 0; i < index; ++i) {
		iterator = iterator->next;
	}
	return iterator->element;
}

void* next(struct LinkedList* target) {
	void *ret = NULL;
	if (target->iterator) {
		ret = target->iterator->element;
		target->iterator = target->iterator->next;
	} else {
		target->iterator = target->head;
	}

	return ret;
}

bool hasNext(struct LinkedList* target) {
	return !target->iterator || target->iterator->next;
}

void reset(struct LinkedList* target) {
	target->iterator = target->head;
}

void* ll_remove(struct LinkedList* target, size_t position) {
	if (position >= target->size) {
		return NULL;
	}
	
	struct ListNode **iterator = &(target->head), *prev = NULL;
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
	struct ListNode *toRemove = *iterator;
	*iterator = (*iterator)->next;
	free(toRemove);
	--target->size;
	return data;
}

void ll_clear(struct LinkedList* target) {
	struct ListNode *iterator = target->head, *prev = NULL;
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

void join(struct LinkedList* left_list, struct LinkedList* right_list) {	
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

struct LinkedList split(struct LinkedList* target, size_t split) {
	struct LinkedList new = {.head = NULL, .iterator = NULL, .tail = target->tail, .size = 0};
	if (split >= target->size) {
		return new;
	}
	struct ListNode *iterator = target->head, *prev = NULL;
	for (size_t i = 0; i < split; ++i) {
		prev = iterator;
		iterator = iterator->next;
	}
	target->tail = prev;
	if (split == 0) {
		target->head = NULL;
	}
	new.head = iterator;
	new.iterator = new.head;
	new.size = target->size - split;

	target->size -= new.size;
	return new;
}