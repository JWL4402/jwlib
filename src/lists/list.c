#include <stdlib.h>
#include <stdio.h>

#include "../../include/lists/list.h"

List list_s(char** strings) {
    // strings should be terminated with a 0
    Node* HEAD = 0;

    Node* last_node;

    int iter = 0;
    while (*(strings + iter) != 0) {
        Node* cur_node = (Node*) malloc(sizeof(Node));
        if (cur_node == 0) { return 0; } // ?
        
        cur_node->data = *(strings + iter);
        cur_node->next = 0;
        
        if (HEAD == 0) {
            HEAD = cur_node;
        } else {
            last_node->next = cur_node;
        }
        
        last_node = cur_node;
        iter++;
    }

    return HEAD;

}

void list_append(List HEAD, void* data) {
    List cur_node = HEAD;

    while (cur_node->next != 0) {
        cur_node = cur_node->next;
    };

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = 0;

    cur_node->next = new_node;
}

/*
NEXT QUESTION :
SHOULD FUNCTION RETURN A SUCESS CODE, and modify a pointer,
OR

*/

Node* list_at(List HEAD, int index) {
    Node* cur_node = HEAD;
    for (int i = 0; i < index; i++) {
        Node* next_node = cur_node->next;

        if (next_node == 0) {
            // fprintf(stderr, "Index %d is out of bounds.\n", index);
            // TODO : Should there be an error print here? or is returning NULL pointer sufficient
            return 0;
        }

        cur_node = next_node;
    }

    return cur_node;
}

void* list_get(List HEAD, int index) {
    Node* node = list_at(HEAD, index);

    if (node == 0) { return 0; }

    return node->data;
}

void list_destroy(List HEAD) {
    Node* cur_node = HEAD;

    while (cur_node != 0) {
        Node* next_node = cur_node->next;
        cur_node->next = 0; // necessary?
        free(cur_node);
        cur_node = next_node;
    }
}