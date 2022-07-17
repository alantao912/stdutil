#include "stack_tests.h"

jmp_buf break_point;

bool test_create_stack() {
    printf("Test: \"create_stack(size_t capacity)\" is starting ... ");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch(assert_code) {
            case 1:
            printf("stack->capacity is incorrect value.");
            break;
            case 2:
            printf("stack->size != 0 upon creation.");
            break;

        }
        printf("\n\n");
        return false;
    } else {
        stack *s = create_stack(4);
        int_assert_equal(s->capacity, 4, 1);
        int_assert_equal(s->size, 0, 2);
        free(s);
    }

    printf("\x1b[32m passed!\x1b[0m\n\n");
    return true;
}

bool test_stack_push() {
    printf("Test: \"push(stack *s, void *element)\" is starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch(assert_code) {
            case 1:
                printf("pushed elements do not appear in correct order.");
            break;
            case 2:
                printf("s->size is not correct value after after push.");
            break;
            case 3:
                printf("s->capacity is not correct value after push.");
            break;
        }
        printf("\n\n");
        return false;
    } else {
        stack* s = create_stack(5);
        int correct_values[] = {3, 4, 5, 6, 7, 8};
        push(s, Integer(3));
        push(s, Integer(4));
        push(s, Integer(5));
        int_array_assert_equal((int **) s->elements, correct_values, 3, 1);
        int_assert_equal(s->size, 3, 2);
        push(s, Integer(6));
        push(s, Integer(7));
        push(s, Integer(8));
        int_array_assert_equal((int **) s->elements, correct_values, 6, 1);
        int_assert_equal(s->size, 6, 2);
        int_assert_equal(s->capacity, 10, 3);
    }
    printf("\x1b[32m passed!\x1b[0m\n\n");
    return true;
}

bool test_stack_peek() {
    printf("Test: \"peek(stack *s)\" is starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch(assert_code) {
            case 1:
                printf("pushed elements do not appear in correct order.");
            break;
            case 2:
                printf("s->size is not correct value after after push.");
            break;
            case 3:
                printf("peek(stack* target) does not return top element.");
            break;
        }
        printf("\n\n");
        return false;
    } else {
        stack* s = create_stack(5);
        int correct_values[] = {3, 4, 5};
        push(s, Integer(3));
        push(s, Integer(4));
        push(s, Integer(5));
        int_array_assert_equal((int **) s->elements, correct_values, 3, 1);
        int_assert_equal(s->size, 3, 2);
        int_assert_equal(*((int *) peek(s)), 5, 3);
    }
    printf("\x1b[32m passed!\x1b[0m\n\n");
    return true;
}

bool test_stack_pop() {
    printf("Test: \"pop(stack *s)\" is starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch(assert_code) {
            case 1:
                printf("pushed elements do not appear in correct order.");
            break;
            case 2:
                printf("s->size is not correct value after after push.");
            break;
            case 3:
                printf("pop(stack* target) does not return top element.");
            break;
            case 4:
                printf("pop(stack* target) does not decrement size.");
            break;
        }
        printf("\n\n");
        return false;
    } else {
        stack* s = create_stack(5);
        int correct_values[] = {3, 4, 5};
        push(s, Integer(3));
        push(s, Integer(4));
        push(s, Integer(5));
        int_array_assert_equal((int **) s->elements, correct_values, 3, 1);
        int_assert_equal(s->size, 3, 2);
        int *top = pop(s);

        int_assert_equal(*top, 5, 3);

        int_assert_equal(s->size, 2, 4);
    }
    printf("\x1b[32m passed!\x1b[0m\n\n");
    return true;

}

bool test_stack_ensure_capacity() {
    printf("Test: \"ensure_capacity(stack *s, size_t capacity)\" is starting ...");

    int assert_code;

    if ((assert_code = setjmp(break_point))) {
        printf("\x1b[31m failed!\x1b[0m\n\n");
        switch(assert_code) {
            printf("Exit code: %d", assert_code);
        }
        printf("\n\n");
        return false;
    } else {
        stack* s = create_stack(5);
        push(s, Integer(3));
        push(s, Integer(4));
        bool_assert_equal(s_ensure_capacity(s, 1), false, 1);
        bool_assert_equal(s_ensure_capacity(s, 4), true, 2);
        int_assert_equal(s->size, 2, 3);
        int_assert_equal(s->capacity, 4, 4);

        bool_assert_equal(s_ensure_capacity(s, 10), true, 5);
        int_assert_equal(s->capacity, 10, 6);
        int_assert_equal(s->size, 2, 7);
    }
    printf("\x1b[32m passed!\x1b[0m\n\n");
    return true;
}