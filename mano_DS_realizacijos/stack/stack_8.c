// Stack C implementation with linked list
// Reverse a string
// Is interneto paimta

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

typedef struct node *Node;
typedef struct node node;
struct node {
  char data;
  Node next;
};
Node top = NULL;

void push(char c) {
  Node temp = (Node) malloc(sizeof(node));
  if (temp == NULL) {
    printf("Cannot create node!");
    return;
  }
  temp -> data = c;
  temp -> next = top;
  top = temp;
}

char pop() {  // <-- kompiliuojasi, nepaisant klaidos (return is empty)
  if (top == NULL) 
	return;
  char c = top -> data;
  Node temp = top;
  top = top -> next;
  free(temp);
  return c;
}

void Reverse(char s[], int n) {
  int i;
  for (i = 0; i < n; i++) 
	push(s[i]);
  for (i = 0; i < n; i++) 
	s[i] = pop();
}

int main() {
  char str[20];
  printf("Enter a string: ");
  gets(str);
  Reverse(str, strlen(str));
  printf("Reversed string: %s", str);
  return 0;
}
