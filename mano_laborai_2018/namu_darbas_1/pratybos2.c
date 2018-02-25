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
 +-----------------------------------------------------------------------------
 |
 |  Description: C/C++ languages do not have numerical data types which let
 |               save many digits and work with them comfortably. Standard
 |               integer and real number types are not enough to work with
 |               very large or very small numbers. Hence the aim of this 
 |               module is to create an effective ADT which would allow
 |               working with large real numbers with great precision.
 |               The main structure is struct Number, which saves the
 |               real number divided into whole and decimal parts.
 |               A char array containing the number can be converted into
 |               a Number structure, and vice a versa.
 |               Standard arithmetical operations are defined also.
 |               Sum and subtraction are performed in a vertical column
 |               manner, mulitplication and division are performed in a 
 |               long (multiplication/division) way.
 |               Assignment operation is defined also (deep copy). 
 |               Standard comparison operators are also defined.
 |               Both comparison and arithmetic is performed using
 |               functions, since there is no possibility to overload
 |               operators in C.
 |
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 |    Known bugs: [1] Division seems to not work in certain cases.
 |                [2] Division returns the result of max 35 digits. If division
 |                is continued after that, the program seems to stop working. 
 |                Temporary if condition guard is placed now, not letting the 
 |                resulting quotient to be more than 35 digits.
 |                
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Header file with useful debugging macros
#include "dbg.h"
// Custom library with various helper functions
#include "lib_riddle.h"

// This value is used in dynamic array containing
// Number structures
#define CHUNK_SIZE 5
// How many digits to store a whole part of the number
// as well as the decimal part, ie whole_part[DIGITS] 
// and decimal_part[DIGITS]
#define DIGITS 500
#define TEN "10.0"
#define ONE "1.0"
#define ZERO_ONE "0.1"

// Main structure, Number data type (BigNum)
// Contains char arrays for whole and decimal parts,
// in case the number was given by a user via command line,
// and int arrays for actual number storage, as well
// as other parameters describing the number.
typedef struct {
    int whole_part[DIGITS];
    int decimal_part[DIGITS];
    int digits_whole;
    int digits_decimal;
    int negative;
} Number;

// Table structure contains dynamic array of 
// numbers. Used as a quosi-database for Number 
// data type.
typedef struct {
    Number** numbers;
    int size;
    int capacity;
} Table;

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

/* table operation functions */

// initialize table
// set table size, capacity, allocate memory
// of the CHUNK_SIZE
void initTable();

// save number to the table
void saveNumber(Number* number);

// print number
void printEntry(Number* number);

// print whole table
void printTable();

// convert Number struct to char array
// ::params:: the Number to be converted
// ::return:: resulting char array
char* numToChar(Number* number);

/* function to write a given number from user input */

// to char array
// ::params:: message - the prompt message
// ::params:: output - the resulting char array
void getNumberChar(char* message, char* output);

/* functions working with Number structure (might be Number class methods in C++) */

// set a new number
// ::return:: a Number initialized to zero
Number* setNewNumber();

// set a number from char arry
// ::params:: numArray - given char array
// ::return::  a Number parsed from the char array
Number* setNumberFromChar(char* numArray);

// set a number from long double
// ::params:: number - number in long double format
// ::params:: whole_digits - how many whole digits a number has
// ::params:: decimal_digits - how many decimal digits a number has
// ::return::  a resulting Number
Number* setNumberFromDouble(long double number, int whole_digits, int decimal_digits);

// assign one number (might be existing already with a certain value)
// to another
// ::params:: num1 - Number struct to which assignment is made
// ::params:: num2 - Number to be assigned
void assign(Number* num1, Number* num2);

// fix zeroes in the number, ie if the number has no whole or 
// decimal part, set it to zero. Else, remove zeroes at the front
// of the whole part and at the back of the decimal part
// ::params:: num - Number to be fixed
void fixNumber(Number* num);

// check if a Number struct has a value of zero (0.0)
// ::params:: num - Number to be checked
int isZero(Number* num);

// compare two numbers
// ::params:: num1 - first number
// ::params:: num2 - second number
/*[return values]       [meaning]      */
/*       1            greater than (>) */
/*       2            less than (<)    */
/*       3            equal to (==)    */
int compare(Number* num1, Number* num2);

// add two numbers
// ::params:: num1 - first number
// ::params:: num2 - second number
// ::params:: negative - whether result should be negative
// ::return::  a resulting Number
Number* add(Number* num1, Number* num2, int negative);

// subtract two numbers
// ::params:: num1 - first number
// ::params:: num2 - second number
// ::return::  a resulting Number
Number* subtract(Number* num1, Number* num2);

// multiply two numbers
// ::params:: num1 - first number
// ::params:: num2 - second number
// ::return::  a resulting Number
Number* multiply(Number* num1, Number* num2);

// multiply a Number struct by int
// ::params:: num1 - Number struct
// ::params:: integer - integer to be multiplied by
// ::return::  a resulting Number
Number* multiplyByInt(Number* num1, int integer);

// divide two numbers
// ::params:: num1 - first number
// ::params:: num2 - second number
// ::return::  a resulting Number
Number* divide(Number* num1, Number* num2);


// Declare table as a global variable
static Table* table;


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


char* numToChar(Number* number) {

        char* numArray = malloc(DIGITS * 2 * sizeof(char));
        int index = 0;

        if (number->negative) {
            numArray[0] = '-';
            index++;
        }

        for (int i = number->digits_whole - 1; i >= 0; i--, index++) {
            numArray[index] = number->whole_part[i] + '0';
        }
        numArray[index++] = '.';

        for (int i = 0; i < number->digits_decimal; i++, index++) {
            numArray[index] = number->decimal_part[i] + '0';
        }
        return numArray;
}


void getNumberChar(char* message, char* output)
{

    while (1) {
        printf("%s", message);
        if (scanf("%s", output) == 1 && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a string, or too many arguments\n");
        }
    }
}


Number* setNewNumber() {

    Number* num = (Number*) malloc(sizeof(Number));

    num->negative = 0;
    num->digits_whole = 1;
    num->digits_decimal = 1;
    num->whole_part[0] = 0;
    num->decimal_part[0] = 0;

    return num;
}
 



Number* setNumberFromChar(char* numArray) {

    Number* number = (Number*) malloc(sizeof(Number));

    char whole_part[DIGITS];
    char decimal_part[DIGITS];

    int count = 0;
    int error = 0;
    int decimal_pos = 0;

    int start = 0;
    int is_decimal_part = 0;

    number->negative = 0;

    if (numArray[0] == '-') {
        number->negative = 1;
        start++;
    } 

    for (int i = start; i < DIGITS * 2; i++) {

        if(!isdigit(numArray[i])) {
            if (numArray[i] == '.') {
                strncpy(whole_part, numArray+number->negative, count);
                number->digits_whole = count;
                decimal_pos = count;
                count = 0;
                is_decimal_part = 1;
            } else if (numArray[i] == 0) {
                if (is_decimal_part) {
                    strncpy(decimal_part, numArray+decimal_pos+number->negative+1, count);
                    number->digits_decimal = count;
                    break;
                } else {
                    strncpy(whole_part, numArray+number->negative, count);
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

    /// TODO handle this error
    if(error) {
        printf("Invalid number\n");
    }

    for (int i = number->digits_whole - 1; i >= 0; i--) {
        number->whole_part[i] = (int)whole1[number->digits_whole-1-i] - '0';
    }

    for (int i = 0; i < number->digits_decimal; i++) {
        number->decimal_part[i] = (int)decimal1[i] - '0';
    }

    fixNumber(number);
    return number;
}


Number* setNumberFromDouble(long double number, int whole_digits, int decimal_digits) {

    char charray[DIGITS];

    sprintf(charray, "%*.*Lf", whole_digits, decimal_digits, number);

    return setNumberFromChar(charray);

}






void assign(Number* num1, Number* num2) {

    num1->digits_whole = num2->digits_whole;
    num1->digits_decimal = num2->digits_decimal;
    num1->negative = num2->negative;

    for (int i = 0; i < num2->digits_decimal; i++) {
        num1->decimal_part[i] = num2->decimal_part[i];
    }
    for (int i = 0; i < num2->digits_whole; i++) {
        num1->whole_part[i] = num2->whole_part[i];
    }
}




void fixNumber(Number* num) {
    if (num->digits_whole == 0) {
        num->digits_whole = 1;
        num->whole_part[0] = 0;
    }
    if (num->digits_decimal == 0) {
        num->digits_decimal = 1;
        num->decimal_part[0] = 0;
    }

    int zeros = 0;

    for (int i = num->digits_whole - 1; i > 0; i--) {
        if (num->whole_part[i] == 0) {
            zeros++;
        } else {
            break;
        }
    }
    num->digits_whole -= zeros;

    zeros = 0;

    for (int i = num->digits_decimal - 1; i > 0; i--) {
        if (num->decimal_part[i] == 0) {
            zeros++;
        } else {
            break;
        }
    }
    num->digits_decimal -= zeros;
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
        for (int i = num1->digits_whole-1; i >= 0; i--) {
            if (num1->whole_part[i] > num2->whole_part[i]) {
                return 1;
            } else if (num1->whole_part[i] < num2->whole_part[i]) {
                return 2;
            }
        }

        // compare decimal parts
        for (int i = 0; i < DIGITS; i++) {
            if (num1->decimal_part[i] > num2->decimal_part[i]) {
                return 1;
            } else if (num1->decimal_part[i] < num2->decimal_part[i]) {
                return 2;
            }
        }

        return 3; // the numbers are equal
    }
}

Number* add(Number* num1, Number* num2, int negative) {
    Number* bigger = num1;
    Number* smaller = num2;

    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
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
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
    }

    // copy whole_part to the result struct
    res->digits_whole = bigger->digits_whole + 1;

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

    fixNumber(res);
    return res;
}





Number* subtract(Number* num1, Number* num2) {

    int negative;
    // compare the two numbers
    int rs = compare(num1, num2);

    Number* first;
    Number* second;

    Number* res = setNewNumber();

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

    fixNumber(res);
    return res;
}




Number* multiply(Number* num1, Number* num2) {

    Number* res = (Number*) malloc(sizeof(Number));
    // firstly, set the result as a whole part of the resulting number
    // set digits of the result to a maximum possible number after  multiplication
    res->digits_whole = num1->digits_whole + num1->digits_decimal + num2->digits_whole + num2->digits_decimal;

    // two dimensional array used for storing partial products
    // first dimension size - how many numerals does the factor have (the second number)
    // second dimension size - the maximum possible number of digits after multiplication
    int a[num2->digits_whole+num2->digits_decimal][res->digits_whole];
    // initialize two dimensional array with zeroes.
    memset(a, 0, sizeof(a[0][0]) * (num2->digits_whole+num2->digits_decimal) * res->digits_whole);

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

    // Set how many decimal numbers the result will contain at most
    int decimal_numbers = num1->digits_decimal + num2->digits_decimal;

    int part = 0;
    int rc;

    // pos (position) sets how many zeroes there will be before the actual
    // partial product (since each partial product is multiplied by ten
    // in a sense from the point of view of the previous partial product,
    // ie
    //    211
    //    *
    //     52
    //  _____
    //    422
    //  1055  <- differs by the power of ten.
    //
    //  The resulting partial products are then stored in two dimentional
    //  array, with zeros both in front and the back of the number:
    //  
    //  00422
    //  10550
    int pos = 0;

    // long multiplication of numbers, storing each partial product
    // in a two dimensional array
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

    int result = 0;
    part = 0;

    // add all partial products together
    for (int j = 0; j < res->digits_whole; j++) {
        for (int i = 0; i < n2->digits_whole; i++) {
            result += a[i][j];
        }

        result += part;
        part = result / 10;
        res->whole_part[j] = result % 10;
        result = 0;
    }

    
    // remove zeroes in the front of the resulting number
    for (int i = res->digits_whole-1; i >= 0; i--) {
        if (res->whole_part[i] == 0) {
            res->digits_whole--;
        } else {
            break;
        }
    }

    // move decimal dot to the required place
    // ie convert whole number to a decimal number again
    res->digits_decimal = decimal_numbers;
    for (int i = 0; i < decimal_numbers; i++) {
        res->decimal_part[i] = res->whole_part[decimal_numbers-1-i];
    }


    for (int i = 0; i < res->digits_whole; i++) {
        res->whole_part[i] = res->whole_part[decimal_numbers+i];
    }
    res->digits_whole -= decimal_numbers;

    fixNumber(res);
    return res;

}



Number* multiplyByInt(Number* num1, int integer) {

    // init to zero
    Number* num2 = setNewNumber();

    while(integer != 0) {
        num2->digits_whole++;
        num2->whole_part[num2->digits_whole-1] = integer % 10;
        integer /= 10;
    }
    return multiply(num1, num2);
}

// FIXME division works until +-35 digits are put in the result.
// FIXME After that, the program freezes.
// FIXME hence the temporary guard if condition is added to stop 
// FIXME division after the resulting number reaches 35 digits.
Number* divide(Number* num1, Number* num2) {

    int rs = compare(num1, num2);
    int quotient;

    // if first is greater or equal, the quotient will 
    // be greater than 1
    if (rs == 1) {
        quotient = 1;
    // if first is less than second, 
    // the quotient will be less than 1
    } else if (rs == 2) {
        quotient = 0;
    // else if numbers are equal, return one 
    // (Number struct with the value of one)
    } else if (rs == 3) {
        Number* res = setNewNumber();
        res->whole_part[0] = 1;
        return res;
    }

    Number* res = setNewNumber();

    // initalize Number with the value of one
    Number* one = setNumberFromChar(ONE);

    // initalize Number with the value of ten
    Number* ten = setNumberFromChar(TEN);

    // initalize Number with the value of 0.1
    Number* zero_one = setNumberFromChar(ZERO_ONE);

    Number* tmp;
    tmp = num1;

    // set the remainder as the dividend at first
    Number* remainder = num1;

    // sets how many times the divisor is subtracted from remainder
    // ie sets the whole number = remainder / divisor
    int counter = 0;

    // run the long division loop
    while (1) {
        tmp = subtract(tmp, num2);
        // if remainder is not yet divided into equal parts or does
        // not yet become negative, continue the division
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !tmp->negative) {
            res = add(res, one, 0);
            counter++;
        // stop if the remainder becomes equal to zero (ie becomes divided
        // into equal parts
        } else if (isZero(tmp)) {
            res = add(res, one, 0);
            counter++;
            return res;
        } else {
            // if the divisor (second number) is greater than the remainder,
            // multiply the remainder by ten and continue the division loop.
            if (counter == 0) {
                // tmp becomes remainder again
                assign(tmp, remainder);

                // the remainder is multiplied by ten
                tmp = multiply(tmp, ten);
                remainder = multiply(remainder, ten);
                // enter a zero to the result, which means that the remainder
                // was smaller than the divisor
                res->decimal_part[res->digits_decimal] = 0;
                res->digits_decimal++;
                // divide "one" by ten (or multiply by 0.1) to set the correct
                // decimal place of the result
                one = multiply(one, zero_one);
                continue;
            }
            // FIXME temporary guard, else the program stops running 
            // FIXME (gets stuck)
            if (res->digits_decimal > 35) {
                return res;
            }
            // get the new remainder (remainder -= divisor * (remainder / divisor))
            remainder = subtract(remainder, multiplyByInt(num2, counter));
            one = multiply(one, zero_one);
            counter = 0;

            // tmp becomes remainder again
            assign(tmp, remainder);

            // increase the remainder by the power of ten each time
            remainder = multiply(remainder, ten);
            tmp = multiply(tmp, ten);

        }
    }

    fixNumber(res);
    return res;
}


