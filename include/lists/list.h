#ifndef LIST_H
#define LIST_H

typedef struct node Node;
typedef struct list List;

struct node
{
    void* data;
    Node* next;
};

struct list
{
    Node* HEAD;
    int count;
    char* type;
};

List list_s(char*[]);
List list_i(int*);                  // TODO
List list_d(double*);               // TODO
void list_append(List, void*);      
void list_pushback(List, void*);    // TODO
Node* list_at(List, int);
void* list_get(List, int);
void list_destroy(List);

#endif // LIST_H