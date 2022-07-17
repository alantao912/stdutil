#ifndef STDUTIL_STACK_TESTS_H
#define STDUTIL_STACK_TESTS_H

#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include "../src/stack.h"
#include "assert.h"
#include "../src/primitives.h"

bool test_create_stack();

bool test_stack_push();

bool test_stack_peek();

bool test_stack_pop();

bool test_stack_ensure_capacity();

#endif