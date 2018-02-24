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

int isZero(Number* num) {
    return num->digits_whole == 1 && num->digits_decimal == 1 && num->whole_part[0] == 0 && num->decimal_part[0] == 0;
}


// this comparison function ignores the sign of the numbers,
// thus it compares the absolute values of the two numbers.
int compare(Number* num1, Number* num2) {
    /*[return values]       [meaning]      */
    /*       1            greater than (>) */
    /*       2            less than (<)    */
    /*       3            equal to (==)    */

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


Number* subtract(Number* num1, Number* num2) {

    int negative;
    // compare the two numbers
    int rs = compare(num1, num2);
    debug("rs = %d", rs);

    Number* first;
    Number* second;

    Number* res = (Number*) malloc(sizeof(Number));

    // if first is greater or equal, 
    // subtract second number from the first
    if (rs == 1) {
        negative = 0;

        first = num1;
        second = num2;

    // if first is less than second, 
    // subtract first number from the second
    } else if (rs == 2) {
        negative = 1;

        first = num2;
        second = num1;

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

    int zeros = 0;
    // TODO add this refactored piece of code to every place it is used
    // remove zeroes in front of the actual resulting number (if there are any)
    for (int i = res->digits_whole - 1; i >= 0; i--) {
        debug("HHHHHHHHHHHHHHHHHHHHHHHHHHHHH");
        if (res->whole_part[i] == 0) {
            zeros++;
            debug("zeros++");
        } else {
            res->digits_whole -= zeros;
            break;
        }
    }
    res->digits_whole -= zeros;

    // TODO add this nullifier everywhere
    if (res->digits_whole == 0 && res->digits_decimal == 0) {
        res->digits_whole = 1;
        res->digits_decimal = 1;
        res->whole_part[0] = 0;
        res->decimal_part[0] = 0;
    }



    debug("ENTRY ENTRY");
    printEntry(res);
    return res;
}




// TODO make arguments to be ponters to a Number struct
Number* add(Number* num1, Number* num2, int negative) {
    Number* bigger = num1;
    Number* smaller = num2;

    // TODO change to swap 
    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
    }
    printEntry(smaller);

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

    debug("111");
    printEntry(res);

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


    debug("222");
    printEntry(res);


    debug("I dont need ");
    printEntry(bigger);
    printEntry(smaller);

    // select number with bigger amount of whole part digits
    if (bigger->digits_whole < smaller->digits_whole) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
    }

    debug("I dont need ");
    printEntry(bigger);
    printEntry(smaller);

    // copy whole_part to the result struct
    res->digits_whole = bigger->digits_whole + 1;

    for (int i = 0; i < bigger->digits_whole; i++) {
        res->whole_part[i] = bigger->whole_part[i];
    }

    debug("wish you were here");
    printEntry(res);
    printEntry(smaller);


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

    // remove zeroes in the front of the resulting number
    for (int i = res->digits_whole-1; i >= 0; i--) {
        if (res->whole_part[i] == 0) {
            res->digits_whole--;
        } else {
            break;
        }
    }

    // set sign
    res->negative = negative;

    return res;
}


Number* multiply(Number* num1, Number* num2) {
    printf("Multiplication is conducted\n");

    Number* res = (Number*) malloc(sizeof(Number));
    res->digits_whole = num1->digits_whole + num1->digits_decimal + num2->digits_whole + num2->digits_decimal;

    int a[num2->digits_whole+num2->digits_decimal][res->digits_whole];
    /*memset(a, 0, sizeof a);*/
    memset(a, 0, sizeof(a[0][0]) * (num2->digits_whole+num2->digits_decimal) * res->digits_whole);

    debug("here--");


    /*for (int i = 0; i < 4; i++) {*/
        /*printf("%d", a[0][i]);*/
    /*}*/
    /*printf("\n");*/

    /*for (int i = 0; i < 4; i++) {*/
        /*printf("%d", a[1][i]);*/
    /*}*/
    /*printf("\n");*/

    // populate first factor with both decimal and whole parts of the first
    // number (convert decimal part to whole part) - ie move decimal dot(.) to 
    // the end of the number, or multiply it by 10^n, where n is the number of 
    // decimal digits (digits after the dot).
    Number* n1 = (Number*) malloc(sizeof(Number));

    for (int i = num1->digits_decimal - 1, j = 0; i >= 0; i--, j++) {
        n1->whole_part[j] = num1->decimal_part[i];
        n1->digits_whole++;
    }
    for (int i = 0; i < num1->digits_whole; i++) {
        n1->whole_part[i+num1->digits_decimal] = num1->whole_part[i];
        n1->digits_whole++;
    }

    debug("print");
    printEntry(n1);

    // TODO if no decimal part, do not copy
    // TODO define clear constraints, ex. max 250 digits or so
    // populate second factor with both decimal and whole parts of the second
    // number (convert decimal part to whole part) - ie move decimal dot(.) to 
    // the end of the number, or multiply it by 10^n, where n is the number of 
    // decimal digits (digits after the dot).
    Number* n2 = (Number*) malloc(sizeof(Number));

    for (int i = num2->digits_decimal - 1, j = 0; i >= 0; i--, j++) {
        n2->whole_part[j] = num2->decimal_part[i];
        n2->digits_whole++;
    }
    for (int i = 0; i < num2->digits_whole; i++) {
        n2->whole_part[i+num2->digits_decimal] = num2->whole_part[i];
        n2->digits_whole++;
    }

    debug("print");
    printEntry(n2);

    int decimal_numbers = num1->digits_decimal + num2->digits_decimal;

    int part = 0;
    int rc;
    int pos = 0;

    for (int i = 0; i < n2->digits_whole; i++) {
        pos = i;
        for (int j = 0; j < n1->digits_whole; j++) {
            rc = n2->whole_part[i] * n1->whole_part[j];
            a[i][j+pos] = (rc + part) % 10; 
            part = (rc+part) / 10;
        }
        // FIXME if part == 0 error
        a[i][n1->digits_whole+pos] = part;
        part = 0;
    }

    for (int i = 0; i < 10; i++) {
        /*printf("i = %d\n", a[0][i]);*/
        printf("%d", a[0][i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d", a[1][i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d", a[2][i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d", a[3][i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d", a[4][i]);
    }
    printf("\n");

    int result = 0;
    part = 0;
    int initial_result = 0;

    for (int j = 0; j < res->digits_whole; j++) {
        for (int i = 0; i < n2->digits_whole; i++) {
            result += a[i][j];
        }
        debug("Part is %d", part);
        debug("Result is %d", result);

        result += part;
        part = result / 10;
        res->whole_part[j] = result % 10;
        result = 0;
    }

    printEntry(res);

    debug("here--");
    
    // remove zeroes in the front of the resulting number
    for (int i = res->digits_whole-1; i >= 0; i--) {
        if (res->whole_part[i] == 0) {
            res->digits_whole--;
        } else {
            break;
        }
    }


/*    for (int i = 0; i < 8; i++) {*/
        /*printf("%d", a[0][i]);*/
    /*}*/
    /*printf("\n");*/

    /*for (int i = 0; i < 8; i++) {*/
        /*printf("%d", a[1][i]);*/
    /*}*/
    /*printf("\n");*/

    /*for (int i = 0; i < 8; i++) {*/
        /*printf("%d", a[2][i]);*/
    /*}*/
    /*printf("\n");*/

    /*for (int i = 0; i < 8; i++) {*/
        /*printf("%d", a[3][i]);*/
    /*}*/
    /*printf("\n");*/


    // move decimal dot to the required place
    // ie convert whole number to a decimal number again
    res->digits_decimal = decimal_numbers;
    for (int i = 0; i < decimal_numbers; i++) {
        res->decimal_part[i] = res->whole_part[decimal_numbers-1-i];
    }

    debug("hre");
    printEntry(res);

    for (int i = 0; i < res->digits_whole; i++) {
        res->whole_part[i] = res->whole_part[decimal_numbers+i];
    }
    res->digits_whole -= decimal_numbers;


    debug("hre2");
    printEntry(res);

    for (int i = 0; i < res->digits_whole; i++) {
        printf("%d  ", res->whole_part[i]);
    }

    return res;

}


Number* divide(Number* num1, Number* num2) {
    printf("Division is conducted\n");

    Number* res = (Number*) malloc(sizeof(Number));
    int rs = compare(num1, num2);
    int quotient;

    // if first is greater or equal, the quotient will 
    // be greater than 1
    if (rs == 1) {
        debug("quotient one");
        quotient = 1;
    // if first is less than second, 
    // the quotient will be less than 1
    } else if (rs == 2) {
        quotient = 0;
    // else if numbers are equal, return one 
    // (Number struct with the value of one)
    } else if (rs == 3) {
        debug("what??");
        res->negative = 0;
        res->digits_whole = 1;
        res->digits_decimal = 1;
        res->whole_part[0] = 1;
        res->decimal_part[0] = 0;
        return res;
    }

    res->digits_whole = 1;
    res->digits_decimal = 1;
    res->whole_part[0] = 0;
    res->decimal_part[0] = 0;

    Number* one = (Number*) malloc(sizeof(Number));
    one->digits_whole = 1;
    one->digits_decimal = 1;
    one->whole_part[0] = 1;
    one->decimal_part[0] = 0;


    Number* tmp;

    int counter = 0;

    tmp = num1;

    while (quotient == 1) {
        tmp = subtract(tmp, num2);
        debug("tmp is:");
        printEntry(tmp);
        debug("digits whole: %d", tmp->digits_whole);
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !tmp->negative) {
            res = add(res, one, 0);
        } else if (isZero(tmp)) {
            debug("IS ZERO!");
            res = add(res, one, 0);
            break;
        } else {
            break;
        }
    }







    debug("hello from the other side");
    printEntry(res);

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

    // TODO move to sum argparse function
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

    debug("%d", x);
    debug("%d", y);
    // result
    Number* res;

    // TODO use switch statement instead
    // case addition
    if (action == 1) {
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
    }
    // case subtraction
    if (action == 2) {
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
    }

    if (action == 3) {
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
    }


    if (action == 4) {
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

