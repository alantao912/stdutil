#include <stdlib.h>
#include "BinaryTree.h"

#define TEST
#ifdef TEST
	#include <stdio.h>
#endif

static struct TreeNode* tree_addHelper(struct TreeNode* target, void* element, signed char (*comparator)(void* cmpl, void* cmpr));

static void preorderHelper(struct TreeNode* target, struct ArrayList* list);

static void inorderHelper(struct TreeNode* target, struct ArrayList* list);

static void postorderHelper(struct TreeNode* target, struct ArrayList* list);

void tree_add(struct TreeNode** target, void* element, signed char (*comparator)(void* cmpl, void* cmpr)) {
	*target = tree_addHelper(*target, element, comparator);
}

static struct TreeNode* tree_addHelper(struct TreeNode* target, void* element, signed char (*comparator)(void* cmpl, void* cmpr)) {
	if(!target) {
		struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		node->data = element;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	signed char difference = (*comparator)(element, target->data);
	if(difference > 0)
		target->right = tree_addHelper(target->right, element, comparator);
	else
		target->left = tree_addHelper(target->left, element, comparator);	
	return target;
}

struct ArrayList preorderTree(struct TreeNode* target) {
	struct ArrayList data = create_ArrayList(1);
	preorderHelper(target, &data);	
	return data;
}

static void preorderHelper(struct TreeNode* target, struct ArrayList* list) {
	if(!target)
		return;
	al_append(list, target->data);
	preorderHelper(target->left, list);
	preorderHelper(target->right, list);
}

struct ArrayList inorderTree(struct TreeNode* target) {
	struct ArrayList data = create_ArrayList(1);
	inorderHelper(target, &data);
	return data;
}

static void inorderHelper(struct TreeNode* target, struct ArrayList* list) {
	if(!target)
		return;
	inorderHelper(target->left, list);
	al_append(list, target->data);
	inorderHelper(target->right, list);
}

struct ArrayList postorderTree(struct TreeNode* target) {
	struct ArrayList data = create_ArrayList(1);
	postorderHelper(target, &data);
	return data;
}

static void postorderHelper(struct TreeNode* target, struct ArrayList* list) {
	if(!target)
		return;
	postorderHelper(target->left, list);
	postorderHelper(target->right, list);
	al_append(list, target->data);
}

struct ArrayList levelorderTree(struct TreeNode* target) {
	struct ArrayList data = create_ArrayList(1);
	if(target) {
		struct ArrayList node_queue = create_ArrayList(1);
		al_append(&node_queue, target);
		al_append(&data, target->data);

		char cont;
		int start = 0;

		do {
			int front = al_size(&node_queue);
			cont = 0;
			for(int i = start; i < al_size(&node_queue); ++i) {
				struct TreeNode* iterator = al_get(&node_queue, i);
				if(iterator->left) {
					al_append(&data, iterator->left->data);
					al_append(&node_queue, iterator->left);
					cont = 1;
				}
				if(iterator->right) {
					al_append(&data, iterator->right->data);
					al_append(&node_queue, iterator->right);
					cont = 1;
				}
			}
			start = al_size(&node_queue) - front;
		} while(cont == 1);
	}
	return data;
}

void* searchTree(struct TreeNode* target, signed char (*comparator)(void* cmpl, void* cmpr), void* element) {
	if(!target)
		return NULL;
	
	signed char difference = (*comparator)(element, target->data);
	if(difference == 0)
		return target->data;
	if(difference > 0)
		return searchTree(target->right, comparator, element);
	else
		return searchTree(target->left, comparator, element);
}

void applyTree(struct TreeNode* target, void (*operation)(void* operand)) {
	if(!target)
		return;
	(*operation)(target->data);
	applyTree(target->left, operation);
	applyTree(target->right, operation);
}

void tree_clear(struct TreeNode* target) {
	if(!target)
		return;
	tree_clear(target->left);
	tree_clear(target->right);
	free(target);
}
