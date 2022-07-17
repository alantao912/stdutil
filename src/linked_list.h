#ifndef UTIL_LINKEDLIST_H
#define UTIL_LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
	void *element;
	struct list_node *next;
} list_node;

typedef struct linked_list {
	list_node *head, *iterator, *tail;
	size_t size;
} linked_list;

/*
	Creates a linked list and initializes it to the size specified by
	[initial_size] by creating the necessary list nodes;
*/

linked_list *array_to_linkedlist(void **array, size_t size);

/*
	Creates and initializes an empty linked list
*/

linked_list *create_linkedlist();

/*
	Creates a new list node with the specified data and prepends it to the front of the linked list.
*/

void ll_add_first(linked_list *target, void* element);

/*
	Creates a new list node with the data specified by [element] and appends it
	to the end of the linked list.
*/

void ll_add_last(linked_list *target, void* element);

/*
	Inserts a new list node with the data specified by [element] and inserts it to
	the position in the linked list specified by [position]
*/

void ll_add_at(linked_list *target, size_t position, void* element);

/*
	Overwrites the data in the list node specified by [position] with the new
	data [element]
*/

void* ll_set(linked_list *target, size_t position, void* element);

/*
	Returns the number of nodes in the linked list
*/

size_t ll_size(linked_list *target);

/*
	Returns a pointer to the data stored in the list node specified by [index]
*/

void* ll_get(linked_list *target, size_t index);

/*
	Returns the data stored in the list node that the iterator was originally pointing at
	then moves the iterator to the next node in the linked list.

	Once the iterator reaches the end of the list, it will return NULL and reset itself to the
	head of the linked list.
*/

void* next(linked_list *target);

/*
	Returns true if the iterator is not pointing to the last element of the linked list
*/

bool hasNext(linked_list *target);

/*
	Resets the iterator to the head of the linked list.
*/

void reset(linked_list *target);

/*
	Frees the list node specified by [position] and returns the data stored by that list node.
*/

void* ll_remove(linked_list *target, size_t position);

/*
	Removes and returns the list node.
*/

list_node *ll_remove_node(linked_list *target, size_t position);

/*
	Frees every node within the linkedlist. Sets head, tail, and iterator to null. Sets size to 0.

	Leaves data within the linkedlist unchanged.
*/

void ll_clear(linked_list *target);

/*
	Frees every node within the linkedlist. Sets head, tail, and iterator to null. Sets size to 0.

	Frees data within the linkedlist.
*/

void ll_delete(linked_list *target);

/*
	Attaches the linked list [right_list] to the end of [left_list]

	right_list is NOT freed as a result of this operation
*/

void join(linked_list *left_list, linked_list *right_list);

/*
	Splits the specified linkedlist at the index split (inclusive).

	Returns the split linked list.
*/

linked_list *split(linked_list *target, size_t split);

#endif