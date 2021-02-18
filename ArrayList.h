#ifndef UTIL_ARRAYLIST_H
#define UTIL_ARRAYLIST_H

#include <stddef.h>

/*
	The 'ArrayList.h' and 'ArrayList.c' files provide the declarations and implementations of
	a generic, dynamically sized, array.  

*/

struct ArrayList {
	void** elements;
	size_t size, capacity;
};

/*
	Creates an ArrayList with an initial_capacity of [initial_capacity]
*/

struct ArrayList create_ArrayList(size_t initial_capacity);

/*
	Adds an element to the first available space in the ArrayList.

	If there are no empty indices in the ArrayList, the ArrayList will
	be resized to capacity + 1, and the new element will be added.
*/

void add(struct ArrayList* target, void* element);

/*
	Inserts an element to the ArrayList at the specified index. The specified index
	must be less than the ArrayList's size.
*/

void insert(struct ArrayList* target, size_t position, void* element);

/*
	Returns the number of elements in the ArrayList.
*/

size_t size(struct ArrayList* target);

/*
	Returns the available capacity of the ArrayList. If the size is equal to the capacity
	and another element is added to the ArrayList, the ArrayList will resize to capacity + 1
	and accomodate the new element.
*/

size_t capacity(struct ArrayList* target);

/*
	Ensures that the ArrayList must be able to contain [new_capacity] number of elements.
*/

void ensure_capacity(struct ArrayList* target, size_t new_capacity);

/*
	Assigns the element at index [position] to [element]
	calls free() on the existing element.
*/

void set(struct ArrayList* target, size_t position, void* element);

/*
	Returns the element at index [position] of the ArrayList.
*/

void* get(struct ArrayList* target, size_t position);

/*
	Removes the element at index [position] of the ArrayList and returns it.
	It is up to the programmer to call free() the returned pointer.
*/

void* delete(struct ArrayList* target, size_t position);

/*
	Deletes all contents of the ArrayList. Sets the size and capacity of the ArrayList to 0
	and calls free() on all of the elements stored within the ArrayList.
*/

void clear(struct ArrayList* target);

#endif
