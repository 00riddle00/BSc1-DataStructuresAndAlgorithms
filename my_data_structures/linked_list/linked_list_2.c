// Linked List passing using global "head" variable
// - Insert AtBegginning
// - Print Elements

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head;

void InsertAtBeginning(int x) 
{
    Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = x;
        temp->next = NULL;
        if(head != NULL) temp->next = head;
        head = temp;
}

void InsertAtBeginningSimplified(int x) 
{
    Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = x;
        temp->next = head;
        head = temp;
}

void Print() {
    struct Node *temp = head;
    printf("List is: ");
    while(temp!= NULL)
    {
        printf(" %d", temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main() {
    head = NULL; // empty list

    printf("How many numbers?\n");
    int n,i,x;
    scanf("%d", &n);

    for(i = 0; i< n; i++) {
        printf("Enter the number \n");
        scanf("%d", &x);
        InsertAtBeginningSimplified(x);
        Print();
    }
}

