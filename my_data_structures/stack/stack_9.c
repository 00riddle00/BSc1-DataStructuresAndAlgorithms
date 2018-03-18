// Stack 
// Check for balanced parenthesis

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 


typedef struct Node {
    int data;
    struct Node *next;
} Node;

int ArePair(char opening, char closing);
int AreParenthesisBalanced(char *exp, int size);
void push(char c);
char pop();
void eraseStack();
int isEmpty();
void print();


Node *top = NULL;

int ArePair(char opening, char closing) {
	if(opening == '(' && closing == ')') return 1;
	else if(opening == '{' && closing == '}') return 1;
	else if(opening == '[' && closing == ']') return 1;
	return 0;
}

int AreParenthesisBalanced(char *exp, int size) {
    for (int i = 0; i < size; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            push(exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty() || !ArePair(top->data, exp[i]))  {
                eraseStack();
                return 0;
            } else {
                pop(exp[i]);
            }
        }
    }
    if (isEmpty()) {
        eraseStack();
        return 1;
    } else {
        eraseStack();
        return 0;
    }
}

void push(char c) {
  Node *temp = malloc(sizeof(Node));
  if (temp == NULL) {
    printf("Cannot create node!");
    return;
  }
  temp -> data = c;
  temp -> next = top;
  top = temp;
}

char pop() {  // <-- kompiliuojasi, nepaisant klaidos
  if (isEmpty()) {
	return;
  }
  char c = top -> data;
  Node *temp = top;
  top = top -> next;
  free(temp);
  return c;
}

void eraseStack() {
    while(!isEmpty()) {
        pop();
    }
}

int isEmpty() {
    return top == NULL;
}

void print() {
    Node *temp = top;
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    printf("Parenthesis balanced? %d\n", AreParenthesisBalanced(")(", 2));
    printf("Parenthesis balanced? %d\n", AreParenthesisBalanced("[()]", 4));
    printf("Parenthesis balanced? %d\n", AreParenthesisBalanced("[(])", 4));
    printf("Parenthesis balanced? %d\n", AreParenthesisBalanced("[()()]", 6));
    printf("Parenthesis balanced? %d\n", AreParenthesisBalanced("()", 2));
}
