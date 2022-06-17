#include "arraylist_tests.h"

jmp_buf break_point;

bool test_create_arraylist() {
    printf("Test: \"create_arraylist('int')\" starting ... \n");

    int assert_code;

    if (assert_code = setjmp(break_point)) {
        switch (assert_code) {
            case 1:
            printf("list->capacity != DEFAULT_CAPACITY when initial_capacity == 0.\n");
            break;
            case 2:
            printf("list->size != 0 when \"create_arraylist('int')\" returns.\n");
            break;
            case 3:
            printf("list->elements == NULL when \"create_arraylist('int')\" returns.\n");
            break;
        }
        printf("Test: create_arraylist('int') failed!\n");
        return false;
    } else {
        arraylist *list = create_arraylist(0);
        int_assert_equal(list->capacity, 10, 1);
        int_assert_equal(list->size, 0, 2);
        int_assert_nequal((int) list->elements, 0, 3);
        free(list->elements);
        free(list);

        list = create_arraylist(5);
        int_assert_equal(list->capacity, 5, 4);
        int_assert_equal(list->size, 0, 2);
        int_assert_nequal((int) list->elements, 0, 3);
        free(list->elements);
        free(list);

        printf("Test: \"create_arraylist('int')\" passed!\n\n");
        return true;
    }
}

bool test_create_arraylist_OOM() {
    printf("Test: \"create_arraylist(UINT_MAX)\" starting ... \n");
    
    int assert_code;

    if (assert_code = setjmp(break_point)) {
        switch (assert_code) {
            case 1:
            printf("list != NULL when \"create_arraylist(UINT_MAX)\" returns.\n");
            break;
        }
         printf("Test: \"create_arraylist(UINT_MAX)\" failed! \n");
    } else {
        arraylist *list = create_arraylist(UINT_MAX);
        int_assert_equal((int) list, 0, 1);
        printf("Test: \"create_arraylist(UINT_MAX)\" passed! \n");    
    }
}

bool test_al_add();

bool test_al_addAt();

bool test_al_set();

bool test_ensure_capacity();

bool test_al_get();

bool test_remove();

bool test_sort();