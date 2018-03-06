/*=============================================================================
 | Program for testing Big Numbers ADT with the help of user input
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Header file with useful debugging macros
#include "dbg.h"

#include "helpers.h"
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

// TODO add description
int getNumberIndex();



int main() {

    // initialize table structure holding numbers
    initTable();

    atexit(freeTable);

    char choice;

    char* separator = (char*) "------------------------------------------------------";

    char* about = (char*) "This is a program to test the ADT used for working with very large/very small numbers. The user can"
        "set numbers, perform arithmethic and comparison operations with them. The numbers are saved in a table, which"
        "can also be viewed at any time. The program does not save the data after its completion";

    char* info = (char*) "Usage: in the main shell, input the Action[1].[1] Action - n = set new number, p = print table,"
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
                getNumberChar((char*)"Enter a number (separate whole and decimal parts using \".\" symbol)\n > ", numArray);
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
    int action, id1, id2;
    printf("Which comparison would you like to perform?\n");
    printf("[1] Equal to (==)\n");
    printf("[2] Not equal to (==)\n");
    printf("[3] Greater than (>)\n");
    printf("[4] Less than (<)\n");
    printf("[5] Greater than or equal to (>=)\n");
    printf("[6] Less than or equal to (<=)\n");

    action = get_num_interval((char*)"(Enter a number) > ", (char*)"Such option does not exist", 1, 6);

    printTable();

    id1 = getNumberIndex();
    id2 = getNumberIndex();

    Number* num1 = table->numbers[id1];
    Number* num2 = table->numbers[id2];

    int cmp;

    switch (action) {
        case 1:
            cmp = compareEqual(num1, num2);
            break;
        case 2:
            cmp = compareNotEqual(num1, num2);
            break;
        case 3:
            cmp = compareGreaterThan(num1, num2);
            break;
        case 4:
            cmp = compareLessThan(num1, num2);
            break;
        case 5:
            cmp = compareGreaterThanOrEqual(num1, num2);
            break;
        case 6:
            cmp = compareLessThanOrEqual(num1, num2);
            break;
        default:
            printf("Wrong action\n");
            break;
    }
    if (cmp) {
        printf("True\n");
    } else {
        printf("False\n");
    }
 
}

void performMath() {
    int action, id1, id2;
    printf("Which action would you like to perform?\n");
    printf("[1] Addition\n");
    printf("[2] Subtraction\n");
    printf("[3] Multiplication\n");
    printf("[4] Division\n");
    printf("[5] Modulo\n");

    action = get_num_interval((char*)"(Enter a number) > ", (char*)"Such option does not exist", 1, 5);

    printTable();

    id1 = getNumberIndex();
    id2 = getNumberIndex();

    Number* num1 = table->numbers[id1];
    Number* num2 = table->numbers[id2];

    // result
    Number* res;

    switch(action) {
        // case addition
        case 1:
            res = addNumbers(num1, num2);
            break;
        // case subtraction
        case 2:
            res = subtractNumbers(num1, num2);
            break;
        case 3:
            res = multiplyNumbers(num1, num2);
            break;
        case 4:
            res = divideNumbers(num1, num2);
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

int getNumberIndex() {

    printf("Select first argument (ID from the table (zero indexed))\n");
    return get_num_interval((char*)"(Enter a number) > ", (char*)"Such ID does not exist", 0, table->size - 1);
}

