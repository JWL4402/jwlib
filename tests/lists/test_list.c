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
    /* SETUP */
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

    /* TESTING */
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

    /* TEARDOWN */
    list_destroy(list_init);
    list_destroy(list_appended_partial);
    list_destroy(list_appended);

    puts("\ttest_list_append() : PASS");
}

static void test_list_pushback() {
    /* SETUP */
    char* init_string[] = { // TODO char* [] works but not char**??
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List init_list = list_s(init_string);

    char* partial_string[] = {
        "Cherry", "Durian", "Eggplant", 0
    };
    List partial_list = list_s(partial_string);
    list_pushback(partial_list, (void*) "Banana");
    list_pushback(partial_list, (void*) "Apple");

    char* pushback_string[] = {
        0
    };
    List pushback_list = list_s(pushback_string);
    list_pushback(pushback_list, (void*) "Eggplant");
    list_pushback(pushback_list, (void*) "Durian");
    list_pushback(pushback_list, (void*) "Cherry");
    list_pushback(pushback_list, (void*) "Banana");
    list_pushback(pushback_list, (void*) "Apple");

    /* TESTING */
    assert("List using pushback has same length as initialized list" &&
        init_list->count == partial_list->count &&
        init_list->count == pushback_list->count);

    assert("List using pushback has same type as initialized list" &&
        strcmp(init_list->type, partial_list->type) == 0 &&
        strcmp(init_list->type, pushback_list->type) == 0);

    for (int i = 0; i < init_list->count; i++) {
        void* init_data = list_get(init_list, i);
        void* partial_data = list_get(partial_list, i);
        void* pushback_data = list_get(pushback_list, i);
        assert("All methods produce identical lists" &&
            init_data == partial_data &&
            init_data == pushback_data);
    } // TODO : should probably test by value not reference?

    /* TEARDOWN */
    list_destroy(init_list);
    list_destroy(partial_list);
    list_destroy(pushback_list);

    puts("\ttest_list_pushback() : PASS");
}

int main() {
    puts("Test suite: test_list.c");
    test_list_s();
    test_list_at();
    test_list_get();
    test_list_append();
    test_list_pushback();
    puts("test_list.c : PASS");

    return 0;
}