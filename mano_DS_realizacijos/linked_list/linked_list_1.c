// Linked List basics
// - creating first node
// - creating new node
// - creating new node to the end of the list
// - traversing the list
// - printing elements in the list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head;


int main() {
    head = NULL; // empty list

    // Creating a first node
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = 2;
    temp->next = NULL;
    head = temp;

    // Creating new node
    temp = malloc(sizeof(Node));
    temp->data = 4;
    temp->next = NULL;

    // List traversal and adding a created node
    Node *temp1 = head;
    while (temp1 -> next != NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = temp;


    // List traversal and printing
    Node *temp1 = head;
    while (temp1 -> next != NULL)
    {
        temp1 = temp1->next;
        printf("%d ", temp1->data);
    }

}

