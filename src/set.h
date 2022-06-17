#ifndef STDUTIL_SET_H
#define STDUTIL_SET_H

#include <stdbool.h>
#include <stddef.h>

struct SetEntry {
	void *data;
	bool removed;
};

typedef struct set {

	/* Backing array for the elements in the set. */	

	struct SetEntry *data;
	
	/*
		Number of elements within the set
	*/

	size_t cardinality, capacity;

	/*
		Hash function must return the same hash for two keys that are deemed equal by the comparator.

		Example:
		If comparator(key1, key2) == true, then hash_function(key1) == hash_function(key2).
	*/

	size_t (*hash_function)(const void* key);

	/*
		The programmer must implement an equivalence relation as a comparator function. That is, it must be:

		Let a, b, c be elements within set S.

		Reflexive: If comparator(a, b) is true, then comparator(b, a) must also be true.

		Transitive: If comparator(a, b) is true, and comparator(b, c) is true, then comparator(a, c) must also be true.

		Symmetric: comparator(a, a) must be true.
	*/

	bool (*comparator)(const void *l_operand, const void *r_operand);
	
	/*
		Load factor of the set, value between 0 and 1. Resizes the backing array of the set when size / capacity > lf
	*/

	float lf;

} set;

/*
	Initializes an empty set with the specified initial capacity using default hash function and comparator.
*/

struct set *create_Set(size_t initial_capacity);

/*
	Adds an element to the set. If the element was already present in the set, this function will leave the set unchanged and return false.
	If element was not already in the set, adds element to the set and returns true.

	Returns false if specified element is null or OOM exception occurs
*/

bool set_add(struct set *set, void *element);

/*
	Removes an element from the set. If the element is present within the set, removes it and returns a pointer to the data it stored.
	If the element is not present within the set, leaves set unchanged and returns NULL.	

	Returns NULL if specified element is NULL.
*/

void *set_remove(struct set *set, void *element);

/*
	Returns true if the specified element is contained within the set, false otherwise.
*/

bool set_contains(struct set *set, void *element);

/*
	Removes every element within the set.
*/

void set_clear(struct set *set);

/*
	Removes and frees every element from within the set.
*/

void set_delete(struct set *set);

#endif
