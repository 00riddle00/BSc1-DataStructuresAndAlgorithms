// Stack 
// - Infix to Postfix expression

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
        } else if (IsOperator(exp[i])) {
            // if stack is not empty and the precedence is not higher (might
            // not be lower (ex. + and -), but just not higher), then pop all 
            // the elements from the stack which have higher than or SAME(!!) precedence 
            // as the operator.
            while (!isEmpty() && !HigherPrecedence(exp[i], top->data)) {
                printf("%c ", pop());
            }
            // push the operator to stack 
            // THE CASES: 
            // (1) we encountered the operator of lower precedence in top of stack 
            // (2) stack reached its end (stack is empty)
            // (3) stack was empty to begin with
            push(exp[i]);
        }
    }
    while(!isEmpty()) {
        printf("%c ", pop());
    }
    // TODO: return the actual result string instead of just printing every
    // time the character to output
    return "RETURN";
}

int HigherPrecedence(char operator, char stack_top) {
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

    char *expression = "A+B*C-D*E";
    int size = 9;

    printf("Infix expression: %s\n", expression);
    /*printf("Postfix expression: %s\n", InfixToPostfix(expression, 9));*/
    printf("Postfix expression: \n");
    InfixToPostfix(expression, size);
    printf("\n");

    return 0;
}
