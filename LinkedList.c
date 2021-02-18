#include <stdlib.h>
#include "LinkedList.h"

struct LinkedList create_LinkedList(size_t initial_size) {
	struct LinkedList list = {.head = NULL, .iterator = NULL, .size = initial_size};
	struct ListNode** tail_ptr = &list.head;
	for(size_t i = 0; i < initial_size; i++) {
		*tail_ptr = (struct ListNode*) malloc(sizeof(struct ListNode));
		(*tail_ptr)->element = NULL;
		tail_ptr = &((*tail_ptr)->next);
	}
	*tail_ptr = NULL;
	list.iterator = list.head;
	return list;
}

void append(struct LinkedList* target, void* element) {
	struct ListNode** iterator = &(target->head);
	while(*iterator != NULL) {
		iterator = &((*iterator)->next);
	}
	*iterator = (struct ListNode*) malloc(sizeof(struct ListNode));
	(*iterator)->element = element;
	(*iterator)->next = NULL;
	target->size++;
}

void place(struct LinkedList* target, size_t position, void* element) {
	if(position < target->size) {
		struct ListNode** iterator = &(target->head);
		for(size_t i = 0; i < position; i++)
			iterator = &((*iterator)->next);
		struct ListNode* new_next = *iterator;
		*iterator = (struct ListNode*) malloc(sizeof(struct ListNode));
		(*iterator)->next = new_next;
		(*iterator)->element = element;
		target->size++;
	}
}

void assign(struct LinkedList* target, size_t position, void* element) {
	if(position < target->size) {
		struct ListNode* iterator = target->head;
		for(size_t i = 0; i < position; i++)
			iterator = iterator->next;
		free(iterator->element);
		iterator->element = element;
	}
}

size_t length(struct LinkedList* target) {
	return target->size;
}

void* fetch_data(struct LinkedList* target, size_t index) {
	if(index < target->size) {
		struct ListNode* iterator = target->head;
		for(size_t i = 0; i < index; i++)
			iterator = iterator->next;
		return iterator->element;
	}
}

void* next(struct LinkedList* target) {
	if(target->iterator == NULL) {
		target->iterator = target->head;
		return NULL;
	} else {
		void* element = target->iterator->element;
		target->iterator = target->iterator->next;
		return element;
	}
}

void reset(struct LinkedList* target) {
	target->iterator = target->head;
}

void* detach(struct LinkedList* target, size_t position) {
	if(position < target->size) {
		struct ListNode** iterator = &(target->head);
		for(size_t i = 0; i < position; i++) {
			iterator = &((*iterator)->next);
		}
		struct ListNode* new_next = (*iterator)->next;
		void* ret = (*iterator)->element;
		*iterator = new_next;
		target->size--;
		return ret;
	}
}

void clean(struct LinkedList* target) {
	struct ListNode* iterator = target->head;
	while(iterator != NULL) {
		struct ListNode* tmp = iterator->next;
		free(iterator);
		iterator = tmp;
	}
}

void chain(struct LinkedList* left_chain, struct LinkedList* right_chain) {
	struct ListNode** iterator = &(left_chain->head);
	while((*iterator) != NULL)
		iterator = &((*iterator)->next);
	*iterator = right_chain->head;
	left_chain->size += right_chain->size;
}

struct LinkedList unchain(struct LinkedList* target, size_t split) {
	struct LinkedList ret = {.head = NULL, .iterator = NULL, .size = 0};
	if(split < target->size) {
		struct ListNode** iterator = &(target->head);
		for(size_t i = 0; i < split; i++)
			iterator = &((*iterator)->next);
		ret.head = *iterator;
		ret.iterator = ret.head;
		*iterator = NULL;
		ret.size = target->size - split;
		target->size = split + 1;
		return ret;
	}
	return ret;
}