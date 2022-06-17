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