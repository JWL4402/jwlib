// To keep it simple, to start we will test with simple assert() statements

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../include/lists/list.h"

static void test_list_s() {
    /* SETUP */
    char* empty[] = {
        0
    };
    List empty_list = list_s(empty);

    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    /* TESTING */
    assert("Empty list HEAD points to NULL" &&
        empty_list->HEAD == 0);
    assert("Empty list count is 0" &&
        empty_list->count == 0);
    assert("Empty list initialized via list_s is of type string" &&
        strcmp(empty_list->type, "string") == 0);


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

    /* TEARDOWN */
    list_destroy(empty_list);
    list_destroy(list);

    puts("\ttest_list_s() : PASS");
}

static void test_list_at() {
    /* SETUP */
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    Node* cur_node = list->HEAD;

    /* TESTING */
    for (int i = 0; i < list->count; i++) {
        Node* node_at = list_at(list, i);
        assert("list_at() is an accurate shorthand for iterating through a list" &&
            cur_node->next == node_at->next &&
            cur_node->data == node_at->data);
        
        cur_node = cur_node->next;
    }

    /* TEARDOWN */
    list_destroy(list);

    puts("\ttest_list_at() : PASS");
}

static void test_list_get() {
    /* SETUP */
    char* strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List list = list_s(strings);

    /* TESTING */
    for (int i = 0; i < list->count; i++) {
        Node* node_at = list_at(list, i);
        void* data_get = list_get(list, i);
        assert("list_get() corresponds to the data at the specified index" &&
            node_at->data == data_get);
    }

    /* TEARDOWN */
    list_destroy(list);

    puts("\ttest_list_get() : PASS");
}

static void test_list_append() {
    /* SETUP */
    char* init_strings[] = {
        "Apple", "Banana", "Cherry", "Durian", "Eggplant", 0
    };
    List init_list = list_s(init_strings);

    char* partial_strings[] = {
        "Apple", "Banana", "Cherry", 0
    };
    List partial_list = list_s(partial_strings);
    list_append(partial_list, (void*) "Durian");
    list_append(partial_list, (void*) "Eggplant");

    char* appended_strings[] = {
        0
    };
    List appended_list = list_s(appended_strings);
    list_append(appended_list, (void*) "Apple");
    list_append(appended_list, (void*) "Banana");
    list_append(appended_list, (void*) "Cherry");
    list_append(appended_list, (void*) "Durian");
    list_append(appended_list, (void*) "Eggplant");

    /* TESTING */
    assert("List using append has same length as initialized list" &&
        init_list->count == appended_list->count &&
        init_list->count == partial_list->count);

    assert("List using append has same type as initialized test" &&
        strcmp(init_list->type, appended_list->type) == 0 &&
        strcmp(init_list->type, partial_list->type) == 0);

    for (int i = 0; i < init_list->count; i++) {
        void* list_data = list_get(init_list, i);
        void* list_appended_data = list_get(appended_list, i);
        void* list_appended_partial_data = list_get(partial_list, i);
        assert("All methods produce identical lists" &&
            list_data == list_appended_data &&
            list_data == list_appended_partial_data);
    }

    /* TEARDOWN */
    list_destroy(init_list);
    list_destroy(partial_list);
    list_destroy(appended_list);

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