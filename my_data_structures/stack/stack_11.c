// Stack 
// - Evaluate Postfix expression

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push(int c);
int pop();
void eraseStack();
int isEmpty();
void print();

// Function to evaluate Postfix expression and return outupt
// Veikia jeigu tik vienazenkliai skaiciai
int EvaluatePostfix(char *exp, int size);

// Function to perform an operation and return output
int PerformOperation(char operation, int operand1, int operand2);

// Function to verify whether a character is operator symbol or not
int IsOperator(char c);


Node *top = NULL;

int EvaluatePostfix(char *exp, int size) {
    for(int i = 0; i < size; i++) {
        if(isdigit(exp[i])) {
            // convert a numeric character (digit) to 
            // an integer value using ASCII code offset
            push(exp[i] - '0');
        } else if (IsOperator(exp[i])) {
            int op1 = pop();
            int op2 = pop();
            int res = PerformOperation(exp[i], op1, op2);
            push(res); 
        }
    print();
    }
    return top->data;
}

int PerformOperation(char operation, int operand1, int operand2) {
	if(operation == '+') return operand1 +operand2;
	else if(operation == '-') return operand2 - operand1;
	else if(operation == '*') return operand1 * operand2;
    else if(operation == '/') return operand1 / operand2;

    else printf("Unexpected Error \n");
    return -1;
}

int IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void push(int n) {
  Node *temp = malloc(sizeof(Node));
  if (temp == NULL) {
    printf("Cannot create node!");
    return;
  }
  temp -> data = n;
  temp -> next = top;
  top = temp;
}

int pop() {  // <-- kompiliuojasi, nepaisant klaidos
  if (isEmpty()) {
	return;
  }
  int n = top->data;
  Node *temp = top;
  top = top->next;
  free(temp);
  return n;
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
    printf("Printing Stack:\n");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    printf("Postfix evaluated: %d\n", EvaluatePostfix("23*54*+9-", 9));
}
