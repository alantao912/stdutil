#include <stdlib.h>
#include "avl_tree.h"
#include "Queue.h"

static void update(treenode *node) {
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

static treenode *leftRotation(treenode *node) {
	treenode *b = node->right;
	node->right = b->left;
	b->left = node;
	update(node);
	update(b);
	return b;
}

static treenode *rightRotation(treenode *node) {
	treenode *b = node->left;
	node->left = b->right;
	b->right = node;
	update(node);
	update(b);
	return b;
}

static treenode *leftRightRotation(treenode *node) {
	node->left = leftRotation(node->left);
	return rightRotation(node);
}

static treenode *rightLeftRotation(treenode *node) {
	node->right = rightRotation(node->right);
	return leftRotation(node);
}

static treenode *findSuccessor(treenode *node) {
	treenode *iterator = node->right;
	while (iterator->left) {
		iterator = iterator->left;
	}
	return iterator;
}

static treenode *addHelper(treenode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
	if (!node) {
		treenode *child = (treenode*) malloc(sizeof(treenode));
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

static treenode *removeHelper(treenode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
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
		treenode *successor = findSuccessor(node);
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

static void *getHelper(treenode *node, void *data, signed char (*comparator)(const void *loperand, const void *roperand)) {
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

struct tree *create_tree(void **array, size_t size, const signed char (*comparator)(const void *loperand, const void *roperand)) {
	struct tree *tree = (struct tree *) malloc(sizeof(struct tree)); 
	tree->root = NULL;
	tree->size = 0;
	tree->comparator = comparator;
	
	for (size_t i = 0; i < size; ++i) {
		tree_add(tree, array[i]);
	}

	return tree;
}

void tree_add(struct tree *tree, void *data) {
	if (!data) {
		return;
	}
	tree->root = addHelper(tree->root, data, tree->comparator);
	++tree->size;
}

void *tree_remove(struct tree *tree, void *data) {
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

void *tree_get(struct tree *tree, void *data) {
	if (!data) {
		return NULL;
	}
	return getHelper(tree->root, data, tree->comparator);
}

static void tree_clear_helper(treenode *node) {
	if (!node) {
		return;
	}
	
	tree_clear_helper(node->left);
	tree_clear_helper(node->right);
	free(node);
}

void tree_clear(struct tree *tree) {
	tree_clear_helper(tree->root);
	tree->root = NULL;
	tree->size = 0;	
}

static void tree_delete_helper(treenode *node) {
	if (!node) {
		return;
	}
	
	tree_delete_helper(node->left);
	tree_delete_helper(node->right);
	free(node->data);
	free(node);
}

void tree_delete(struct tree *tree) {
	tree_delete_helper(tree->root);
	tree->root = NULL;
	tree->size = 0;	
}

static void preorderHelper(treenode *node, arraylist *collection) {
	if (!node) {
		return;
	}
	al_add(collection, node->data);
	preorderHelper(node->left, collection);
	preorderHelper(node->right, collection);
}

arraylist *preorder(struct tree *tree) {
	arraylist *collection = create_arraylist(tree->size);
	preorderHelper(tree->root, collection);
	return collection;
}

static void inorderHelper(treenode *node, arraylist *collection) {
	if (!node) {
		return;
	}
	inorderHelper(node->left, collection);
	al_add(collection, node->data);
	inorderHelper(node->right, collection);
}

arraylist *inorder(struct tree *tree) {
	arraylist *collection = create_arraylist(tree->size);
	inorderHelper(tree->root, collection);
	return collection;
}

static void postorderHelper(treenode *node, arraylist *collection) {
	if (!node) {
		return;
	}
	postorderHelper(node->left, collection);
	postorderHelper(node->right, collection);
	al_add(collection, node->data);
}

arraylist *postorder(struct tree *tree) {
	arraylist *collection = create_arraylist(tree->size);
	postorderHelper(tree->root, collection);
	return collection;
}

arraylist *levelorder(struct tree *tree) {
	struct Queue node_queue = create_Queue(8);
	arraylist *data = create_arraylist(tree->size);

	enqueue(&node_queue, tree->root);
	
	while (node_queue.size > 0) {
		treenode *current = (treenode*) dequeue(&node_queue);
		al_add(data, current->data);
		
		if (current->left) {
			enqueue(&node_queue, current->left);
		}

		if (current->right) {
			enqueue(&node_queue, current->right);			
		}
	}
	free(node_queue.data);
	return data;
}