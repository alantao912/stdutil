a: Test.o ArrayList.o Primitives.o Stack.o LinkedList.o BinaryTree.o Matrix.o ImageBMP.o Queue.o HashMap.o
	gcc Test.o ArrayList.o Primitives.o Stack.o LinkedList.o BinaryTree.o Matrix.o ImageBMP.o Queue.o HashMap.o -o a

Test.o: Test.c
	gcc -c Test.c

ArrayList.o: ArrayList.c ArrayList.h
	gcc -c ArrayList.c

Primitives.o: Primitives.c Primitives.h
	gcc -c Primitives.c

Stack.o: Stack.c Stack.h
	gcc -c Stack.c

LinkedList.o: LinkedList.c LinkedList.h
	gcc -c LinkedList.c

BinaryTree.o: BinaryTree.c BinaryTree.h
	gcc -c BinaryTree.c

Matrix.o: Matrix.c Matrix.h
	gcc -c Matrix.c

ImageBMP.o: ImageBMP.c ImageBMP.h
	gcc -c ImageBMP.c

Queue.o: Queue.c Queue.h
	gcc -c Queue.c

HashMap.o: HashMap.c HashMap.h
	gcc -c HashMap.c
