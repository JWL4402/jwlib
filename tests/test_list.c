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

    assert("Count is accurate" &&
        list.count == 5);

    assert("Type is accurate" &&
        strcmp(list.type, "string") == 0);

    Node* node = list.HEAD;
    for (int i = 0; i < list.count; i++) {
        assert("Variables are properly initialized" &&
            strcmp(node->data, *(strings + i)) == 0);
        node = node->next;
    }

    assert("Last element points to NULL" &&
        node == 0); // since we did node->next 5 times, and there is 5 elements, already at the end

    list_destroy(list);

    puts("\ttest_list_s() : PASS");
}

static void test_list_at() {
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    Node* cur_node = list.HEAD;

    for (int i = 0; i < list.count; i++) {
        Node* node_at = list_at(list, i);
        assert("list_at() is an accurate shorthand for iterating through a list" &&
            cur_node->next == node_at->next &&
            cur_node->data == node_at->data);
        
        cur_node = cur_node->next;
    }

    list_destroy(list);

    puts("\ttest_list_at() : PASS");
}

static void test_list_get() {
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    for (int i = 0; i < list.count; i++) {
        Node* node_at = list_at(list, i);
        void* data_get = list_get(list, i);
        assert("list_get() corresponds to the data at the specified index" &&
            node_at->data == data_get);
    }

    list_destroy(list);

    puts("\ttest_list_get() : PASS");
}

int main() {
    puts("Test suite: test_list.c");
    test_list_s();
    test_list_at();
    test_list_get();

    return 0;
}