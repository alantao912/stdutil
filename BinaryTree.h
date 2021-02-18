#ifndef UTIL_BINARYTREE_H
#define UTIL_BINARYTREE_H

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

void extend(struct TreeNode* target, signed char (*comparator)(void* cmpl, void* cmpr), void* element);

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

void destroy(struct TreeNode* target);

#endif