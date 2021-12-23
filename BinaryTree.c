#include <stdlib.h>
#include "BinaryTree.h"
#include "Queue.h"

static void update(struct TreeNode *node) {
	int leftHeight = -1;
	
	if (node->left) {
		leftHeight = node->left->height;
	}

	int rightHeight = -1;

	if (node->right) {
		rightHeight = node->right->height;
	}

	node->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	node->bf = (signed char) (leftHeight - rightHeight);
}

static struct TreeNode* leftRotation(struct TreeNode *node) {
	struct TreeNode *b = node->right;
	node->right = b->left;
	b->left = node;
	update(node);
	update(b);
	return b;
}

static struct TreeNode* rightRotation(struct TreeNode *node) {
	struct TreeNode *b = node->left;
	node->left = b->right;
	b->right = node;
	update(node);
	update(b);
	return b;
}

static struct TreeNode* leftRightRotation(struct TreeNode *node) {
	node->left = leftRotation(node->left);
	return rightRotation(node);
}

static struct TreeNode* rightLeftRotation(struct TreeNode *node) {
	node->right = rightRotation(node->right);
	return leftRotation(node);
}

static struct TreeNode* findSuccessor(struct TreeNode *node) {
	struct TreeNode *iterator = node->right;
	while (iterator->left) {
		iterator = iterator->left;
	}
	return iterator;
}

static struct TreeNode* addHelper(struct TreeNode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
	if (!node) {
		struct TreeNode *child = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		child->left = NULL;
		child->right = NULL;
		child->data = data;
		child->height = 0;
		child->bf = 0;
		child->count = 1;
		return child;
	}
	
	signed char difference = comparator(data, node->data);
	if (difference < 0) {
		node->left = addHelper(node->left, data, comparator);
	} else if (difference > 0) {
		node->right = addHelper(node->right, data, comparator);
	} else {
		++node->count;
	}
	update(node);
	if (node->bf > 1) {
		if (node->left->bf < 0) {
			node = leftRightRotation(node);
		} else {
			node = rightRotation(node);
		}
	} else if (node->bf < -1) {
		if (node->right->bf > 0) {
			node = rightLeftRotation(node);
		} else {
			node = leftRotation(node);
		}
	}
	return node;
}

static struct TreeNode* removeHelper(struct TreeNode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
	if (!node) {
		return NULL;
	}
	signed char difference = comparator(data, node->data);
	if (difference < 0) {
		node->right = removeHelper(node->right, data, comparator);
	} else if (difference > 0) {
		node->left = removeHelper(node->left, data, comparator);
	} else if (node->count > 1) {
		--node->count;
	} else if (!node->left && !node->right) {
		return NULL;
	} else if (!node->left) {
		return node->right;
	} else if (!node->right) {
		return node->right;
	} else {
		struct TreeNode *successor = findSuccessor(node);
		node->data = successor->data;
		node->count = successor->count;
		successor->count = 1;
		node->right = removeHelper(node->right, successor->data, comparator);
	}
	update(node);
	if (node->bf > 1) {
		if (node->left->bf < 0) {
			node = leftRightRotation(node);
		} else {
			node = rightRotation(node);
		}
	} else if (node->bf < -1) {
		if (node->right->bf > 0) {
			node = rightLeftRotation(node);
		} else {
			node = leftRotation(node);
		}
	}
	return node;
}

static void* getHelper(struct TreeNode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
	if (!node) {
		return NULL;
	}
	
	signed char difference = comparator(data, node->data);
	if (difference < 0) {
		return getHelper(node->left, data, comparator);
	} else if (difference > 0) {
		return getHelper(node->right, data, comparator);
	} else {	
		return node->data;
	}
}

struct Tree create_tree(void **array, size_t size, signed char (*comparator)(const void *loperand, const void *roperand)) {
	struct Tree tree = {.root = NULL, .size = 0, .comparator = comparator};
	
	for (size_t i = 0; i < size; ++i) {
		tree_add(&tree, array[i]);
	}

	return tree;
}

void tree_add(struct Tree *tree, void *data) {
	if (!data) {
		return;
	}
	tree->root = addHelper(tree->root, data, tree->comparator);
	++tree->size;
}

void* tree_remove(struct Tree *tree, void *data) {
	if (!data) {
		return NULL;
	}
	
	void *found = getHelper(tree->root, data, tree->comparator);
	if (!found) {
		return NULL;
	}

	tree->root = removeHelper(tree->root, data, tree->comparator);
	--tree->size;
	return found;
}

void* tree_get(struct Tree *tree, void *data) {
	if (!data) {
		return NULL;
	}
	return getHelper(tree->root, data, tree->comparator);
}

static void tree_clear_helper(struct TreeNode *node) {
	if (!node) {
		return;
	}
	
	tree_clear_helper(node->left);
	tree_clear_helper(node->right);
	free(node);
}

void tree_clear(struct Tree *tree) {
	tree_clear_helper(tree->root);
	tree->root = NULL;
	tree->size = 0;	
}

static void tree_delete_helper(struct TreeNode *node) {
	if (!node) {
		return;
	}
	
	tree_delete_helper(node->left);
	tree_delete_helper(node->right);
	free(node->data);
	free(node);
}

void tree_delete(struct Tree *tree) {
	tree_delete_helper(tree->root);
	tree->root = NULL;
	tree->size = 0;	
}

static void preorderHelper(struct TreeNode *node, struct ArrayList *collection) {
	if (!node) {
		return;
	}
	al_append(collection, node->data);
	preorderHelper(node->left, collection);
	preorderHelper(node->right, collection);
}

struct ArrayList preorder(struct Tree tree) {
	struct ArrayList collection = create_ArrayList(tree.size);
	preorderHelper(tree.root, &collection);
	return collection;
}

static void inorderHelper(struct TreeNode *node, struct ArrayList *collection) {
	if (!node) {
		return;
	}
	inorderHelper(node->left, collection);
	al_append(collection, node->data);
	inorderHelper(node->right, collection);
}

struct ArrayList inorder(struct Tree tree) {
	struct ArrayList collection = create_ArrayList(tree.size);
	inorderHelper(tree.root, &collection);
	return collection;
}

static void postorderHelper(struct TreeNode *node, struct ArrayList *collection) {
	if (!node) {
		return;
	}
	postorderHelper(node->left, collection);
	postorderHelper(node->right, collection);
	al_append(collection, node->data);
}

struct ArrayList postorder(struct Tree tree) {
	struct ArrayList collection = create_ArrayList(tree.size);
	postorderHelper(tree.root, &collection);
	return collection;
}

struct ArrayList levelorder(struct Tree tree) {
	struct Queue node_queue = create_Queue(8);
	struct ArrayList data = create_ArrayList(tree.size);

	enqueue(&node_queue, tree.root);
	
	while (node_queue.size > 0) {
		struct TreeNode *current = (struct TreeNode*) dequeue(&node_queue);
		al_append(&data, current->data);
		
		if (current->left) {
			enqueue(&node_queue, current->left);
		}

		if (current->right) {
			enqueue(&node_queue, current->right);			
		}
	}
	return data;
}