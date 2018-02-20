// Stack - Reverse a linked list
#include <iostream>
#include <cstring>
#include <stack> // stack from standard template library (STL)
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *head;

// mano funkcija
// needs refactoring
void createList(int size) {
    Node *temp = new Node();
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            head = temp;
        }
        temp->data = i;
        if (i != size-1) {
            temp->next = new Node();
            temp = temp->next;
        }
    }
}

void Print() {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Reverse() {
    if(head == NULL) return;
    stack<struct Node*> S;
    Node *temp = head;
    while(temp != NULL) {
        S.push(temp);
        temp = temp->next;
    }
    temp = S.top(); head = temp;
    S.pop();
    while(!S.empty()) {
        temp->next = S.top();
        S.pop();
        temp = temp->next;
    }
    temp->next = NULL;
}


int main() {
    createList(10);
    Print();
    Reverse();
    Print();
}
