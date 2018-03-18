// This module provides functions, which is necessary working with stack.

// Stack implementation with pointers (dynamic array)

// Version history:
// v0: Created mod.c and mod.h files
// v1: used if sentences to fix some problems
//     added debugging mode (#define DEBUG 0)
// v2: now functions can operate with all types of variables
// v3: Author:  - Tomas Giedraitis (student).
//     Changes: - Add required libraries for 'malloc' and 'memcpy'
//              - Edit 'push' and 'pop' functions (memory alloc, return values)
//              - Add functions to create stack, get element count, get nth
//              - element and add memory error handler function.


#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mod.h"


//------------------------------------------------------------------------------
void push(Stack *s, void *value, int valueSize) {

    s->max++;

    // reallocate memory for array of void pointers
    s->data = realloc(s->data, ((s->max) + 1) * sizeof(s->data));

    if (!s->data) {
        die("Memory error!\n");
    }

    // allocate memory for new stack element
    s->data[s->max] = malloc(valueSize);
    if (!s->data[s->max]) {
        die("Memory error!\n");
    }

    memcpy(s->data[s->max], value, valueSize);

#if DEBUG
    printf("Element added.\n");
#endif
}

//------------------------------------------------------------------------------
void *pop(Stack *s) {
    if (s->max >= 0) {
#if DEBUG
        printf("Element popped.\n");
#endif
        return s->data[s->max--];
    }
#if DEBUG
    printf("The stack is empty.\n");
#endif
}

//------------------------------------------------------------------------------
Stack create_stack() {
    Stack s;
    s.data = NULL;
    // stack is 0-indexed, hence max index of empty stack is -1
    s.max = -1;

    return s;
}

//------------------------------------------------------------------------------
int get_count(Stack *s) {

    // since stack is 0-indexed, add 1
    return s->max+1;
}

//------------------------------------------------------------------------------
void *get_nth_element(Stack *s, int n) {

    if (s->max == 0) {
        printf("The stack is empty.\n");
    } else if (n > s->max || n <= 0) {
        printf("The is no such element by that index in the stack\n");
    }

    void *ptr = s->data[n];

    return ptr;
}

//------------------------------------------------------------------------------
void die(char *message) {
#if DEBUG
    if (errno) {
        perror(message);
    } else {
        printf("%s\n", message);
    }
#endif
    exit(1);
}

