#ifndef LIST_H
#define LIST_H

typedef struct node Node;
typedef Node * List;

struct node
{
    void* data;
    Node* next;
};

List list_s(char**);
void list_append(List, void*);
void list_pushback(List, void*);

#endif // LIST_H