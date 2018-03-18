// Linked List passing "head" variable
// between functions
// - Insert AtBegginning
// - Print Elements

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;


void InsertAtBeginning(Node **head, int x) 
{
    Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = x;
        temp->next = NULL;
        if(*head != NULL) temp->next = *head;
        *head = temp;
}

void InsertAtBeginningSimplified(Node **head, int x) 
{
    Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = x;
        temp->next = *head;
        *head = temp;
}

void Print(Node *head) {
    printf("List is: ");
    while(head!= NULL)
    {
        printf(" %d", head->data);
        head=head->next;
    }
    printf("\n");
}

int main() {
    Node *head = NULL; // empty list

    printf("How many numbers?\n");
    int n,i,x;
    scanf("%d", &n);

    for(i = 0; i< n; i++) {
        printf("Enter the number \n");
        scanf("%d", &x);
        InsertAtBeginningSimplified(&head, x);
        Print(head);
    }
}

