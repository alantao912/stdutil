#include <stdio.h>
#include "arraylist_tests.h"
#include "stack_tests.h"
#include "../src/dlinked_list.h"

int main(int argc, char *argv[]) {
    test_create_arraylist();
    test_create_arraylist_OOM();
    test_al_add();
    test_al_addAt();
    test_al_set();
    test_ensure_capacity();
    test_al_get();
    test_remove();
    test_create_stack();
    test_stack_push();
    test_stack_peek();
    test_stack_pop();
    test_stack_ensure_capacity();
    dlinked_list *dll = create_dlinkedlist();
    printf("dll size: %d\n", dll->size);
    if (!(dll->head) && !(dll->tail)) {
        printf("Head and tail are both null!\n");
    }
    return 0;
}
