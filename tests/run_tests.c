#include <stdio.h>
#include "arraylist_tests.h"

int main(int argc, char *argv[]) {
    test_create_arraylist();
    test_create_arraylist_OOM();
    test_al_add();
    return 0;
}
