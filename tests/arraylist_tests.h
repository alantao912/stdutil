#ifndef STDUTIL_ARRAYLIST_TESTS_H
#define STDUTIL_ARRAYLIST_TESTS_H

#include <stdio.h>
#include <setjmp.h>
#include <stdbool.h>
#include "assert.h"
#include "limits.h"
#include "../src/ArrayList.h"

bool test_create_arraylist();

bool test_create_arraylist_OOM();

bool test_al_add();

bool test_al_addAt();

bool test_al_set();

bool test_ensure_capacity();

bool test_al_get();

bool test_remove();

bool test_sort();

#endif