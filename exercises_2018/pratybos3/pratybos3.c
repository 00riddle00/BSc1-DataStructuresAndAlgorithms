/*=============================================================================
 |
 |  Assignment:   Exercise 3
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  February 20th, 2018
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -g -lm -std=c11 pratybos3.c -o pratybos3
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:
 |
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>

#include "dbg.h"
#include "lib_riddle.h"

//#define MINDIFF 2.2250738585072014e-308   // smallest positive double
#define MINDIFF 2.25e-308 // use for convergence check
#define N 10              // logarithm base

double get_pos_double(char* message, int zero_allowed)
{
    double num;
    int margin;

    if (zero_allowed) {
        margin = 0;
    } else {
        margin = 1;
    }

    while (1) {
        printf("%s", message);
        if (scanf("%lf", &num) == 1 && getchar() == '\n') {
            if (num >= margin) {
                break;
            } else {
                printf("Error: number is not positive");
                if (zero_allowed) {
                    printf(" or zero");
                }
                printf("\n");
            }
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a number\n");
        }
    }

    return num;
}

float f(int i)
{
    int j;
    float fact = 1;
    for (j = 0; j < i; j++)
        fact *= (j + 1);
    return fact;
}

double square_root(double square)
{
    double root = square / 3, last, diff = 1;
    if (square <= 0)
        return 0;
    do {
        last = root;
        root = (root + square / root) / 2;
        diff = root - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    return root;
}

float ln(float x)
{
    int i;
    float result;
    float xt;
    float xtpow;
    int sign;
    if (x > 0 && x <= 1) {
        xt = x - 1.0;
        sign = -1;
        xtpow = 1.0;
        result = 0;
        for (i = 1; i < N + 1; i++) {
            sign = sign * (-1);
            xtpow *= xt;
            result += xtpow * sign / i;
        }
    } else if (x >= 1) {
        return -1 * ln(1.0 / x);
    }
    return result;
}

double pow(double x, double n)
{
    int i; /* Variable used in loop counter */
    double number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return (number);
}

double sine(double num)
{

    int i, j;
    double sum_sin = 0;

    for (i = 0, j = 0; i < 20; i = i + 2, j++) {
        sum_sin += pow(-1, j) * pow(num, i + 1) / f(i + 1);
    }
    return sum_sin;
}

double cosine(double num)
{

    int i, j;
    double sum_cos = 1;

    for (i = 2, j = 1; i < 20; i = i + 2, j++) {
        sum_cos += pow(-1, j) * pow(num, i) / f(i);
    }
    return sum_cos;
}

int main(int argc, char* argv[])
{

    double num = get_pos_double("Enter a positive number > ", 0);

    printf("\nSquare root of a number is %lf\n", square_root(num));

    printf("Sine of a number is %lf\n", sine(num));
    printf("Cosine of a number is %lf\n", cosine(num));
    printf("ln of a number is %lf\n", ln(num));

    return 0;
}
