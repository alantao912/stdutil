#ifndef UTIL_BINARYTREE_H
#define UTIL_BINARYTREE_H

#include "arraylist.h"

typedef struct treenode {

	/*
		Generic data to data contained in tree node
	*/

	void *data;

	/*
		Left and right respective children of the node.

		A value of 'NULL' represents no child.
	*/

	struct treenode *left, *right;
	
	/*
		Maximum number of tree levels below current node.
	*/

	unsigned char height;

	/*
		Balance factor: Difference of the heights of the left child and right child

		bf = left->height - right->height		
	*/

	signed char bf;
	
	/*
		Number of copies of duplicate values stored in this treenode.
	*/

	unsigned int count;
} treenode;

typedef struct tree {

	/*
		Pointer to the root of the tree.
	*/

	treenode *root;
	
	/*
		Total number of nodes within the tree.
	*/

	size_t size;

	/*
		Compares the data stored in the tree.

		Must return a negative number if loperand < roperand,
			    a positive number if loperand > roperand,
			    zero if loperand = roperand.
	*/

	const signed char (*comparator)(const void *loperand, const void *roperand);
} tree;

/*
	Takes data contained in an array, and constructs a balanced tree.

	Leaves original array and elements of the original array unchanged.
*/

tree *create_tree(void **array, size_t size, const signed char (*comparator)(const void *loperand, const void *roperand));

/*
	Adds a new node containing the specified data to its correct position within the tree, and increments size.

	Maintains that the tree is balanced.
*/

void tree_add(tree *t, void *data);

/*
	Removes and returns the node containing the specified data from the tree, and decrements size.

	Maintains that the tree is balanced.	
*/

void *tree_remove(tree *t, void *data);

/*
	Searches for and returns the data specified from the tree.

	Leaves the tree unchanged.
*/

void *tree_get(tree *t, void *data);

/*
	Frees every node within the tree, sets root to NULL, and sets size to 0.

	Does not free data stored within the tree.
*/

void tree_clear(tree *t);

/*
	Frees every node within the tree, sets root to NULL, and sets size to 0.

	Frees data stored within the tree.
*/

void tree_delete(tree *t);

/*
	Returns an arraylist of data stored in the tree from a preorder traversal.
*/

arraylist *preorder(tree *t);

/*
	Returns an arraylist of data stored in the tree from an inorder traversal.
*/

arraylist *inorder(tree *t);

/*
	Returns an arraylist of data stored in the tree from a postorder traversal.
*/

arraylist *postorder(tree *t);

/*
	Returns an arraylist of data stored in the tree from a levelorder traversal.
*/

arraylist *levelorder(tree *t);

#endif