a: test.o arraylist.o primitives.o stack.o linked_list.o avl_tree.o matrix.o bmp_image.o queue.o hashmap.o set.o priority_queue.o
	gcc test.o arraylist.o primitives.o stack.o linked_list.o avl_tree.o matrix.o bmp_image.o queue.o hashmap.o set.o priority_queue.o -o a

libstdutil.a: arraylist.o primitives.o stack.o linked_list.o avl_tree.o matrix.o bmp_image.o queue.o hashmap.o set.o priority_queue.o
	ar rcs libstdutil.a arraylist.o primitives.o stack.o linked_list.o avl_tree.o matrix.o bmp_image.o queue.o hashmap.o set.o priority_queue.o

test.o: test.c
	gcc -c test.c

arraylist.o: arraylist.c arraylist.h
	gcc -c arraylist.c

primitives.o: primitives.c primitives.h
	gcc -c primitives.c

stack.o: stack.c stack.h
	gcc -c stack.c

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

avl_tree.o: avl_tree.c avl_tree.h
	gcc -c avl_tree.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

bmp_image.o: bmp_image.c bmp_image.h
	gcc -c bmp_image.c

queue.o: queue.c queue.h
	gcc -c queue.c

hashmap.o: hashmap.c hashmap.h
	gcc -c hashmap.c

set.o: set.c set.h
	gcc -c set.c

priority_queue.o: priority_queue.c priority_queue.h
	gcc -c priority_queue.c
