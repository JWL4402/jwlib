// To keep it simple, to start we will test with simple assert() statements

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/lists/list.h"

static void test_list_s() {
    char* empty[] = {
        0
    };

    List empty_list = list_s(empty);

    assert("Empty list HEAD points to NULL" &&
        empty_list->HEAD == 0);
    assert("Empty list count is 0" &&
        empty_list->count == 0);
    assert("Empty list initialized via list_s is of type string" &&
        strcmp(empty_list->type, "string") == 0);

    list_destroy(empty_list);

// todo { 0 }
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    assert("Count is accurate" &&
        list->count == 5);

    assert("Type is accurate" &&
        strcmp(list->type, "string") == 0);

    Node* node = list->HEAD;
    for (int i = 0; i < list->count; i++) {
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

    Node* cur_node = list->HEAD;

    for (int i = 0; i < list->count; i++) {
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

    for (int i = 0; i < list->count; i++) {
        Node* node_at = list_at(list, i);
        void* data_get = list_get(list, i);
        assert("list_get() corresponds to the data at the specified index" &&
            node_at->data == data_get);
    }

    list_destroy(list);

    puts("\ttest_list_get() : PASS");
}

static void test_list_append() {
    char* strings1[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list_init = list_s(strings1);

    char* strings2[] = {
        "Apple", "Banana", "Cherry", 0
    };
    List list_appended_partial = list_s(strings2);
    list_append(list_appended_partial, (void*) "Durian");
    list_append(list_appended_partial, (void*) "Eggplant");

    char* strings3[] = {
        0
    };
    List list_appended = list_s(strings3);
    list_append(list_appended, (void*) "Apple");
    list_append(list_appended, (void*) "Banana");
    list_append(list_appended, (void*) "Cherry");
    list_append(list_appended, (void*) "Durian");
    list_append(list_appended, (void*) "Eggplant");

    assert("List using append has same length as initialized list" &&
        list_init->count == list_appended->count &&
        list_init->count == list_appended_partial->count);

    assert("List using append has same type as initialized test" &&
        strcmp(list_init->type, list_appended->type) == 0 &&
        strcmp(list_init->type, list_appended_partial->type) == 0);

    for (int i = 0; i < list_init->count; i++) {
        void* list_data = list_get(list_init, i);
        void* list_appended_data = list_get(list_appended, i);
        void* list_appended_partial_data = list_get(list_appended_partial, i);
        assert("All methods produce identical lists" &&
            list_data == list_appended_data &&
            list_data == list_appended_partial_data);
    }

    list_destroy(list_init);
    list_destroy(list_appended_partial);

    puts("\ttest_list_append() : PASS");
}

int main() {
    puts("Test suite: test_list.c");
    test_list_s();
    test_list_at();
    test_list_get();
    test_list_append();
    puts("test_list.c : PASS");

    return 0;
}