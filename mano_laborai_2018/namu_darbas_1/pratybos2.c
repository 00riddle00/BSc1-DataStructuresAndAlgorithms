/*=============================================================================
 |
 |  Assignment:   Exercise 2
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  December 13th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -g -lm -std=c11 pratybos2.c -o pratybos2
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  
 |                
 |                
 |                
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |                
 |                
 |              
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dbg.h"
#include "lib_riddle.h"

typedef struct {
    int whole_part[500];
    int decimal_part[500];
    int digits_whole;
    int digits_decimal;
    int negative;
} Number;

typedef struct {
    char *number;
    char whole_part[500];
    char decimal_part[500];
    int digits_whole;
    int digits_decimal;
    int negative;
} NumberInChar;


int main(int argc, char* argv[]) {

    NumberInChar* numberInChar = (NumberInChar*) malloc(sizeof(NumberInChar));
    numberInChar->number = malloc(sizeof(char) * 1000); 

    numberInChar->number = get_word("Enter a number (separate whole and decimal parts using \".\" symbol)\n > ", numberInChar->number);

    int count = 0;
    int error = 0;
    int decimal_pos = 0;

    int start = 0;
    int is_decimal_part = 0;

    numberInChar->negative = 0;

    if (numberInChar->number[0] == '-') {
        numberInChar->negative = 1;
        start++;
        debug("Start %d", start);
    } 

    // TODO move to separate function
    for (int i = start; i < 1000; i++) {

        if(!isdigit(numberInChar->number[i])) {
            if (numberInChar->number[i] == '.') {
                strncpy(numberInChar->whole_part, numberInChar->number+numberInChar->negative, count);
                numberInChar->digits_whole = count;
                decimal_pos = count;
                count = 0;
                is_decimal_part = 1;
            } else if (numberInChar->number[i] == 0) {
                if (is_decimal_part) {
                    strncpy(numberInChar->decimal_part, numberInChar->number+decimal_pos+numberInChar->negative+1, count);
                    numberInChar->digits_decimal = count;
                    break;
                } else {
                    strncpy(numberInChar->whole_part, numberInChar->number+numberInChar->negative, count);
                    numberInChar->digits_whole = count;
                    decimal_pos = count;
                    numberInChar->digits_decimal = 0;
                }

            } else {
                error = 1;
                break;
            }
        } else {
            count++;
        }
    }

    if(error) {
        printf("Invalid number\n");
    }

/*    debug("%s", numberInChar->whole_part);*/
    /*debug("%d", numberInChar->digits_whole);*/
    /*debug("%s", numberInChar->decimal_part);*/
    /*debug("%d", numberInChar->digits_decimal);*/
    /*debug("%d", numberInChar->negative);*/
    /*debug("-------------------------------");*/

    Number* number = (Number*) malloc(sizeof(Number));

    number->digits_whole = numberInChar->digits_whole;
    number->digits_decimal = numberInChar->digits_decimal;
    number->negative = numberInChar->negative;

    for (int i = 0; i < numberInChar->digits_whole; i++) {
        number->whole_part[i] = (int)numberInChar->whole_part[i] - '0';
    }

    for (int i = 0; i < numberInChar->digits_decimal; i++) {
        number->decimal_part[i] = numberInChar->decimal_part[i] - '0';
    }

    printf("Whole part is: \n");
    for (int i = 0; i < numberInChar->digits_whole; i++) {
        printf("%d", number->whole_part[i]);
    }
    printf("\n");

    printf("Decimal part is: \n");
    for (int i = 0; i < numberInChar->digits_decimal; i++) {
        printf("%d", number->decimal_part[i]);
    }
    printf("\n");

}

