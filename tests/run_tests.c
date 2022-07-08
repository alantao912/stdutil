#include <stdio.h>
#include "arraylist_tests.h"

int main(int argc, char *argv[]) {
    test_create_arraylist();
    test_create_arraylist_OOM();
    test_al_add();
    test_al_addAt();
    test_al_set();
    test_ensure_capacity();
    test_al_get();
    test_remove();
    return 0;
}
