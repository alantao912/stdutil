#ifndef UTIL_LINKEDLIST_H
#define UTIL_LINKEDLIST_H

#include <stdbool.h>
#include "ArrayList.h"

struct ListNode {
	void *element;
	struct ListNode *next;
};

struct LinkedList {
	struct ListNode *head, *iterator, *tail;
	size_t size;
};

/*
	Creates a linked list and initializes it to the size specified by
	[initial_size] by creating the necessary list nodes;
*/

struct LinkedList array_to_linkedlist(void **array, size_t size);

/*
	Creates a new list node with the specified data and prepends it to the front of the linked list.
*/

void add_first(struct LinkedList* target, void* element);

/*
	Creates a new list node with the data specified by [element] and appends it
	to the end of the linked list.
*/

void add_last(struct LinkedList* target, void* element);

/*
	Inserts a new list node with the data specified by [element] and inserts it to
	the position in the linked list specified by [position]
*/

void ll_addAt(struct LinkedList* target, size_t position, void* element);

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

void* ll_remove(struct LinkedList* target, size_t position);

/*
	Destroys the entire linked list, while freeing all the data that the linked list stored.
*/

void ll_clear(struct LinkedList* target);

/*
	Attaches the linked list [right_list] to the end of [left_list]

	right_list is NOT freed as a result of this operation
*/

void join(struct LinkedList* left_list, struct LinkedList* right_list);

/*
	Splits the specified linkedlist at the index split (inclusive).

	Returns the split linked list.
*/

struct LinkedList split(struct LinkedList* target, size_t split);

#endif