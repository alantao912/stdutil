#ifndef UTIL_LINKEDLIST_H
#define UTIL_LINKEDLIST_H

#include <stdbool.h>
#include "ArrayList.h"

struct ListNode {
	void* element;
	struct ListNode* next;
};

struct LinkedList {
	struct ListNode* head, *iterator;
	size_t size;
};

/*
	Creates a linked list and initializes it to the size specified by
	[initial_size] by creating the necessary list nodes;
*/

struct LinkedList create_LinkedList(struct ArrayList* array);

/*
	Creates a new list node with the data specified by [element] and appends it
	to the end of the linked list.
*/

void ll_append(struct LinkedList* target, void* element);

/*
	Inserts a new list node with the data specified by [element] and inserts it to
	the position in the linked list specified by [position]
*/

bool ll_addAt(struct LinkedList* target, size_t position, void* element);

/*
	Overwrites the data in the list node specified by [position] with the new
	data [element]
*/

void* ll_set(struct LinkedList* target, size_t position, void* element);

/*
	Returns the number of nodes in the linked list
*/

size_t ll_size(struct LinkedList* target);

/*
	Returns a pointer to the data stored in the list node specified by [index]
*/

void* ll_get(struct LinkedList* target, size_t index);

/*
	Returns the data stored in the list node that the iterator was originally pointing at
	then moves the iterator to the next node in the linked list.

	Once the iterator reaches the end of the list, it will return NULL and reset itself to the 
	head of the linked list.
*/

void* next(struct LinkedList* target);

/*
	Returns true if the iterator is not pointing to the last element of the linked list
*/

bool hasNext(struct LinkedList* target);

/*
	Resets the iterator to the head of the linked list.
*/

void reset(struct LinkedList* target);

/*
	Deletes the list node specified by [position] and returns the data stored by that list node.
*/

void* ll_delete(struct LinkedList* target, size_t position);

/*
	Destroys the entire linked list, while freeing all the data that the linked list stored.
*/

void ll_clear(struct LinkedList* target);

/*
	Attaches the linked list [right_chain] to the end of the linked list [left_chain]
*/

void chain(struct LinkedList* left_chain, struct LinkedList* right_chain);

/*
	Splits the linked list [target] into two linked lists at the index [split]
	returns the newly disconnected linked list. The listnode at the index [split]
	will be a part of the new linked list.
*/

struct LinkedList unchain(struct LinkedList* target, size_t split);

#endif