#ifndef UTIL_ARRAYLIST_H
#define UTIL_ARRAYLIST_H

#include <stddef.h>
#include <stdbool.h>

/*
	The 'ArrayList.h' and 'ArrayList.c' files provide the declarations and implementations of
	a generic, dynamically sized, array.  

*/

struct ArrayList {
	void **elements;
	size_t size, capacity;
};

/*
	Creates an ArrayList with an initial_capacity of [initial_capacity]
*/

struct ArrayList create_ArrayList(size_t initial_capacity);

/*
	Adds an element to the end of the arraylist.

	If the arraylist is at capacity, it will
	be resized to 2 * capacity, and the new element will be added.
*/

bool al_append(struct ArrayList *target, void *element);

/*
	Inserts an element to the ArrayList at the specified index. The specified index
	must be less than the ArrayList's size.
*/

bool al_addAt(struct ArrayList *target, size_t position, void *element);

/*
	Returns the number of elements in the ArrayList.
*/

size_t al_size(struct ArrayList *target);

/*
	Returns the available capacity of the ArrayList. If the size is equal to the capacity
	and another element is added to the ArrayList, the ArrayList will resize to capacity + 1
	and accomodate the new element.
*/

size_t al_capacity(struct ArrayList *target);

/*
	Ensures that the ArrayList must be able to contain [new_capacity] number of elements.
*/

bool al_ensure_capacity(struct ArrayList *target, size_t new_capacity);

/*
	Assigns the element at index [position] to [element]
	calls free() on the existing element.

	Returns the data previously stored there
*/

void* al_set(struct ArrayList* target, size_t position, void* element);

/*
	Returns the element at index [position] of the ArrayList.
*/

void* al_get(struct ArrayList *target, size_t position);

/*
	Removes the element at index [position] of the ArrayList and returns it.
	It is up to the programmer to call free() the returned pointer.
*/

void* al_remove(struct ArrayList *target, size_t position);

/*
	Sorts the ArrayList using the quick sort algorithm. The programmer must provide a function for comparing two generic elements.

	The comparator function must return a negative number if cmpl < cmpr,
	a positive number if cmpl > cmpr,
	and 0 if cmpl == cmpr
*/

void sort(struct ArrayList *target, int (*comparator)(const void *cmpl, const void *cmpr));

/*
	Deletes all contents of the ArrayList. Sets the size of the ArrayList to 0
	and calls free() on all of the elements stored within the ArrayList.
*/

void al_delete(struct ArrayList *target);

/*
	Removes all contents of the ArrayList, sets the size and capacity of the ArrayList to 0
	and sets all of the indices to null.
*/

void al_clear(struct ArrayList *target);

#endif
