#ifndef MOD_H
#define MOD_H

typedef struct Stack {
    void **data;
    // maximum index (index of top element)
    int max;
} Stack;

// This function adds element to the end of the structure.
void push(Stack *s, void *value, int valueSize);

// Get pointer to the top element, and remove it from the stack
void *pop(Stack *s);

// Get the element count of the stack as integer
int get_count(Stack *s);

// Create empty stack
Stack create_stack();

// Get element from Stack by index, not removing it from the stack
// (pass by reference)
void *get_nth_element(Stack *s, int n);

// Execute if memory error occurs (exits the program)
void die(char *message);

#endif