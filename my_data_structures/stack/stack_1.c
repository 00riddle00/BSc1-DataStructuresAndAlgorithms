/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

// Stack implementation with static array
// Stack holds data structures of type "struct Point"

// TODOS:
// Convert Point pointers array to dynamic array
// Add top(), init(), get_elem_size() functions
// Validate user input
// display function


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Point {

    float x;
    float y;
    float z;

} Point;

typedef struct Stack {

    Point *data[10];
    int capacity;
    int size;

} Stack;


// Point functions
Point create_point(float x, float y, float z);
Point scan_point();
void print_point(Point p);
void get_coordinate(Point *p, char name);
void set_coordinate(Point *p, char name, float new_value);

// Stack functions
void print(Stack s);
void push(Stack *s, Point *p);
void pop(Stack *s);
void die();


int main(int argc, char *argv[]) {

    printf("NOTE: Stack is zero indexed.\n\n");


    Stack s;
    s.capacity = 10;
    s.size = 0;

    Point p1 = create_point(1.0, 2.5, 16.2);

    get_coordinate(&p1, 'z');
    set_coordinate(&p1, 'z', 42.42);
    print_point(p1);


    Point p2 = scan_point();
    print_point(p2);

    push(&s, &p1);
    push(&s, &p2);

    print(s);

    pop(&s);

    print(s);

    return 0;

}

Point create_point(float x, float y, float z) {
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;

    printf("Point created\n\n");

    return p;
}

void print_point(Point p) {
    printf("Point print out:\n");
    printf("(x, y, z): %f %f %f\n\n", p.x, p.y, p.z);
}

Point scan_point() {

    int coordinates = 3;
    float input;
    float array[3];

    printf("Enter x, y, z coordinates to create a point\n> ");

    for (int i = 0; i < coordinates; i++) {
        if ((scanf("%f", &input) == 1)) {
            array[i] = input;
        }
    }
    while (getchar() != '\n');

    Point p;

    p.x = array[0];
    p.y = array[1];
    p.z = array[2];

    printf("Point created\n\n");

    return p;
}


void get_coordinate(Point *p, char name) {

    switch (name) {
        case 'x':
            printf("x coordinate: %f\n", p->x);
            break;
        case 'y':
            printf("y coordinate: %f\n", p->y);
            break;
        case 'z':
            printf("z coordinate: %f\n", p->z);
            break;
        default:
            printf("No such coordinate\n");
    }
    printf("\n");
}


void set_coordinate(Point *p, char name, float new_value) {

    int valid = 1;

    switch (name) {
        case 'x':
            p->x = new_value;
            break;
        case 'y':
            p->y = new_value;
            break;
        case 'z':
            p->z = new_value;
            break;
        default:
            printf("No such coordinate\n");
            valid = 0;
    }
    if (valid) {
        printf("Set success.\n");
    }
    printf("\n");
}


void print(Stack s) {
    printf("Stack print out:\n");
    printf("[ID] (x, y, z): \n");

    for (int i = 0; i < s.size; i++) {
        printf("[%d] %f %f %f\n", i, s.data[i]->x, s.data[i]->y, s.data[i]->z);
        //void print_point(s.data[i]);
    }
    printf("\n\n");
};

void push(Stack *s, Point *p) {
    s->data[s->size] = p;
    s->size += 1;

    printf("Push success\n\n");
}

void pop(Stack *s) {

    s->data[s->size] = NULL;

    s->size -= 1;

    printf("Pop success\n\n");
}


void die(char *message) {
    printf("%s\n\n", message);
    exit(1);
}





