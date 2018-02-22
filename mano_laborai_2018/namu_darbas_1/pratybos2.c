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
    char *number;
    char char_whole_part[500];
    char char_decimal_part[500];
    int whole_part[500];
    int decimal_part[500];
    int digits_whole;
    int digits_decimal;
    int negative;
} Number;


int main(int argc, char* argv[]) {

    Number* number = (Number*) malloc(sizeof(Number));
    number->number = malloc(sizeof(char) * 1000); 

    number->number = get_word("Enter a number (separate whole and decimal parts using \".\" symbol)\n > ", number->number);

    int count = 0;
    int error = 0;
    int decimal_pos = 0;

    int start = 0;
    int is_decimal_part = 0;

    number->negative = 0;

    if (number->number[0] == '-') {
        number->negative = 1;
        start++;
        debug("Start %d", start);
    } 

    // TODO move to separate function
    for (int i = start; i < 1000; i++) {

        if(!isdigit(number->number[i])) {
            if (number->number[i] == '.') {
                strncpy(number->char_whole_part, number->number+number->negative, count);
                number->digits_whole = count;
                decimal_pos = count;
                count = 0;
                is_decimal_part = 1;
            } else if (number->number[i] == 0) {
                if (is_decimal_part) {
                    strncpy(number->char_decimal_part, number->number+decimal_pos+number->negative+1, count);
                    number->digits_decimal = count;
                    break;
                } else {
                    strncpy(number->char_whole_part, number->number+number->negative, count);
                    number->digits_whole = count;
                    decimal_pos = count;
                    number->digits_decimal = 0;
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

    for (int i = 0; i < number->digits_whole; i++) {
        number->whole_part[i] = (int)number->char_whole_part[i] - '0';
    }

    for (int i = 0; i < number->digits_decimal; i++) {
        number->decimal_part[i] = number->char_decimal_part[i] - '0';
    }

    printf("Whole part is: \n");
    for (int i = 0; i < number->digits_whole; i++) {
        printf("%d", number->whole_part[i]);
    }
    printf("\n");

    printf("Decimal part is: \n");
    for (int i = 0; i < number->digits_decimal; i++) {
        printf("%d", number->decimal_part[i]);
    }
    printf("\n");

}

