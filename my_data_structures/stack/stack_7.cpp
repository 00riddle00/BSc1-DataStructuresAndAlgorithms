//  Stack - linked list based implemention 
// Reverse a linked list
// Is interneto paimta

#include <stdlib.h>
#include <stdio.h>
#include <stack>

#define MAX_SIZE 50

int A[MAX_SIZE];

struct Node {
  int data;
  struct Node* link;
};

struct Node* top = NULL;

void push_head(int x) {
  struct Node* temp = new Node();
  temp->data = x;
  temp->link = top;
  top = temp;
}

void push_tail(int x) {
  struct Node* temp = top;
  while (temp->link != NULL) {
    temp = temp->link;
  }
  temp->link = new Node; // returns a pointer to the new node
  temp->link->data = x;
  temp->link->link = NULL;
}

void pop_head() {
  struct Node* temp; //no node necessary
  if (top == NULL) return;
  temp = top;
  top = top->link;
  free(temp);
}

void pop_tail() {
  struct Node* temp = top;
  struct Node* prev = NULL;
  while (temp->link != NULL) {
    prev = temp;
    temp = temp->link;
  }
  free(temp);
  prev->link = NULL;
}

void print() {
  Node* temp = top;
  while (temp != NULL) {
    printf("%d ", temp -> data);
    temp = temp -> link;
  }
  printf("\n");
}

void reverse() { // Time O(N), Space O(1)
  if (top == NULL) return;
  std::stack<struct Node*> S; //create a stack called S 
  Node* temp = top;
  while (temp != NULL) {
    S.push(temp); //LIFO 
    temp = temp->link;
  }
  temp = S.top(); //now temp is pointing at the last inserted element on the stack or the TOP
  top = temp; // head points at the same element 
  S.pop(); //clear up the element from top of the stack 
  while(!S.empty()) {
    temp->link = S.top(); //point temp to the previous element in the linked list, or the element at the top 
    S.pop(); // clear up that element fromt the stack
    temp = temp->link;
  }
  temp->link = NULL;
}

int main() {
  push_head(2);
  print(); // output 2
  push_head(6);
  print(); // output 6 2
  push_head(9);
  print(); // output 9 6 2
  pop_head();
  print(); // output 6 2
  push_tail(8);
  print(); // output 6 2 8
  pop_head();
  print(); // output 2 8
  pop_tail();
  push_tail(3);
  print(); // output 2 3
  push_tail(5);
  print(); // output 2 3 5
  pop_tail();
  print(); // output 2 3
  push_head(6);
  push_tail(19);
  push_tail(55);
  print(); // output 6 2 3 19 55
  reverse();
  print(); // output 55 19 3 2 6
}

