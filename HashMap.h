#ifndef STDUTIL_HASHMAP_H
#define STDUTIL_HASHMAP_H

#include <stdbool.h>
#include <stddef.h>
#include "ArrayList.h"

struct MapEntry {
	void* key;
	void* value;
	bool removed;
};

struct HashMap {
	struct MapEntry** table;
	size_t capacity;
	size_t size;
	float load_factor;

	/*
		Hash function must return the same hash for two keys that are deemed equal by the comparator.

		Example:
		If comparator(key1, key2) == true, then hash_function(key1) == hash_function(key2).
	*/

	size_t (*hash_function)(void* key);

	/*
		The programmer must implement an equivalence relation as a comparator function. That is, it must be:

		Let a, b, c be elements within set S.

		Reflexive: If comparator(a, b) is true, then comparator(b, a) must also be true.

		Transitive: If comparator(a, b) is true, and comparator(b, c) is true, then comparator(a, c) must also be true.

		Symmetric: comparator(a, a) must be true.
	*/

	bool (*comparator)(void* key0, void* key1);
};

/*
	Creates an empty hashmap with specified initial capacity and loadfactor, using default hash function and comparator.

	It is recommended that the initial capacity be a prime number.

	It is up to the programmer to specify a function that returns a boolean which compares keys.
*/

struct HashMap create_HashMap(size_t initial_capacity, float lf);

/*
	Puts a specified key-value pair into the hashmap, returns the associated value if the key already exists, null otherwise.
*/

void* hm_put(struct HashMap* map, void* key, void* value);

/*
	Removes the MapEntry with specified key, returns the value formerly stored there, null if key does not exist.
*/

void* hm_remove(struct HashMap* map, void* key);

/*
	Returns the value associated with a specified key, NULL if the hashmap does not contain the key.
*/

void* hm_get(struct HashMap* map, void* key);

/*
	Returns true if a specified key is contained in the hashmap, false otherwise.
*/

bool hm_containsKey(struct HashMap* map, void* key);

/*
	Returns an ArrayList of all keys stored in the hashmap
*/

struct ArrayList keySet(struct HashMap* map);

/*
	Returns an ArrayList of all values stored in the HashMap
*/

struct ArrayList values(struct HashMap* map);

/*
	Computes the hash of input "key" using the multiplicative hashing formula: h(K) = floor(aK mod W / (W/M)),
	where a and W are relatively prime and M = UINT_MAX, and a is a large number with random distribution of 0s and 1s. 
	Generates values between [0, M - 1].
*/

size_t default_hash_function(void* key);

/*
	Default comparator function, checks if pointers have the same value.
*/

bool default_comparator(void *key0, void *key1);

#endif