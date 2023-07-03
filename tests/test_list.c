// To keep it simple, to start we will test with simple assert() statements

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/lists/list.h"

static void test_list_s() {
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    Node* node = list;
    for (int i = 0; i < 5; i++) {
        assert("Initializing variables" &&
            strcmp(node->data, *(strings + i)) == 0);
        node = node->next;
    }

    assert("Last element points to NULL" &&
        node == 0); // since we did node->next 5 times, and there is 5 elements, already at the end

    list_destroy(list);

    puts("test_list_s() : PASS\n");
}

int main() {
    test_list_s();

    return 0;
}