#ifndef __NUMBERS_H
#define __NUMBERS_H
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

// free table
void freeTable();

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

int compareEqual(Number* num1, Number* num2);
int compareNotEqual(Number* num1, Number* num2);
int compareGreaterThan(Number* num1, Number* num2);
int compareLessThan(Number* num1, Number* num2);
int compareGreaterThanOrEqual(Number* num1, Number* num2);
int compareLessThanOrEqual(Number* num1, Number* num2);

int compareNumbers(Number* num1, Number* num2);

// TODO add description
Number *addNumbers(Number* num1, Number* num2);
Number* subtractNumbers(Number* num1, Number* num2);
Number* multiplyNumbers(Number* num1, Number* num2);
Number* divideNumbers(Number* num1, Number* num2);

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


Number* modulus(Number* num1, Number* num2);

// Declare table as a global variable
extern Table* table;

#endif
