// Queue 
// - Array implementation of queue (circular)

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define MAX_SIZE 10


int A[MAX_SIZE];
int front = -1;
int rear = -1;


int isEmpty() {
    if (front == -1 && rear == -1) {
        return 1;
    } else {
        return 0;
    }
}


int isFull() {
    if ((rear + 1) % MAX_SIZE == front) {
        return 1;
    } else {
        return 0;
    }
}

void Enqueue(int x) {
    if (isFull()) {
        printf("The queue is Full!\n");
        return;
    } else if (isEmpty()) {
        front = 0;
        rear = 0;
        A[rear] = x;
    } else {
        rear = (rear + 1) % MAX_SIZE;
        A[rear] = x;
    }
}

void Dequeue() {
    if (isEmpty()) {
        printf("The queue is Empty!\n");
        return;
    } else if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front+1) % MAX_SIZE;
    }
}

void Print() {
    // Printing all queue indexes
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    if (front <= rear) {
        // Printing empty spaces until "front" of queue
        for (int i = 0; i < front; i++) {
            printf("  ");
        }
        // Printing existing queue elements
        for (int i = front; i <= rear; i++) {
            printf("%d ", A[i]);
        }
        // Printing empty spaces after "rear" of queue
        for (int i = rear; i < MAX_SIZE; i++) {
            printf("  ");
        }
    } else {
        // Printing existing queue elemnts 
        // from 0 to rear, since front > rear
        for (int i = 0; i <= rear; i++) {
            printf("%d ", A[i]);
        }
        // Printing empty spaces between end of 
        // "rear" and start of "front"
        // since front > rear
        for (int i = rear + 1; i < front; i++) {
            printf("  ");
        }
        // Printing existing queue elements from front
        // to the end
        // since front > rear
        for (int i = front; i < MAX_SIZE; i++) {
            printf("%d ", A[i]);
        }
    }

    printf("\n");
    printf("\n");
}

int main() {
    printf("Initial view: \n");
    Print();

    Dequeue();
    Print();

    Enqueue(1);
    Enqueue(2);
    Enqueue(3);
    Print();

    Dequeue();
    Print();

    Enqueue(4);
    Print();

    Enqueue(5);
    Enqueue(6);
    Enqueue(7);
    Print();

    Dequeue();
    Dequeue();
    Print();

    Enqueue(8);
    Enqueue(9);
    Print();

    Dequeue();
    Enqueue(1);
    Print();

    Enqueue(2);
    Print();

    Dequeue();
    Dequeue();
    Dequeue();
    Dequeue();
    Dequeue();
    Print();

    Dequeue();
    Print();

    Dequeue();
    Print();

    Enqueue(1);
    Enqueue(2);
    Print();

    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Enqueue(1);
    Print();

    Dequeue();
    Dequeue();
    Dequeue();
    Print();

    Enqueue(2);
    Enqueue(2);
    Print();

    Enqueue(3);
    Print();

    Enqueue(4);
    Print();

    return 0;
}

