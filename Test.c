#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include "Primitives.h"

int comparator(const void* cmpl, const void* cmpr) {
	return *(int*)cmpl - *(int*)cmpr;
}

int main() {
	
	struct ArrayList list = create_ArrayList(10);
	
	
	for(int i = 0; i < list.capacity; i++)
		add(&list, Integer(rand() % 20));

	sort(&list, comparator);


	for(int i = 0; i < list.size; i++)
		printf("%d ", *(int*)(list.elements[i]));
	printf("\n");
	
	return 0;
}
