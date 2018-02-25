/*=============================================================================
 | Main program for testing Big Numbers ADT
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Header file with useful debugging macros
#include "dbg.h"
// Custom library with various helper functions
#include "lib_riddle.h"
#include "numbers.h"

/* action functions */

// prompt the user to enter two numbers (from the table),
// and conduct comparison operation, printing the answer 
// to standard output
void compareNumbers();

// prompt the user to enter two numbers (from the table) 
// and perform Math operations, printing the result to
// the standard output. Prompt the user whether to save
// the result to the table
void performMath();


int main() {

    // initialize table structure holding numbers
    initTable();

    char choice;

    char* separator = ("------------------------------------------------------");

    char* about = "This is a program to test the ADT used for working with very large/very small numbers. The user can"
        "set numbers, perform arithmethic and comparison operations with them. The numbers are saved in a table, which"
        "can also be viewed at any time. The program does not save the data after its completion";

    char* info = "Usage: in the main shell, input the Action[1].[1] Action - n = set new number, p = print table,"
        "m = perform math, c = compare numbers, i = print information. When prompted, enter the ID[2] of the number "
        "from the table. [2] ID - a non-negative integer, chosen from the entries in the table.";

    printf("%s\n", separator);
    printf("%s\n", about);
    printf("%s\n", separator);
    printf("%s\n\n", info);

    // ask for user input and process it
    while(1) {
        printf("[Enter \"i\" for info] Enter action> ");
        scanf(" %c", &choice);

        switch (choice) {
            // new number
            case 'n':
            case 'N':;
                char numArray[DIGITS*2];
                getNumberChar("Enter a number (separate whole and decimal parts using \".\" symbol)\n > ", numArray);
                Number* number;
                number = setNumberFromChar(numArray);
                saveNumber(number);
                break;
            // print existing table
            case 'p':
            case 'P':
                printTable();
                break;
            // perform action
            case 'm':
            case 'M':
                performMath();
                break;
            case 'c':
            case 'C':
                compareNumbers();
                break;
            case 'i':
            case 'I':
                printf("\n%s\n\n", info);
                break;
            default:
                printf("wrong action\n");
                break;
        }
    }
    return 0;
}


void compareNumbers() {
    int action, arg1, arg2;
    printf("Which comparison would you like to perform?\n");
    printf("[1] Equal to (==)\n");
    printf("[2] Not equal to (==)\n");
    printf("[3] Greater than (>)\n");
    printf("[4] Less than (<)\n");
    printf("[5] Greater than or equal to (>=)\n");
    printf("[6] Less than or equal to (<=)\n");

    action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 6);

    printTable();

    printf("Select first argument (ID from the table (zero indexed))\n");
    arg1 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    printf("Select second argument (ID from the table (zero indexed))\n");
    arg2 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    Number* num1 = table->numbers[arg1];
    Number* num2 = table->numbers[arg2];

    int x = num1->negative;
    int y = num2->negative;

    int cmp;

    // both numbers positive
    if (!x && !y) {
        cmp = compare(num1, num2);
    // both numbers negative
    } else if (x && y) {
        cmp = compare(num2, num1);
    // first number is positive, second - negative
    } else if (x && !y) {
        // greater than
        cmp = 1;
    // first number is negative, second - positive
    } else if (!x && y) {
        // less than
        cmp = 2;
    }

    switch (action) {
        case 1:
            if (cmp == 3) {
                printf("True");
            } else {
                printf("False");
            }
            break;
        case 2:
            if (cmp == 3) {
                printf("False");
            } else {
                printf("True");
            }
            break;
        case 3:
            if (cmp == 1) {
                printf("True");
            } else {
                printf("False");
            }
            break;
        case 4:
            if (cmp == 2) {
                printf("True");
            } else {
                printf("False");
            }
            break;
        case 5:
            if (cmp == 2) {
                printf("False");
            } else {
                printf("True");
            }
            break;
        case 6:
            if (cmp == 1) {
                printf("False");
            } else {
                printf("True");
            }
            break;
        default:
            printf("Wrong action\n");
            break;
    }
    printf("\n");
 
}

void performMath() {
    int action, arg1, arg2;
    printf("Which action would you like to perform?\n");
    printf("[1] Addition\n");
    printf("[2] Subtraction\n");
    printf("[3] Multiplication\n");
    printf("[4] Division\n");
    printf("[5] Modulo\n");

    action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 5);

    printTable();

    printf("Select first argument (ID from the table (zero indexed))\n");
    arg1 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    printf("Select second argument (ID from the table (zero indexed))\n");
    arg2 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    Number* num1 = table->numbers[arg1];
    Number* num2 = table->numbers[arg2];

    int x = num1->negative;
    int y = num2->negative;

    // result
    Number* res;

    switch(action) {
        // case addition
        case 1:
            // both numbers positive
            if (!x && !y) {
                res = add(num1, num2, 0);
            // both numbers negative
            } else if (x && y) {
                res = add(num1, num2, 1);
            // first number is positive, second - negative
            } else if (!x && y) {
                res = subtract(num1, num2);
            // first number is negative, second - positive
            } else if (x && !y) {
                res = subtract(num1, num2);
            }
            break;
        // case subtraction
        case 2:
            // both numbers positive
            if (!x && !y) {
                res = subtract(num1, num2);
            // both numbers negative
            } else if (x && y) {
                res = subtract(num1, num2);
            // first number is positive, second - negative
            } else if (!x && y) {
                res = add(num1, num2, 0);
            // first number is negative, second - positive
            } else if (x && !y) {
                res = add(num1, num2, 1);
            }
            break;
        case 3:
            res = multiply(num1, num2);

            // both numbers positive
            if (!x && !y) {
                res->negative = 0;
            // both numbers negative
            } else if (x && y) {
                res->negative = 0;
            // one number is positive, another - negative
            } else {
                res->negative = 1;
            }
            break;
        case 4:
            res = divide(num1, num2);

            // both numbers positive
            if (!x && !y) {
                res->negative = 0;
            // both numbers negative
            } else if (x && y) {
                res->negative = 0;
            // one number is positive, another - negative
            } else {
                res->negative = 1;
            }
            break;
        case 5:
            /*res = modulo(num1, num2);*/
            break;
        default:
            printf("Such action does not exist\n");
            break;
    }

    printf("The result is:\n");
    printEntry(res);
    
    if (choice("Would you like to save it?")) {
        saveNumber(res);
    }
}

