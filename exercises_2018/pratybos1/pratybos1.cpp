#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 25
#define TIMES 2000000000

clock_t begin;
clock_t end;

double clocks;
double time_spent;

int main(int argc, char* argv[])
{

    printf("Repetition times: %d\n", TIMES);

    // Test assignment time

    begin = clock();
    int res;

    for (int i = 0; i < TIMES; ++i) {
        res = i;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC;

    printf("Assignment time: %f clocks, %f seconds\n", clocks, time_spent);

    clock_t assignment = time_spent;

    // Test addition

    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        res = i + NUMBER;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test addition: %f seconds\n", time_spent);

    // Test subtraction

    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        res = i - NUMBER;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test subtraction: %f seconds\n", time_spent);

    // Test multiplication

    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        res = i * NUMBER;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test multiplication: %f seconds\n", time_spent);

    // Test division

    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        res = i / NUMBER;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test division: %f seconds\n", time_spent);

    // Test modulus

    begin = clock();

    for (int i = 0; i < TIMES; ++i) {
        res = i % NUMBER;
    }

    end = clock();

    clocks = (double)(end - begin);
    time_spent = clocks / CLOCKS_PER_SEC - assignment;

    printf("Test modulus: %f seconds\n", time_spent);
}
