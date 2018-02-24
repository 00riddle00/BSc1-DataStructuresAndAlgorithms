/*=============================================================================
 |
 |  Assignment:   Homework 1
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  February 23rd, 2018
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
#include <string.h>
#include <ctype.h>

#include "dbg.h"
#include "lib_riddle.h"

#define CHUNK_SIZE 2

typedef struct {
    char *number;
    // TODO define this 500
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

    for (int i = number->digits_whole - 1; i >= 0; i--) {
        number->whole_part[i] = (int)number->char_whole_part[number->digits_whole-1-i] - '0';
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




void printEntry(Number* number) {

        if (number->negative) {
            printf("-");
        }

        for (int i = number->digits_whole - 1; i >= 0; i--) {
            printf("%d", number->whole_part[i]);
        }
        printf(".");

        for (int i = 0; i < number->digits_decimal; i++) {
            printf("%d", number->decimal_part[i]);
        }
        printf("\n");
}

void printTable() {
    for (int i = 0; i < table->size; i++) {
        printf("[%d] ", i);
        printEntry(table->numbers[i]);
    }
}







int compare(int arg1, int arg2) {
    /*[return values]       [meaning]      */
    /*       1            greater than (>) */
    /*       2            less than (<)    */
    /*       3            equal to (==)    */

    Number* num1 = table->numbers[arg1];
    Number* num2 = table->numbers[arg2];

    if (num1->digits_whole > num2->digits_whole) {
        return 1;
    } else if (num1->digits_whole < num2->digits_whole) {
        return 2;
    // case for equal number of digits
    } else {
        // compare whole parts
        for (int i = num1->digits_whole-1; i >= 0; i++) {
            if (num1->whole_part[i] > num2->whole_part[i]) {
                return 1;
            } else if (num1->whole_part[i] < num2->whole_part[i]) {
                return 2;
            }
        }

        // compare decimal parts
        for (int i = 0; i < 500; i++) {
            if (num1->decimal_part[i] > num2->decimal_part[i]) {
                return 1;
            } else if (num1->decimal_part[i] < num2->decimal_part[i]) {
                return 2;
            }
        }

        return 3; // the numbers are equal
    }
}


Number* subtract(int arg1, int arg2) {
    

    int negative;
    // compare the two numbers
    int rs = compare(arg1, arg2);

    Number* first;
    Number* second;

    Number* res = (Number*) malloc(sizeof(Number));

    // if first is greater or equal, 
    // subtract second number from the first
    if (rs == 1) {
        negative = 0;

        first = table->numbers[arg1];
        second = table->numbers[arg2];

    // if first is less then second, 
    // subtract first number from the second
    } else if (rs == 2) {
        negative = 1;

        first = table->numbers[arg2];
        second = table->numbers[arg1];

    // else if numbers are equal, return zero 
    // (zeroth Number struct)
    } else if (rs == 3) {
        res->negative = 0;
        res->digits_whole = 1;
        res->digits_decimal = 1;
        res->whole_part[0] = 0;
        res->decimal_part[0] = 0;
        return res;
    }

    // set decimal digits of the result to that of number having
    // more decimal digits
    res->digits_decimal = (first->digits_decimal >= second->digits_decimal) ? first->digits_decimal : second->digits_decimal;

    // copy decimal digits to the result
    for (int i = 0; i < res->digits_decimal; i++) {
        res->decimal_part[i] = first->decimal_part[i];
    }

    // set whole digits of the result to that the bigger number's 
    res->digits_whole = first->digits_whole;
    for (int i = 0; i < res->digits_whole; i++) {
        res->whole_part[i] = first->whole_part[i];
    }

    // set the sign of the result
    res->negative = negative;

    
    /* actual subraction starts   */
    
    // subtract decimal digits
    for (int i = res->digits_decimal - 1; i >= 0; i--) {
        int result = res->decimal_part[i] - second->decimal_part[i];
        if (result < 0) {

            if (i == 0) {
                // borrow the ten (10) from the whole part
                // in case the whole part's number becomes -1,
                // this is then handled when substracting whole digits
                res->decimal_part[i] = result + 10;
                res->whole_part[0]--;
                break;
            }

            // go through the remaining numbers to borrow the needed 
            // ten exponent (10) for subtraction
            for (int j = i-1; j >= 0; j--) {
                res->decimal_part[j] = (res->decimal_part[j] == 0) ? 9 : res->decimal_part[j] - 1; 
                if (res->decimal_part[j] == 9) {
                    if (j == 0) {
                        // borrow the ten (10) from the whole part
                        // in case the whole part's number becomes -1,
                        // this is then handled when substracting whole digits
                        res->whole_part[0]--;
                    }
                    continue;
                } else {
                    break;
                }
            }
            res->decimal_part[i] = result + 10;
        } else {
            res->decimal_part[i] = result;
        }
    }

    // subtract whole digits
    for (int i = 0; i < second->digits_whole; i++) {
        int result = res->whole_part[i] - second->whole_part[i];

        if (result < 0) {

            for (int j = i+1; j < res->digits_whole; j++) {
                res->whole_part[j] = (res->whole_part[j] == 0) ? 9 : res->whole_part[j] - 1;
                if (res->whole_part[j] == 9) {
                    continue;
                } else {
                    break;
                }
            }
            res->whole_part[i] = (result + 10) % 10;
        } else {
            res->whole_part[i] = result;
        }
    }

    // remove zeroes in front of the actual resulting number (if there are any)
    for (int i = res->digits_whole - 1, zeros = 0; i >= 0; i--) {
        if (res->whole_part[i] == 0) {
            zeros++;
        } else {
            res->digits_whole -= zeros;
            break;
        }
    }
    return res;
}




// TODO make arguments to be ponters to a Number struct
Number* add(int arg1, int arg2, int negative) {
    Number* bigger = table->numbers[arg1];
    Number* smaller = table->numbers[arg2];

    // TODO change to swap 
    if (bigger->digits_decimal < smaller->digits_decimal) {
        bigger = table->numbers[arg2];
        smaller = table->numbers[arg1];
    }

    // create result Number and populate it with decimal digits 
    // of the bigger number
    Number* res = (Number*) malloc(sizeof(Number));
    for (int i = 0; i < bigger->digits_decimal; i++) {
        res->decimal_part[i] = bigger->decimal_part[i];
    }
    res->digits_decimal = bigger->digits_decimal;

    // part - the part to be transfered to the next sum. 
    //  Ex. 9+5 = 14, 1 then becomes the "part" to be transfered next.
    int part;

    // add decimal parts
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

    // part then moves on to be added to the whole part of the number
    if (res->decimal_part[0] >= 10) {
        part = 1;
        res->decimal_part[0] %= 10;
    } 

    // select number with bigger amount of whole part digits
    if (bigger->digits_whole < smaller->digits_whole) {
        Number* temp = bigger;
        *bigger = *smaller;
        *smaller = *temp;
    }

    // copy whole_part to the result struct
    res->digits_whole = bigger->digits_whole;

    for (int i = 0; i < bigger->digits_whole; i++) {
        res->whole_part[i] = bigger->whole_part[i];
    }


    // add whole parts
    for (int i = 0; i < smaller->digits_whole; i++) {
        int result = res->whole_part[i] + smaller->whole_part[i];
        if (i == 0) {
            result += part;
        }
        part = 0;
        if (result >= 10) {
            part = 1;
            result %= 10;
        }
        res->whole_part[i] = result;
        res->whole_part[i+1] += part;
    }
 
    // set sign
    res->negative = negative;

    return res;
}


Number* multiply(int arg1, int arg2) {
    printf("Multiplication is conducted\n");
    Number* num1 = table->numbers[arg1];
    Number* num2 = table->numbers[arg2];

    Number* res = (Number*) malloc(sizeof(Number));
    res->digits_whole = num1->digits_whole + num2->digits_whole;

    Number* res2 = (Number*) malloc(sizeof(Number));
    res2->digits_whole = num1->digits_whole + num2->digits_whole;

    int a[num2->digits_whole][res->digits_whole];
    /*memset(a, 0, sizeof a);*/
    memset(a, 0, sizeof(a[0][0]) * num2->digits_whole * res->digits_whole);

    debug("here--");

    /*for (int i = 0; i < num2->digits_whole; i++) {*/
        /*for (int j = 0; j < res->digits_whole; j++) {*/
            /*a[i][j] = 0;*/
        /*}*/
    /*}*/

    for (int i = 0; i < 4; i++) {
        printf("%d", a[0][i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%d", a[1][i]);
    }
    printf("\n");

    int part = 0;
    int rc;
    int pos = 0;

    for (int i = 0; i < num2->digits_whole; i++) {
        pos = i;
        for (int j = 0; j < num1->digits_whole; j++) {
            rc = num2->whole_part[i] * num1->whole_part[j];
            a[i][j+pos] = rc % 10 + part;
            /*debug("i = %d, j = %d, a[i][j] = %d", i, j, a[i][j]);*/
            part = rc / 10;
        }
        // FIXME if part == 0 error
        a[i][num1->digits_whole+pos] = part;
        part = 0;
    }

    int result = 0;
    part = 0;
    int initial_result = 0;

    for (int j = 0; j < res->digits_whole; j++) {
        for (int i = 0; i < num2->digits_whole; i++) {
            result += a[i][j];
        }
        debug("Result is %d", result);

        initial_result = result;
        result %= 10;
        debug("Result2 is %d", result);
        res->whole_part[j] = result + part;
        part = initial_result / 10;
        result = 0;
    }

    printEntry(res);

    debug("here--");

    for (int i = 0; i < 4; i++) {
        printf("%d", a[0][i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%d", a[1][i]);
    }
    printf("\n");

    return res;

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

    // TODO move to sum argparse function
    action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 6);

    printTable();

    printf("Select first argument (ID from the table (zero indexed))\n");
    arg1 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    printf("Select second argument (ID from the table (zero indexed))\n");
    arg2 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    int x = table->numbers[arg1]->negative;
    int y = table->numbers[arg2]->negative;
    int cmp;

    // both numbers positive
    if (!x && !y) {
        cmp = compare(arg1, arg2);
    // both numbers negative
    } else if (x && y) {
        cmp = compare(arg2, arg1);
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

    // TODO move to sum argparse function
    action = get_num_interval("(Enter a number) > ", "Such option does not exist", 1, 5);

    printTable();

    printf("Select first argument (ID from the table (zero indexed))\n");
    arg1 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    printf("Select second argument (ID from the table (zero indexed))\n");
    arg2 = get_num_interval("(Enter a number) > ", "Such ID does not exist", 0, table->size - 1);

    int x = table->numbers[arg1]->negative;
    int y = table->numbers[arg2]->negative;
    // result
    Number* res;

    // case addition
    if (action == 1) {
        // both numbers positive
        if (!x && !y) {
            res = add(arg1, arg2, 0);
        // both numbers negative
        } else if (x && y) {
            res = add(arg1, arg2, 1);
        // first number is positive, second - negative
        } else if (x && !y) {
            res = subtract(arg1, arg2);
        // first number is negative, second - positive
        } else if (!x && y) {
            res = subtract(arg2, arg1);
        }
    }
    // case subtraction
    if (action == 2) {
        // both numbers positive
        if (!x && !y) {
            res = subtract(arg1, arg2);
        // both numbers negative
        } else if (x && y) {
            res = subtract(arg2, arg1);
        // first number is positive, second - negative
        } else if (x && !y) {
            res = add(arg1, arg2, 0);
        // first number is negative, second - positive
        } else if (!x && y) {
            res = add(arg1, arg2, 1);
        }
    }

    if (action == 3) {
        res = multiply(arg1, arg2);

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
    }

    printf("The result is:\n");
    printEntry(res);
    
    if (choice("Would you like to save it?")) {
        saveNumber(res);
    }
}



int main(int argc, char* argv[]) {

    // initialize table structure holding numbers
    initTable();

    char choice;
    printf("Description\n");

    // ask for user input and process it
    while(1) {
        printf("Enter action> ");
        scanf(" %c", &choice);

        switch (choice) {
            // new number
            case 'n':
            case 'N':;
                Number* number = (Number*) malloc(sizeof(Number));
                number->number = malloc(sizeof(char) * 1000); 
                getNumber(number);

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
            default:
                printf("wrong action\n");
                break;
        }
    }
    return 0;
}

