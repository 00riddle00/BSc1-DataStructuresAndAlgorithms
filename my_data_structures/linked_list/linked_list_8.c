// Reverse a linked list using recursion
// One-indexed linked-list
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node *head; // global

void Reverse(struct Node *p) {

    if (p->next == NULL)
    { 
        head = p;
        return;
    }
    Reverse(p->next);
    struct Node *q = p->next;
    q->next = p;
    // Could be written as 
    // p->next->next = p;
    p->next = NULL;
}
