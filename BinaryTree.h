#ifndef UTIL_BINARYTREE_H
#define UTIL_BINARYTREE_H

#include "ArrayList.h"

struct TreeNode {
	void* data;
	struct TreeNode* left;
	struct TreeNode* right;
};

/*
	Places a new tree node in the appropriate position of the tree.
	
	Comparator must return -1 if the element is smaller than the searched for element, 
	0 if the two are equal, and 1 if the element is greater than the searched for element.
	
*/

void tree_add(struct TreeNode** target, void* element, signed char (*comparator)(void* cmpl, void* cmpr));

/*
	Returns the nodes of the tree in an arraylist in preorder.
*/

struct ArrayList preorderTree(struct TreeNode* target);

/*
	Returns the nodes of the tree in an arraylist inorder.
*/

struct ArrayList inorderTree(struct TreeNode* target);

/*
	Returns the nodes of the tree in an arraylist in postorder.
*/

struct ArrayList postorderTree(struct TreeNode* target);

/*
	Returns the nodes of the tree in an arrayist in levelorder.
*/

struct ArrayList levelorderTree(struct TreeNode* target);

/*
	Searches the tree for data containing [element]. Returns a pointer to the found data.

	Comparator must return -1 if the element is smaller than the searched for element, 
	0 if the two are equal, and 1 if the element is greater than the searched for element.
*/

void* searchTree(struct TreeNode* target, signed char (*comparator)(void* cmpl, void* cmpr), void* element);

/*
	Applies a function to every node on the tree
*/

void applyTree(struct TreeNode* target, void (*operation)(void* operand));

/*
	Frees ALL children, grandchildren, great-grandchidlren etc. nodes of the 
	tree node pointed to by [target] as well as the data stored in the freed nodes.
*/

void tree_clear(struct TreeNode* target);

#endif