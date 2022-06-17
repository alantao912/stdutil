#ifndef STDUTIL_ASSERT_H
#define STDUTIL_ASSERT_H

#include <stdbool.h>
#include <setjmp.h>

void int_assert_equal(int val0, int val1, int assert_code);

void int_assert_nequal(int val0, int val1, int assert_code);

void int_array_assert_equal(int **arr0, int *arr1, int size, int assert_code);

void int_array_assert_nequal(int **arr0, int *arr1, int size, int assert_code);

void bool_assert_equal(bool bool0, bool bool1, int assert_code);

#endif