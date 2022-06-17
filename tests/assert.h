#ifndef STDUTIL_ASSERT_H
#define STDUTIL_ASSERT_H

#include <setjmp.h>

void int_assert_equal(int val0, int val1, int assert_code);

void int_assert_nequal(int val0, int val1, int assert_code);

#endif