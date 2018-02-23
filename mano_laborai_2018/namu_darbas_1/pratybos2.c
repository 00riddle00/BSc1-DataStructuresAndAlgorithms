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

#define CHUNK_SIZE 2

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

typedef struct {
    Number** numbers;
    int size;
    int capacity;
} Table;

static Table* table;

// TODO min length = 3
// TODO use strlen and strstr
void getNumber(Number* number) {

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
        number->decimal_part[i] = (int)number->char_decimal_part[i] - '0';
    }

}

void initTable() {
    table = (Table*) malloc(sizeof(Table));
    table->capacity = CHUNK_SIZE;
    table->size = 0;
    table->numbers = malloc(CHUNK_SIZE * sizeof(Number*));
    
    for (int i = 0; i < table->capacity; i++) {
        table->numbers[i] = calloc(1, sizeof(Number));
    }
}

void saveNumber(Number* number) {
    if (table->size == table->capacity) {
        table->capacity += CHUNK_SIZE;
        table->numbers = realloc(table->numbers, table->capacity * sizeof(Number*));

        for (int i = table->size; i < table->capacity; i++) {
            table->numbers[i] = calloc(1, sizeof(Number));
        }
    }
    table->numbers[table->size] = number;
    table->size++;
}

void printTable() {

    for (int i = 0; i < table->size; i++) {
        printf("[%d] ", i);
        if (table->numbers[i]->negative) {
            printf("-");
        }

        for (int j = 0; j < table->numbers[i]->digits_whole; j++) {
            printf("%d", table->numbers[i]->whole_part[j]);
        }
        printf(".");

        for (int j = 0; j < table->numbers[i]->digits_decimal; j++) {
            printf("%d", table->numbers[i]->decimal_part[j]);
        }
        printf("\n");

    }
}



void subtract(int arg1, int arg2) {
    printf("Subtraction is performed\n");
}






// TODO siaip jau geriau kad argumentai butu patys pointeriai strukturos (oop)
void sum(int arg1, int arg2) {
    Number* bigger = table->numbers[arg1];
    Number* smaller = table->numbers[arg2];

    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number* temp = bigger;
        *bigger = *smaller;
        *smaller = *temp;
    }

    Number* res = (Number*) malloc(sizeof(Number));
    for (int i = 0; i < bigger->digits_decimal; i++) {
        res->decimal_part[i] = bigger->decimal_part[i];
    }

    res->digits_decimal = bigger->digits_decimal;

    int part;
    for (int i = smaller->digits_decimal - 1; i > 0; i--) {
        int result = res->decimal_part[i] + smaller->decimal_part[i];
        part = 0;
        if (result > 10) {
            part = 1;
            result %= 10;
        } else if (result == 10) {
            result = 0;
            part = 1;
        }
        res->decimal_part[i] = result;
        res->decimal_part[i-1] += part;
    }
    res->decimal_part[0] += smaller->decimal_part[0];

    part = 0;

    if (res->decimal_part[0] > 10) {
        part = 1;
        res->decimal_part[0] %= 10;
    } else if (res->decimal_part[0] == 10) {
        part = 1;
        res->decimal_part[0] = 0;
    }

    if (bigger->digits_whole < smaller->digits_whole) {
        Number* temp = bigger;
        *bigger = *smaller;
        *smaller = *temp;
    }
    res->digits_whole = bigger->digits_whole;

    for (int i = 0; i < bigger->digits_whole; i++) {
        res->whole_part[i] = bigger->whole_part[i];
    }
    
    for (int i = smaller->digits_whole - 1, j = 0; i >= 0; i--, j++) {
        debug("Here");
        int result = res->whole_part[res->digits_whole-1-j] + smaller->whole_part[i];
        if (j == 0) {
            res->whole_part[res->digits_whole-1] += part;
        }
        part = 0;
        if (result > 10) {
            part = 1;
            result %= 10;
        } else if (result == 10) {
            result = 0;
            part = 1;
        }
        res->whole_part[res->digits_whole-1-j] = result;
        res->whole_part[res->digits_whole-1-j-1] += part;
    }
 
    saveNumber(res);

    printf("Sum is performed\n");
}

void performAction() {
    int action, arg1, arg2;
    printf("Which action would you like to perform?\n");
    printf("[1] Sum\n");

    action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 1);

    printTable();

    printf("Select first argument (ID from the table (zero indexed))\n");
    arg1 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    printf("Select second argument (ID from the table (zero indexed))\n");
    arg2 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    sum(arg1, arg2);
}



int main(int argc, char* argv[]) {

    initTable();

    char choice;
    printf("Description\n");

    while(1) {
        printf("Enter action > ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'n':
            case 'N':;
                Number* number = (Number*) malloc(sizeof(Number));
                number->number = malloc(sizeof(char) * 1000); 
                getNumber(number);

                saveNumber(number);
                break;
            case 'p':
            case 'P':
                printTable();
                break;
            case 'a':
                performAction();
            default:
                printf("wrong action\n");
                break;
        }
    }

}

