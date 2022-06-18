CC = gcc
SRC_DIR = src
TEST_DIR = tests
LIB_OUT = out/stdutil_win.a
TEST_OUT = tests/run_tests.exe

objects = *.o

*.o : $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	$(CC) -c $(SRC_DIR)/*.c
	ar rcs $(LIB_OUT) $(objects)

	$(CC) -c $(TEST_DIR)/*.c
	$(CC) $(objects) -o $(TEST_OUT)
	del *.o