#include <stdlib.h>
#include "BinaryTree.h"

void extend(struct TreeNode* target, signed char (*comparator)(void* cmpl, void* cmpr), void* element) {
	if(target->data == NULL)
		target->data = element;
	else if((*comparator)(element, target->data) < 0)
		if(target->left == NULL) {
			target->left = (struct TreeNode*) malloc(sizeof(struct TreeNode));
			target->left->data = element;
			target->left->left = NULL;
			target->left->right = NULL;
		} else
			extend(target->left, comparator, element);
	else
		if(target->right == NULL) {
			target->right = (struct TreeNode*) malloc(sizeof(struct TreeNode));
			target->right->data = element;
			target->right->left = NULL;
			target->right->right = NULL;
		} else
			extend(target->right, comparator, element);
}

void* searchTree(struct TreeNode* target, signed char (*comparator)(void* cmpl, void* cmpr), void* element) {
	signed char comparison = (*comparator)(element, target->data);
	if(comparison == 0)
		return target->data;
	if(comparison < 0)
		if(target->left == NULL)
			return NULL;
		else
			return searchTree(target->left, comparator, element);
	else
		if(target->right == NULL)
			return NULL;
		else
			return searchTree(target->right, comparator, element);
}

void applyTree(struct TreeNode* target, void (*operation)(void* operand)) {
	if(target->left != NULL)
		applyTree(target->left, operation);
	if(target->right != NULL)
		applyTree(target->right, operation);
	(*operation)(target->data);
}

void destroy(struct TreeNode* target) {
	if(target->left != NULL) {
		destroy(target->left);
		free(target->left);
	}
	if(target->right != NULL) {
		destroy(target->right);
		free(target->right);
	}
	free(target->data);
}