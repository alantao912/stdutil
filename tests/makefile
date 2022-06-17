run_tests: arraylist_tests.o assert.o arraylist.o primitives.o run_tests.o
	gcc arraylist_tests.o assert.o primitives.o run_tests.o arraylist.o -o run_tests

arraylist_tests.o :arraylist_tests.c arraylist_tests.h 
	gcc -c arraylist_tests.c

primitives.o: ../src/primitives.c ../src/primitives.o
	gcc -c ../src/primitives.c

arraylist.o: ../src/arraylist.c ../src/arraylist.h 
	gcc -c ../src/arraylist.c

run_tests.o: run_tests.c
	gcc -c run_tests.c

assert.o: assert.c assert.h
	gcc -c assert.c