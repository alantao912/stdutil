#include <stdio.h>
#include <stdbool.h>
#include "arraylist_tests.h"
#include "stack_tests.h"
#include "../src/dlinked_list.h"
#include "../src/hashmap.h"
#include "../src/lru_cache.h"

int main(int argc, char *argv[]) {
    test_create_arraylist();
    test_create_arraylist_OOM();
    test_al_add();
    test_al_addAt();
    test_al_set();
    test_ensure_capacity();
    test_al_get();
    test_remove();
    test_create_stack();
    test_stack_push();
    test_stack_peek();
    test_stack_pop();
    test_stack_ensure_capacity();
    lru_cache *cache = create_cache(4);
    int *k = Integer(4);
    cache_put(cache, Integer(3));
    cache_put(cache, k);
    cache_put(cache, Integer(5));
    cache_put(cache, Integer(6));

    printf("Before reputting 4:\n");
    dlist_node *iterator = cache->dll->head;
    while (iterator) {
        int *data = (int *) iterator->data;
        printf("%d, ", *data);
        iterator = iterator->next;
    }
    printf("\n");

    cache_put(cache, k);
    iterator = cache->dll->head;
    while (iterator) {
        int *data = (int *) iterator->data;
        printf("%d, ", *data);
        iterator = iterator->next;
    }
    printf("\n");

    int *lru = (int *) cache_get_lru(cache);
    int *mru = (int *) cache_get_mru(cache);
    printf("MRU: %d, LRU: %d\n", *mru, *lru);
    return 0;
}
