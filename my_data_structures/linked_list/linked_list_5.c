// Linked List: deleting a node at nth position
// One-indexed linked-list
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node *head; // global

// Delete node at position n
void Delete(int n)
{
    struct Node *temp1 = head;
    if(n==1) {
        head = temp1->next; // head now
        free(temp1);
        return;
    }
    int i;
    for (i = 0; i < n-2; i++)
        temp1 = temp1->next;
    // temp1 points to (n-1)th Node
    struct Node* temp2 = temp1->next; // nth Node
    temp1->next = temp2->next; // (n+1)th Node
    free(temp2); //delete temp2;
}

// Insert an integer at the end of list
void Insert(int data) {  
    Node *temp1 = malloc(sizeof(struct Node));
    temp1->data = data;
    temp1->next = NULL;

    if (head == NULL) {
        head = temp1;
        return;
    }

    Node *temp2 = head;
    while(temp2->next != NULL) {
        temp2 = temp2->next;
    }
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
    head = NULL; // empty list;
    Insert(2);
    Insert(4);
    Insert(6);
    Insert(5); // List : 2,4,6,5
    Print();
    int n;
    printf("Enter a position\n");
    scanf("%d", &n);
    Delete(n);
    Print();
}

