CC = gcc
OBJ_DIR = objdump
SRC_DIR = src
TEST_DIR = tests
LIB_OUT = out/stdutil.a
TEST_OUT = tests/run_tests.out

objects = $(OBJ_DIR)/*.o

*.o : $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	$(CC) -c $(SRC_DIR)/*.c
	mv *.o $(OBJ_DIR)
	ar rcs $(LIB_OUT) $(objects)

	$(CC) -c $(TEST_DIR)/*.c
	mv *.o $(OBJ_DIR)
	$(CC) $(objects) -o $(TEST_OUT)