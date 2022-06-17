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
        printf("Test: create_arraylist('int') failed!\n\n");
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
         printf("Test: \"create_arraylist(UINT_MAX)\" failed! \n\n");
    } else {
        arraylist *list = create_arraylist(UINT_MAX);
        int_assert_equal((int) list, 0, 1);
        printf("Test: \"create_arraylist(UINT_MAX)\" passed! \n\n");    
    }
}

bool test_al_add() {
    printf("Test: \"al_add('arraylist *', 'void *')\" starting ... \n");
    
    int assert_code;

    if (assert_code = setjmp(break_point)) {
        switch (assert_code) {
            case 1:
            printf("list values not correctly populated by \"al_add('arraylist *', 'void *')\".\n");
            break;
            case 2:
            printf("list->size not correctly updated by \"al_add('arraylist *', 'void *')\"\n");
            break;
            case 3:
            printf("list->capacity should not have changed when only adding 3 values.\n");
            break;
            case 4:
            printf("list->elements did not resize properly when more than list->capacity elements were added.\n");
            break;
            case 5:
            printf("Order of data in list->elements is incorrect.\n");
            break;
        }
        printf("Test: \"al_add('arraylist *', 'void *')\" failed! \n\n");
    } else {
        arraylist *list = create_arraylist(10);
        al_add(list, Integer(3));
        al_add(list, Integer(4));
        al_add(list, Integer(5));
        int_assert_equal(*((int *) (list->elements[0])), 3, 1);
        int_assert_equal(*((int *) (list->elements[1])), 4, 1);
        int_assert_equal(*((int *) (list->elements[2])), 5, 1);

        int_assert_equal(list->size, 3, 2);
        int_assert_equal(list->capacity, 10, 3);

        for (int i = 0; i < 10; ++i) {
            al_add(list, Integer(4));
        }

        int_assert_equal(list->size, 13, 2);
        int_assert_equal(list->capacity, 20, 4);
        
        int correct_values[] = {3, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

        for (int i = 0; i < sizeof(correct_values) / sizeof(correct_values[0]); ++i) {
            int_assert_equal(*((int *) (list->elements[i])), correct_values[i], 5);
        }

        al_delete(list);
        free(list);
        
        printf("Test: \"al_add('arraylist *', 'void *')\" passed! \n\n");    
    }
}

bool test_al_addAt();

bool test_al_set();

bool test_ensure_capacity();

bool test_al_get();

bool test_remove();

bool test_sort();