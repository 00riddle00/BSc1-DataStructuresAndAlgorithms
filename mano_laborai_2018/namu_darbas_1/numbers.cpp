/*=============================================================================
 | Big Numbers ADT implementation
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Header file with useful debugging macros
#include "dbg.h"
#include "numbers.h"

// Define table as a global variable
Table* table;

void initTable() {
    table = (Table*) malloc(sizeof(Table));
    table->capacity = CHUNK_SIZE;
    table->size = 0;
    table->numbers = (Number**) malloc(CHUNK_SIZE * sizeof(Number*));
    
    for (int i = 0; i < table->capacity; i++) {
        table->numbers[i] = (Number*) calloc(1, sizeof(Number));
    }
}

void saveNumber(Number* number) {
    if (table->size == table->capacity) {
        table->capacity += CHUNK_SIZE;
        table->numbers = (Number**) realloc(table->numbers, table->capacity * sizeof(Number*));

        for (int i = table->size; i < table->capacity; i++) {
            table->numbers[i] = (Number*) calloc(1, sizeof(Number));
        }
    }
    table->numbers[table->size] = number;
    table->size++;
}

void printEntry(Number* number) {

        if (number->negative) {
            printf("-");
        }

        debug("NUM COUNT %d", number->digits_whole);

        for (int i = number->digits_whole - 1; i >= 0; i--) {
            printf("%d", number->whole_part[i]);
            debug("WHOLE PART DISSECTED %d", number->whole_part[i]);
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
        debug("ENTRY");
        printEntry(number);

        debug("DD %d", number->digits_decimal);
        debug("DW %d", number->digits_whole);

        char* numArray = (char*) calloc(1, DIGITS * 2 * sizeof(char));
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
        printf("Invalid number. Number 0.0 is returned/written\n");
        free(number);
        Number* zero = setNumberFromChar((char*)"0.0");
        return zero;
    }

    for (int i = number->digits_whole - 1; i >= 0; i--) {
        number->whole_part[i] = (int)whole_part[number->digits_whole-1-i] - '0';
    }

    for (int i = 0; i < number->digits_decimal; i++) {
        number->decimal_part[i] = (int)decimal_part[i] - '0';
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

int compareEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 3) {
        return 1;
    } else {
        return 0;
    }
}

int compareNotEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 3) {
        return 0;
    } else {
        return 1;
    }
}

int compareGreaterThan(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 1) {
        return 1;
    } else {
        return 0;
    }
}

int compareLessThan(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 2) {
        return 1;
    } else {
        return 0;
    }
}

int compareGreaterThanOrEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 2) {
        return 0;
    } else {
        return 1;
    }
}

int compareLessThanOrEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 1) {
        return 0;
    } else {
        return 1;
    }
}




int compareNumbers(Number* num1, Number* num2) {

    int sign1 = num1->negative;
    int sign2 = num2->negative;
    int cmp;

    // both numbers positive
    if (!sign1 && !sign2) {
        cmp = compare(num1, num2);
    // both numbers negative
    } else if (sign1 && sign2) {
        cmp = compare(num2, num1);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        // greater than
        cmp = 1;
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        // less than
        cmp = 2;
    }
    return cmp;
}

Number *addNumbers(Number* num1, Number* num2) {
    Number* res;
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res = add(num1, num2, 0);
    // both numbers negative
    } else if (sign1 && sign2) {
        res = add(num1, num2, 1);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        res = subtract(num1, num2);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        res = subtract(num1, num2);
    }

    return res;
}

Number* subtractNumbers(Number* num1, Number* num2) {
    Number* res;
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res =  subtract(num1, num2);
    // both numbers negative
    } else if (sign1 && sign2) {
        res =  subtract(num1, num2);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        res = add(num1, num2, 0);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        res = add(num1, num2, 1);
    }

    return res;
}

Number* multiplyNumbers(Number* num1, Number* num2) {
    Number* res = multiply(num1, num2);
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res->negative = 0;
    // both numbers negative
    } else if (sign1 && sign2) {
        res->negative = 0;
    // one number is positive, another - negative
    } else {
        res->negative = 1;
    }

    return res;
}

Number* divideNumbers(Number* num1, Number* num2) {

    Number* res = divide(num1, num2);
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res->negative = 0;
    // both numbers negative
    } else if (sign1 && sign2) {
        res->negative = 0;
    // one number is positive, another - negative
    } else {
        res->negative = 1;
    }

    return res;
}

Number* add(Number* num1, Number* num2, int negative) {

    Number* bigger = setNewNumber();
    Number* smaller = setNewNumber();
    assign(bigger, num1);
    assign(smaller, num2);

    //Number* bigger = num1;
    //Number* smaller = num2;

    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
        //assign(bigger, num2);
        //assign(smaller, num1);
    }

    // create result Number and populate it with decimal digits 
    // of the bigger number
    Number* res = (Number*) calloc(1, sizeof(Number));
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

    debug("RES IS 1");
    printEntry(res);

    // part then moves on to be added to the whole part of the number
    if (res->decimal_part[0] >= 10) {
        part = 1;
        res->decimal_part[0] %= 10;
    } 

    debug("RES IS 2");
    printEntry(res);

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

    debug("RES IS 3");
    printEntry(res);
    //fixNumber(res);
    debug("RES IS 4");
    printEntry(res);

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

        // TODO maybe use this implementation, 
        // but move it inside addition for loop
/*        if (i + 1 == smaller->digits_whole) {*/
            //while(1) {
                //if (res->whole_part[i+1] >= 10) {
                    //part = 1;
                    //res->whole_part[i+1] %= 10;
                    //res->whole_part[i+2] += part;
                    //if (i+2 == res->digits_whole) {
                        //res->digits_whole++;
                        //breakas = 1;
                        //break;
                    //}
                    //i++;
                    //continue;
                //} else {
                    //break;
                //}
            //}
            //if (breakas) {
                //break;
            //}
        //}
    //fixNumber(res);

    // After adding the whole parts, at the end 
    // such situation might occur that one of the
    // numbers of the sum is equal to 10. Since all
    // the numbers should be 1-digit, this piece
    // of code fixes this error
    for (int i = 0; i < res->digits_whole; i++) {
        if (res->whole_part[i] >= 10) {
            res->whole_part[i] %= 10;
            res->whole_part[i+1] += 1;
            if (i + 1 == res->digits_whole) {
                res->digits_whole++;
            }
        }
    }


    debug("RES IS 5");
    printEntry(res);

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

    // TODO use setNewNumber here
    Number* res = (Number*) calloc(1, sizeof(Number));
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
    Number* n1 = (Number*) calloc(1, sizeof(Number));

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
    Number* n2 = (Number*) calloc(1, sizeof(Number));

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

    
    // TODO readd this?
/*    // remove zeroes in the front of the resulting number*/
    //for (int i = res->digits_whole-1; i >= 0; i--) {
        //if (res->whole_part[i] == 0) {
            //res->digits_whole--;
        //} else {
            //break;
        //}
    //}

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

    free(n1);
    free(n2);
    fixNumber(res);
    return res;

}



Number* multiplyByInt(Number* num1, int integer) {

    // init to zero
    //Number* num2 = setNewNumber();
    Number* num2 = (Number*) calloc(1, sizeof(Number));

    while(integer != 0) {
        num2->digits_whole++;
        num2->whole_part[num2->digits_whole-1] = integer % 10;
        integer /= 10;
    }

    debug("entries");

    debug("%d", num1->digits_whole);
    debug("%d", num1->digits_decimal);

    debug("%d", num2->digits_whole);
    debug("%d", num2->digits_decimal);

    printEntry(num1);
    printEntry(num2);

    return multiply(num1, num2);
}

// FIXME division works until +-35 digits are put in the result.
// FIXME After that, the program freezes.
// FIXME hence the temporary guard if condition is added to stop 
// FIXME division after the resulting number reaches 35 digits.
Number* divide(Number* num1, Number* num2) {
    int quotient;

    int rs = compare(num1, num2);

    // if first is greater, the quotient will 
    // be greater than 1
    if (rs == 1) {
        quotient = 1;
    // if first is smaller than second, 
    // the quotient will be less than 1
    } else if (rs == 2) {
        quotient = 0;
    // else if numbers are equal, return one 
    } else if (rs == 3) {
        // initalize Number with the value of one
        Number* one = setNumberFromChar((char*) ONE);
        return one;
    }

    Number* res = setNewNumber();

    // initalize Number with the value of one
    Number* one = setNumberFromChar((char*) ONE);

    // initalize Number with the value of ten
    Number* ten = setNumberFromChar((char*) TEN);

    // initalize Number with the value of 0.1
    Number* zero_one = setNumberFromChar((char*) ZERO_ONE);

    Number* tmp = (Number*) calloc(1, sizeof(Number));
    assign(tmp, num1);
    //tmp = num1;

    // set the remainder as the dividend at first
    Number* remainder = num1;

    if (!quotient) {
        one = multiply(one, zero_one);
        tmp = multiply(tmp, ten);
        remainder = multiply(remainder, ten);
    }

    // sets how many times the divisor is subtracted from remainder
    // ie sets the whole number = remainder / divisor
    int counter = 0;

    // run the long division loop
    while (1) {
        tmp = subtract(tmp, num2);
        // if remainder is not yet divided into equal parts or does
        // not yet become negative, continue the division
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !(tmp->negative)) {
            debug("counter: %d", counter);
            if (counter == 99) {
                debug("9999999");

            }
            debug("RES BEFORE");
            printEntry(res);
            res = add(res, one, 0);
            debug("counter++");
            printEntry(res);
            counter++;
            debug("TMP is");
            printEntry(tmp);
            if (counter == 101) {
                //exit(1);
            }
            continue;
        // stop if the remainder becomes equal to zero (ie becomes divided
        // into equal parts
        } else if (isZero(tmp)) {
            res = add(res, one, 0);
            counter++;
            free(one);
            free(ten);
            free(zero_one);
            return res;
        } else {
            debug("Else goes here");
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
                
                // TODO ar nereiktu pirma digits_decimal++ padaryti?
                if (res->digits_decimal > 1) {
                    res->decimal_part[(res->digits_decimal)++] = 0;
                }
                one = multiply(one, zero_one);

                continue;
            }
            // FIXME temporary guard, else the program stops running 
            // FIXME (gets stuck)
            if (res->digits_decimal > 200) {
                free(one);
                free(ten);
                free(zero_one);
                debug("DAAAAAAAAAA: %d", res->digits_whole);
                fixNumber(res);
                return res;
            }
            // get the new remainder (remainder -= divisor * (remainder / divisor))
            //
            //
            debug("counter: %d", counter);
            debug("NUM2");
            printEntry(num2);

            debug("REM1");
            printEntry(remainder);
            
            debug("MULTI");
            printEntry(multiplyByInt(num2, counter));

            debug("BEFORE SUBTRACTION-----------------------------------------");
            remainder = subtract(remainder, multiplyByInt(num2, counter));
            debug("AFTER SUBTRACTION-----------------------------------------");

            debug("REM");
            printEntry(remainder);

            //one->decimal_part[one->digits_decimal-1] = 0;
            //one->decimal_part[(one->digits_decimal)++] = 1;
            one = multiply(one, zero_one);
            debug("ONE");
            printEntry(one);
            //
            counter = 0;

            // tmp becomes remainder again
            assign(tmp, remainder);

            debug("TMP");
            printEntry(tmp);

            remainder = multiply(remainder, ten);
            tmp = multiply(tmp, ten);

            debug("TMP2");
            printEntry(tmp);

            //exit(1);

        }
    }

    free(one);
    free(ten);
    free(zero_one);
    fixNumber(res);
    return res;
}


Number* modulus(Number* num1, Number* num2) {
    int quotient;

    int rs = compare(num1, num2);

    // if first is greater, the modulus will 
    // be mod(num1, num2);
    if (rs == 1) {
    // if first is smaller than second, 
    // the modulus will be the first number
    } else if (rs == 2) {
        return num1;
    // else if numbers are equal, return zero 
    } else if (rs == 3) {
        // initalize Number with the value of zero
        Number* zero = setNewNumber();
        return zero;
    }


    Number* res = setNewNumber();

    // initalize Number with the value of one
    Number* one = setNumberFromChar((char*) ONE);

    // initalize Number with the value of ten
    Number* ten = setNumberFromChar((char*) TEN);

    // initalize Number with the value of 0.1
    Number* zero_one = setNumberFromChar((char*) ZERO_ONE);

    Number* tmp = (Number*) calloc(1, sizeof(Number));
    assign(tmp, num1);
    //tmp = num1;

    // set the remainder as the dividend at first
    Number* remainder = num1;

    if (!quotient) {
        one = multiply(one, zero_one);
        tmp = multiply(tmp, ten);
        remainder = multiply(remainder, ten);
    }

    // sets how many times the divisor is subtracted from remainder
    // ie sets the whole number = remainder / divisor
    int counter = 0;

    // run the long division loop
    while (1) {
        tmp = subtract(tmp, num2);
        // if remainder is not yet divided into equal parts or does
        // not yet become negative, continue the division
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !(tmp->negative)) {
            debug("counter: %d", counter);
            if (counter == 99) {
                debug("9999999");

            }
            debug("RES BEFORE");
            printEntry(res);
            res = add(res, one, 0);
            debug("counter++");
            printEntry(res);
            counter++;
            debug("TMP is");
            printEntry(tmp);
            if (counter == 101) {
                //exit(1);
            }
            continue;
        // stop if the remainder becomes equal to zero (ie becomes divided
        // into equal parts
        } else if (isZero(tmp)) {
            res = add(res, one, 0);
            counter++;
            free(one);
            free(ten);
            free(zero_one);

            Number* zero = setNewNumber();
            return zero;
        } else {
            debug("Else goes here");
            return addNumbers(tmp, num2);
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
                
                // TODO ar nereiktu pirma digits_decimal++ padaryti?
                if (res->digits_decimal > 1) {
                    res->decimal_part[(res->digits_decimal)++] = 0;
                }
                one = multiply(one, zero_one);

                continue;
            }
            // FIXME temporary guard, else the program stops running 
            // FIXME (gets stuck)
            if (res->digits_decimal > 200) {
                free(one);
                free(ten);
                free(zero_one);
                debug("DAAAAAAAAAA: %d", res->digits_whole);
                fixNumber(res);
                return res;
            }
            // get the new remainder (remainder -= divisor * (remainder / divisor))
            //
            //
            debug("counter: %d", counter);
            debug("NUM2");
            printEntry(num2);

            debug("REM1");
            printEntry(remainder);
            
            debug("MULTI");
            printEntry(multiplyByInt(num2, counter));

            debug("BEFORE SUBTRACTION-----------------------------------------");
            remainder = subtract(remainder, multiplyByInt(num2, counter));
            debug("AFTER SUBTRACTION-----------------------------------------");

            debug("REM");
            printEntry(remainder);

            //one->decimal_part[one->digits_decimal-1] = 0;
            //one->decimal_part[(one->digits_decimal)++] = 1;
            one = multiply(one, zero_one);
            debug("ONE");
            printEntry(one);
            //
            counter = 0;

            // tmp becomes remainder again
            assign(tmp, remainder);

            debug("TMP");
            printEntry(tmp);

            remainder = multiply(remainder, ten);
            tmp = multiply(tmp, ten);

            debug("TMP2");
            printEntry(tmp);

            //exit(1);

        }
    }

    free(one);
    free(ten);
    free(zero_one);
    fixNumber(res);
    return res;
}


void freeTable() {
    for (int i = 0; i < table->capacity; i++) {
        free(table->numbers[i]);
    }
    free(table->numbers);
    free(table);
}

