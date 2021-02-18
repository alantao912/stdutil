#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include "Primitives.h"

int main() {
	struct Stack stack = create_Stack(0);
	for(int i = 0; i < 10; i++)
		push(&stack, Integer(i));
	for(int i = 0; i < 10; i++) {
		void* element = pop(&stack);
		printf("%d\n", *(int*)element);
		free(element);
		element = NULL;
	}
	return 0;
}
