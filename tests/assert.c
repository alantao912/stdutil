#include "assert.h"

extern jmp_buf break_point;

void int_assert_equal(int val0, int val1, int assert_code) {
    if (val0 != val1) {
        longjmp(break_point, assert_code);
    }
}

void int_assert_nequal(int val0, int val1, int assert_code) {
    if (val0 == val1) {
        longjmp(break_point, assert_code);
    }
}

void int_array_assert_equal(int **arr0, int *arr1, int size, int assert_code) {
    for (int i = 0; i < size; ++i) {
        if (*(arr0[i]) != arr1[i]) {
            printf("(arr0[%d] == %d, arr1[%d] == %d)\n", i, *(arr0[i]), i, arr1[i]);
            longjmp(break_point, assert_code);
        }
    }
}

void int_array_assert_nequal(int **arr0, int *arr1, int size, int assert_code) {
    for (int i = 0; i < size; ++i) {
        if (*(arr0[i]) != arr1[i]) {
            return;
        }
    }
    longjmp(break_point, assert_code);
}

void bool_assert_equal(bool bool0, bool bool1, int assert_code) {
    if (bool0 != bool1) {
        longjmp(break_point, assert_code);
    }
}