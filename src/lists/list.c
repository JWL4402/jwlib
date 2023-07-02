#include <stdlib.h>

#include "../../include/lists/list.h"

List list_s(char** strings) {
    // strings should be terminated with a 0
    Node* HEAD = (Node*) malloc(sizeof(Node));
    if (HEAD == 0) { return 0; }

    Node* cur_node = HEAD;
    cur_node->data = 0;

    int iter = 0;
    while (*(strings + iter) != 0) {
        Node* next_node = (Node*) malloc(sizeof(Node));
        if (next_node == 0) { return 0; } // ?
        
        cur_node->data = *(strings + iter);
        cur_node->next = next_node;
        cur_node = next_node;
        iter++;
    }

    cur_node->next = 0;

    return HEAD;

}