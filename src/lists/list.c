#include <stdlib.h>
#include <stdio.h>

#include "../../include/lists/list.h"

List list_s(char** strings) {
    // strings should be terminated with a 0
    List list = malloc(sizeof(list));
    if (list == 0) { return 0; }
    
    list->HEAD = 0;
    list->count = 0;
    list->type = "string";

    Node* last_node;
    while (*(strings + list->count) != 0) {
        Node* cur_node = (Node*) malloc(sizeof(Node));
        if (cur_node == 0) { 
            return list;
        }
        
        cur_node->data = *(strings + list->count);
        cur_node->next = 0;
        
        if (list->count == 0) {
            list->HEAD = cur_node;
        } else {
            last_node->next = cur_node;
        }
        
        last_node = cur_node;
        list->count++;
    }

    return list;
}

void list_append(List list, void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == 0) { return; }
    new_node->data = data;
    new_node->next = 0;

    list->count++;

    if (list->HEAD == 0) {
        list->HEAD = new_node;
        return;
    }

    Node* cur_node = list->HEAD;

    while (cur_node->next != 0) {
        cur_node = cur_node->next;
    }; // if true, have to make the head = new node after malloc

    cur_node->next = new_node;
}

void list_pushback(List list, void* data) {
    Node* head = list->HEAD;

    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == 0) { return; }
    new_node->data = data;
    new_node->next = head;

    list->HEAD = new_node;
    list->count++;
}

Node* list_at(List list, int index) {
    Node* cur_node = list->HEAD;
    for (int i = 0; i < index; i++) {
        Node* next_node = cur_node->next;

        if (next_node == 0) {
            return 0;
        }

        cur_node = next_node;
    }

    return cur_node;
}

void* list_get(List list, int index) {
    Node* node = list_at(list, index);

    if (node == 0) { return 0; }

    return node->data;
}

void list_destroy(List list) {
    Node* cur_node = list->HEAD;

    while (cur_node != 0) {
        Node* next_node = cur_node->next;
        cur_node->next = 0; // necessary?
        free(cur_node);
        cur_node = next_node;
    }
    
    free(list);
}