// Stack 
// - Infix to Postfix expression (with parenthesis)

//***************
// all the comments concerning the main logic of the "InfixToPostfix" function
// are contained in the previous file ("stack_13.c"). In this file there 
// are only comments concerning the parenthesis.

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>


typedef struct Node {
    char data;
    struct Node *next;
} Node;

// Functions to work with Stack
void push(char n);
char pop();
void eraseStack();
int isEmpty();
void print();

// Function to evaluate Postfix expression and return outupt
// Veikia jeigu tik vienazenkliai skaiciai
char *InfixToPostfix(char *exp, int size);

// Function to evaluate the precedence of operators 
// Currently works for: "+", "-", "*"
int HigherPrecedence(char operator, char stack_top);

// Function to verify whether a character is operator symbol or not
int IsOperator(char c);


Node *top = NULL;

char *InfixToPostfix(char *exp, int size) {
    char res[size];
    for(int i = 0; i < size; i++) {

        if(isalpha(exp[i])) {
            printf("%c ", exp[i]);
        // if we encounter opening parenthesis, push 
        // it to stack
        } else if (exp[i] == '(') {
            push(exp[i]);
        // in case of closing parenthesis, pop everything
        // from stack until opening parenthesis. And print it all.
        // Then, pop the opening parenthesis (without printing them).
        } else if (exp[i] == ')') {
            while(top->data != '(') {
                printf("%c ", pop());
            }
            // Pop the opening parenthesis (without printing them).
            pop();
        } else if (IsOperator(exp[i])) {
            if (isEmpty()) {
                push(exp[i]);
                continue;
            } else if (HigherPrecedence(exp[i], top->data)) {
                push(exp[i]);
                continue;
            } else while (!isEmpty() && !HigherPrecedence(exp[i], top->data)) {
                printf("%c ", pop());
            }
            push(exp[i]);
        }
    }
    // if there are no elements left to read, pop everything left from the
    // stack (in this case, only operators are left, so they are being popped).
    // If the last character is closing parenthesis, this loop will not run.
    while(!isEmpty()) {
       printf("%c ", pop());
    }
    printf("\n\n");
    print();
    return "RETURN";
}

int HigherPrecedence(char operator, char stack_top) {
    // if the top of stack is opening parenthesis, 
    // we say that the precedence is higher. This is similar
    // to stack being empty, however, since stack is actually
    // not empty, the loop skips the "is_empty check", hence we
    // do it here
    if (stack_top == '(') { 
        return 1;
    }
    if ((operator == '*' && stack_top == '+') || (operator == '*' && stack_top == '-')) {
        return 1;
    } else if ((operator == '+' && stack_top == '-') || (operator == '-' && stack_top == '+')) {
        return 0;
    } else if ((operator == '+' && stack_top == '*') || (operator == '-' && stack_top == '*')) {
        return 0;
    }
}


int IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void push(char n) {
  Node *temp = malloc(sizeof(Node));
  if (temp == NULL) {
    printf("Cannot create node!");
    return;
  }
  temp -> data = n;
  temp -> next = top;
  top = temp;
}

char pop() {  // <-- kompiliuojasi, nepaisant klaidos
  if (isEmpty()) {
	return;
  }
  char n = top->data;
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
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {

    char *expression = "((A+B)*C-D*E)";
    int size = 13;

    printf("Infix expression: %s\n", expression);
    /*printf("Postfix expression: %s\n", InfixToPostfix(expression, 9));*/
    printf("Postfix expression: \n");
    InfixToPostfix(expression, size);
    printf("\n");

    return 0;
}
