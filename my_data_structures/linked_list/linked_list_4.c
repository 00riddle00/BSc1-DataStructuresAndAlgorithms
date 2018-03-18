// Linked List: inserting a node at nth position
// One-indexed linked-list
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node *head;

void Insert(int data, int n) {
    Node *temp1 = malloc(sizeof(struct Node));
    temp1->data = data;
    temp1->next = NULL;
    if(n==1) {
        temp1->next = head;
        head = temp1;
        return;
    } 
    Node *temp2 = head;
    // i=0 corresponds to node1, i=1 to node2....... i=n-3 to node n-2.
    // at the end of execution, temp2 stores address of node n-1.
    // "head" is the same as "first" element, head->next = 2nd element (not 1st!);
    for (int i = 0; i < n-2; i++) {
        printf("HERE\n");
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    temp2->next = temp1;
}


void Print() {
    Node *temp = head;
    while(temp!=NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    head = NULL; // empty list
    Insert(2,1); // List: 2
    Insert(3,2); // List: 2,3
    Insert(4,1); // List: 4,2,3
    Insert(5,2); // List: 4,5,2,3
    Print();
}
