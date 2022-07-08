#include "arraylist_tests.h"

jmp_buf break_point;

bool test_create_arraylist() {
    printf("Test: \"create_arraylist('size_t')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
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
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(0);
        int_assert_equal(list->capacity, 10, 1);
        int_assert_equal(list->size, 0, 2);
        int_assert_nequal((long) list->elements, 0, 3);
        free(list->elements);
        free(list);

        list = create_arraylist(5);
        int_assert_equal(list->capacity, 5, 4);
        int_assert_equal(list->size, 0, 2);
        int_assert_nequal((long) list->elements, 0, 3);
        free(list->elements);
        free(list);

        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_create_arraylist_OOM() {
    printf("Test: \"create_arraylist(ULLONG_MAX)\" starting ...");
    
    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch (assert_code) {
            case 1:
            printf("list != NULL when \"create_arraylist(ULLONG_MAX)\" returns.\n");
            break;
        }
        printf("\n");
         return false;
    } else {
        
        arraylist *list = create_arraylist(ULLONG_MAX);
        
        int_assert_equal((long) list, 0, 1);
        printf("\x1b[32m passed!\x1b[0m\n\n");  
        return true;  
    }
}

bool test_al_add() {
    printf("Test: \"al_add('arraylist *', 'void *')\" starting ...");
    
    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
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
                printf("\"al_add('arraylist *','void *')\" does not maintain correct order of elements.\n");
                
                break;
        }
        printf("\n");
        return false;
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

        int_array_assert_equal((int **) list->elements, correct_values, list->size, 5);

        al_delete(list);
        free(list);
        
        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true; 
    }
}

bool test_al_addAt() {
    printf("Test: \"al_addAt('arraylist *', 'size_t' ,'void *')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch (assert_code) {
            case 1:
                printf("\"al_addAt('arraylist *', 'size_t' ,'void *')\" does not maintain correct order of elements.\n");
            break;
            case 2:
                printf("\"al_addAt('arraylist *', 'size_t' ,'void *')\" does not increase array size.\n");
            break;
            case 3:
                printf("\"al_addAt('arraylist *', 'size_t' ,'void *')\" return incorrect status code.\n");
            break;
            case 4:
                printf("\"al_addAt('arraylist *', 'size_t' ,'void *')\" does not correctly resize backing array.\n");
            break;
            case 5:
                printf("\"al_addAt('arraylist *', 'size_t' ,'void *')\" does not return false when argument 'size_t' out of range.\n");
            break;
        }
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(6);
        al_add(list, Integer(3));
        al_add(list, Integer(4));
        bool status = al_addAt(list, 1, Integer(5));

        int_assert_equal(list->size, 3, 2);
        bool_assert_equal(status, true, 3);

        int correct_values[] = {3, 5, 4, -1, -1, -1, -1};
        int_array_assert_equal((int **) list->elements, correct_values, list->size, 1);

        status = al_addAt(list, 3, Integer(9));
        bool_assert_equal(status, true, 3);
        int_assert_equal(list->size, 4, 2);

        correct_values[3] = 9;
        int_array_assert_equal((int **) list->elements, correct_values, list->size, 1);

        al_addAt(list, 0, Integer(-3));
        al_addAt(list, 0, Integer(-4));
        al_addAt(list, 0, Integer(-5));

        correct_values[0] = -5;
        correct_values[1] = -4;
        correct_values[2] = -3;
        correct_values[3] = 3;
        correct_values[4] = 5;
        correct_values[5] = 4;
        correct_values[6] = 9;

        int_assert_equal(list->size, 7, 2);
        int_assert_equal(list->capacity, 12, 4);
        int_array_assert_equal((int **) list->elements, correct_values, list->size, 1);

        status = al_addAt(list, 999, Integer(10));
        bool_assert_equal(status, false, 5);

        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_al_set() {
    printf("Test: \"al_set('arraylist *', 'size_t' ,'void *')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {

        printf("\x1b[31m failed!\x1b[0m\n");
        switch (assert_code) {
            case 2:
                printf("\"al_set('arraylist *', 'size_t' ,'void *')\" changes size.\n");
            break;
            case 1:
                printf("\"al_set('arraylist *', 'size_t' ,'void *')\" does not preserve correct order.\n");
            break;
        
        }
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(6);
        al_add(list, Integer(3));
        al_add(list, Integer(4));
        al_add(list, Integer(5));

        al_set(list, 1, Integer(6));
        
        int correct_values[] = {3, 6, 5};
        int_assert_equal(list->size, 3, 2);
        int_array_assert_equal((int **) list->elements, correct_values, list->size, 1);

        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_ensure_capacity() {
    printf("Test: \"al_ensure_capacity('arraylist *', 'size_t')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {

        printf("\x1b[31m failed!\x1b[0m\n");
        switch (assert_code) {
            printf("al_ensure_capacity('arraylist *', 'size_t') ");
            case 1:
                printf("starting capacity is incorrect.\n");
            break;
            case 2:
                printf("starting size is incorrect.\n");
            break;
            case 3:
                printf("should fail when new_capacity < list->size.\n");
            break;
            case 4:
                printf("should return false when OOM occurs.\n");
            break;
            case 5:
                printf("should return true when successfully resizes.\n");
            break;
            case 6:
                printf("should preserve size when resizing.\n");
            break;
        
        }
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(6);

        al_add(list, Integer(1));
        al_add(list, Integer(1));

        int_assert_equal(list->capacity, 6, 1);
        int_assert_equal(list->size, 2, 2);

        bool status = al_ensure_capacity(list, 1);
        bool_assert_equal(status, false, 3);

        status = al_ensure_capacity(list, ULLONG_MAX);
        bool_assert_equal(status, false, 4);

        status = al_ensure_capacity(list, 3);
        bool_assert_equal(status, true, 5);
        int_assert_equal(list->size, 2, 6);

        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_al_get() {
    printf("Test: \"al_get('arraylist *', 'size_t')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {

        printf("\x1b[31m failed!\x1b[0m\n");
        switch (assert_code) {
            case 1:
            printf("does not return correct value\n");
            break;    
            case 2:
            printf("index out of bounds should return null\n.");
            break;
        
        }
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(6);

        al_add(list, Integer(1));
        al_add(list, Integer(2));
        
        int *i = (int *) al_get(list, 1);
        int_assert_equal(*i, 2, 1);

        i = (int *) al_get(list, 0);
        int_assert_equal(*i, 1, 1);

        i = (int *) al_get(list, 2);
        int_assert_equal((long) i, 0, 2);
        

        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_remove() {
    printf("Test: \"al_remove('arraylist *', 'size_t')\" starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {

        printf("\x1b[31m failed!\x1b[0m\n");
        switch (assert_code) {
            case 1:
                printf("size should be reduced by 1 when removing.\n");
            break;
            case 2:
                printf("capacity should not change when removing.\n");
            break;
            case 3:
                printf("does not retrieve correct value.\n");
            break;
            case 4:
                printf("does not maintain order of remaining elements.\n");
            break;
        
        }
        printf("\n");
        return false;
    } else {
        arraylist *list = create_arraylist(6);
        al_add(list, Integer(3));
        al_add(list, Integer(4));
        al_add(list, Integer(5));
        int *i = (void *) al_remove(list, 2);

        int_assert_equal(list->size, 2, 1);
        int_assert_equal(list->capacity, 6, 2);
        int_assert_equal(*i, 5, 3);

        int correct_values[2] = {3, 4};

        int_array_assert_equal((int **) list->elements, correct_values, list->size, 4);
        i = (void *) al_remove(list, 0);
        int_assert_equal(*i, 3, 3);
        correct_values[0] = 4;
        int_array_assert_equal((int **) list->elements, correct_values, list->size, 4);
        printf("\x1b[32m passed!\x1b[0m\n\n");
        return true;
    }
}

bool test_sort() {
    return false;
}