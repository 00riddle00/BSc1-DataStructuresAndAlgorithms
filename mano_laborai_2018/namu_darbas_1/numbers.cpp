/*=============================================================================
 | Big Numbers ADT implementation
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <climits>

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

char* numToChar(Number* num) {
    int negative = num->negative;
    // +1 is for dot "." between whole and decimal parts
    // another +1 is for null terminating character
    int char_len = num->digits_whole + num->digits_decimal + negative + 1+1;
    char* res = (char*) malloc(char_len * sizeof(char));

    if (negative) {
        res[0] = '-';
    }
    for (int i = 0; i < num->digits_whole; i++) {
        res[i+negative] = (char) (num->whole_part[num->digits_whole-1-i] + '0');
    }
    res[num->digits_whole+negative] = '.';
    for (int i = num->digits_whole + 1, j = 0; i <= num->digits_whole + num->digits_decimal; i++, j++) {
        res[i+negative] = (char) (num->decimal_part[j] + '0');
    }

    // FIXME Writing out of bounds of an array???
    res[char_len-1] = '\0';

    return res;
}

Number* setNumberFromDouble(double number) {
    int negative = 0;

    if (number < 0) {
        negative = 1;
        number = - number;
    }

    double temp = number;

    char charray[2*16+1+1];

    int whole_digits = 0;
    while (temp >= 1) {
        temp /= 10;
        whole_digits++;
    }

    // TODO what if the number is out of bounds of the charray
    if (whole_digits > 16) {
        sprintf(charray, "%*.1f\0", whole_digits, number);
    } else {
        sprintf(charray, "%*.*f\0", whole_digits, 16-whole_digits, number);
    }

//     TODO rm this debugging code
//    int i = 0;
//    while (charray[i] != '\0') {
//        printf("%c", charray[i]);
//        i++;
//    }
//    printf("\n");
//
    Number* res = setNumberFromChar(charray);
    fixNumber(res);
    if (whole_digits > 16) {
        setAbsolutePrecision(res, 16);
    }
    res->negative = negative;
    return res;
}

Number* setNumberFromInt(int number) {

    int negative = 0;

    if (number < 0) {
        negative = 1;
        number = -number;
    }
    int temp = number;

    int whole_digits = 0;

    while (temp >= 1) {
        temp /= 10;
        whole_digits++;
    }

    int size = whole_digits + 2;
    char charray[size+1];

    sprintf(charray, "%0*d.0\0", whole_digits, number);

    // TODO rm this debugging code
    //int i = 0;
    //while (charray[i] != '\0') {
        //printf("%c", charray[i]);
        //i++;
    //}
    //printf("\n");
    //

    Number* res = setNumberFromChar(charray);
    fixNumber(res);
    res->negative = negative;
    return res;
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

//    Number* num = (Number*) malloc(sizeof(Number));
    Number* num = (Number*) calloc(1, sizeof(Number));

    num->negative = 0;
    num->digits_whole = 1;
    num->digits_decimal = 1;
    num->whole_part[0] = 0;
    num->decimal_part[0] = 0;

    return num;
}




Number* setNumberFromChar(char* numArray) {

//    Number* number = (Number*) malloc(sizeof(Number));
    Number* number = (Number*) calloc(1, sizeof(Number));

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
        // TODO do binary search
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
    // return values:
    // 1 - greater than
    // 2 - less than
    // 3 - equal
    return cmp;
}

void addNumbers(Number* res, Number* num1, Number* num2) {
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        add(res, num1, num2, 0);
    // both numbers negative
    } else if (sign1 && sign2) {
        add(res, num1, num2, 1);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        subtract(res, num1, num2);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        subtract(res, num2, num1);
    }
}

void subtractNumbers(Number* res , Number* num1, Number* num2) {
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        subtract(res, num1, num2);
    // both numbers negative
    } else if (sign1 && sign2) {
        subtract(res, num1, num2);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        add(res, num1, num2, 0);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        add(res, num1, num2, 1);
    }
}

void multiplyNumbers(Number* res, Number* num1, Number* num2) {
    multiply(res, num1, num2);
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
}

void divideNumbers(Number* res, Number* num1, Number* num2) {

    int sign1 = num1->negative;
    int sign2 = num2->negative;

    num1->negative = 0;
    num2->negative = 0;

    divide(res, num1, num2);

    num1->negative = sign1;
    num2->negative = sign2;

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
}

void add(Number* res, Number* num1, Number* num2, int negative) {

    Number* bigger = setNewNumber();
    Number* smaller = setNewNumber();
    assign(bigger, num1);
    assign(smaller, num2);

    //Number* bigger = num1;
    //Number* smaller = num2;

    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number* temp = setNewNumber();
        assign(temp, smaller);
        assign(smaller, bigger);
        assign(bigger, temp);
        free(temp);
    }

    // create result Number and populate it with decimal digits 
    // of the bigger number
    for (int i = 0; i < bigger->digits_decimal; i++) {
        res->decimal_part[i] = bigger->decimal_part[i];
    }
    res->digits_decimal = bigger->digits_decimal;

    // part - the part to be transfered to the next sum. 
    //  Ex. 9+5 = 14, 1 then becomes the "part" to be transfered next.
    int carry;

    // add decimal parts
    for (int i = smaller->digits_decimal - 1; i > 0; i--) {
        int result = res->decimal_part[i] + smaller->decimal_part[i];
        carry = 0;
        if (result > 10) {
            carry = 1;
            result %= 10;
        } else if (result == 10) {
            result = 0;
            carry = 1;
        }
        res->decimal_part[i] = result;
        res->decimal_part[i-1] += carry;
    }
    res->decimal_part[0] += smaller->decimal_part[0];

    carry = 0;

    // carry then moves on to be added to the whole part of the number
    if (res->decimal_part[0] >= 10) {
        carry = 1;
        res->decimal_part[0] %= 10;
    } 

    // select number with bigger amount of whole part digits
    if (bigger->digits_whole < smaller->digits_whole) {
        Number* temp = setNewNumber();
        assign(temp, smaller);
        assign(smaller, bigger);
        assign(bigger, temp);
        free(temp);
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
            result += carry;
        }
        carry = 0;
        if (result >= 10) {
            carry = 1;
            result %= 10;
        }
        res->whole_part[i] = result;
        res->whole_part[i+1] += carry;

    }

        // TODO maybe use this implementation, 
        // but move it inside addition for loop
/*        if (i + 1 == smaller->digits_whole) {*/
            //while(1) {
                //if (res->whole_part[i+1] >= 10) {
                    //carry = 1;
                    //res->whole_part[i+1] %= 10;
                    //res->whole_part[i+2] += carry;
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

    free(bigger);
    free(smaller);
    fixNumber(res);
}





void subtract(Number* res, Number* num1, Number* num2) {

    int negative;
    // compare the two numbers
    int rs = compare(num1, num2);

    Number* first = setNewNumber();
    Number* second = setNewNumber();


    // if first is greater or equal, 
    // subtract second number from the first
    if (rs == 1) {
        negative = 0;

        assign(first, num1);
        assign(second, num2);

    // if first is less than second,
    // subtract first number from the second
    } else if (rs == 2) {
        negative = 1;

        assign(first, num2);
        assign(second, num1);

    // else if numbers are equal, return zero 
    // (zeroth Number struct)
    } else if (rs == 3) {
        free(first);
        free(second);
        // TODO add zerofy fn
        makeZero(res);
        return;
    }

    // set decimal digits of the result to that of number having
    // more decimal digits
    res->digits_decimal = (first->digits_decimal >= second->digits_decimal) ? first->digits_decimal : second->digits_decimal;

    // TODO is first number really bigger?
    // copy decimal digits to the result
    for (int i = 0; i < res->digits_decimal; i++) {
        res->decimal_part[i] = first->decimal_part[i];
    }

    // TODO is first number really bigger?
    // set whole digits of the result to that the bigger number's
    res->digits_whole = first->digits_whole;
    for (int i = 0; i < res->digits_whole; i++) {
        res->whole_part[i] = first->whole_part[i];
    }

    if (second->digits_decimal < first->digits_decimal) {
        int dd = second->digits_decimal;
        second->digits_decimal = first->digits_decimal;
        for (int i = dd; i <= first->digits_decimal-1; i++) {
            second->decimal_part[i] = 0;
        }
    }


    // set the sign of the result
    res->negative = negative;

    /* actual subtraction starts   */
    
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

    free(first);
    free(second);
    fixNumber(res);
    return;
}




void multiply(Number* res, Number* num1, Number* num2) {

    // TODO use setNewNumber here
    // FIXME maybe this makes it crash
//    Number* res = (Number*) calloc(1, sizeof(Number));
    // firstly, set the result as a whole part of the resulting number
    // set digits of the result to a maximum possible number after  multiplication
    res->digits_whole = num1->digits_whole + num1->digits_decimal + num2->digits_whole + num2->digits_decimal;

    // two dimensional array used for storing partial products
    // first dimension size - how many numerals does the factor have (the second number)
    // second dimension size - the maximum possible number of digits after multiplication
    // TODO add a[...+1] ??
    int a[num2->digits_whole+num2->digits_decimal][res->digits_whole];
    // initialize two dimensional array with zeroes.
    memset(a, 0, sizeof(a[0][0]) * (num2->digits_whole+num2->digits_decimal) * res->digits_whole);

    // TODO simple assign might be enough
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
    // TODO add this line
//    n1->digits_whole--;

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
    // TODO add this line
//    n2->digits_whole--;




    // FIXME trouble point
    // Set how many decimal numbers the result will contain at most
    int decimal_numbers = num1->digits_decimal + num2->digits_decimal;

    int carry = 0;
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
            a[i][j+pos] = (rc + carry) % 10;
            carry = (rc+carry) / 10;
        }
        // FIXME if carry == 0 error
        a[i][n1->digits_whole+pos] = carry;
        carry = 0;
    }

    int result = 0;
    carry = 0;


    // create new temp number which can hold 1000 digits as a whole part
    TempNumber* temp = (TempNumber*) calloc(1, sizeof(TempNumber));
    temp->digits_whole = 0;

    // add all partial products together
    for (int j = 0; j < res->digits_whole; j++) {
        for (int i = 0; i < n2->digits_whole; i++) {
            result += a[i][j];
        }

        result += carry;
        carry = result / 10;
        // populate the new temp number with the result
        temp->whole_part[j] = result % 10;
        temp->digits_whole++;
        result = 0;
    }


    // add decimal part and whole part from the temp number to the resulting number (res)
    int whole_numbers = temp->digits_whole - decimal_numbers;
    res->digits_whole = whole_numbers;


    if (decimal_numbers > 500) {
        res->digits_decimal = 500;


        for (int i = temp->digits_whole - 500 - (temp->digits_whole - decimal_numbers), j = 499; i < temp->digits_whole - (temp->digits_whole - decimal_numbers); i++, j--) {
            res->decimal_part[j] = temp->whole_part[i];
        }

//        debug("temp");
//        debug("dn %d", decimal_numbers);
//        debug("dw %d", whole_numbers);
//        printEntry2(temp);
//        debug("res");
//        printEntry(res);

//        for (int i = temp->digits_whole - 1, j = whole_numbers - 1; i > temp->digits_whole - decimal_numbers - 1; i--, j--) {
        for (int i = temp->digits_whole - 1, j = whole_numbers - 1; i > decimal_numbers - 1; i--, j--) {
            res->whole_part[j] = temp->whole_part[i];
        }
    } else {
        res->digits_decimal = decimal_numbers;

        // TODO check for -1 index
        for (int i = temp->digits_whole-1, j = whole_numbers - 1; i > temp->digits_whole - whole_numbers - 1; i--, j--) {
            res->whole_part[j] = temp->whole_part[i];
        }

        // TODO check for -1 index
        for (int i = temp->digits_whole-whole_numbers-1, j = 0; i >= 0; i--, j++) {
            res->decimal_part[j] = temp->whole_part[i];
        }

    }

    // TODO readd free statements
    free(n1);
    // FIXME corrupted size
    free(temp);
    free(n2);
    fixNumber(res);
}


// additional functions
int getWholeLen(Number* num) {
    if (num->digits_whole == 1 && num->whole_part[0] == 0) {
        return 0;
    } else {
        return num->digits_whole;
    }
}

int getDecimalLen(Number* num) {
    if (num->digits_decimal == 1 && num->decimal_part[0] == 0) {
        return 0;
    } else {
        return num->digits_decimal;
    }
}

// decimal digits are marked by negative indexes
// ex. Number is 12.34
// ex.getIthDigit(0) returns 0 (nothing)
// ex getIthDigit(1) returns 1
// ex getIthDigit(2) returns 2
// ex getIthDigit(-1) returns 3
// ex getIthDigit(-2) returns 4
int getIthDigit(Number* num, int index) {
    if (!index) {
        printf("WARNING: Zeroth index does not exist");
    } else if (index > 0) {
        return num->whole_part[index-1];
    // else if index < 0
    } else {
        return num->decimal_part[-index-1];
    }
}

// TODO optimize
void increment(Number* num) {
    plusEquals(num, setNumberFromChar((char*) ONE));
}

// TODO optimize
void decrement(Number* num) {
    minusEquals(num, setNumberFromChar((char*) ONE));
}

void plusEquals(Number* num1, Number* num2) {
    Number* temp = setNewNumber();
    addNumbers(temp, num1, num2);
    assign(num1, temp);
    free(temp);
}

void minusEquals(Number* num1, Number* num2) {
    Number* temp = setNewNumber();
    subtractNumbers(temp, num1, num2);
    assign(num1, temp);
    free(temp);
}

void multiplyEquals(Number* num1, Number* num2) {
    Number* temp = setNewNumber();
    multiplyNumbers(temp, num1, num2);
    assign(num1, temp);
    free(temp);
}

void divideEquals(Number* num1, Number* num2) {
    Number* temp = setNewNumber();
    divideNumbers(temp, num1, num2);
    assign(num1, temp);
    free(temp);
}

void modulusEquals(Number* num1, Number* num2) {
    assign(num1, modulus(num1, num2));
}


// utility functions
void makeZero(Number* num) {
    num->whole_part[0] = 0;
    num->decimal_part[0] = 0;
    num->digits_whole = 1;
    num->digits_decimal = 1;
}

// works only with integers
int isDivisibleByTwo(Number* num) {
    switch(num->whole_part[0]) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 8:
            return 1;
        default:
            return 0;
    }
}

// works only with integers
int isDivisibleByThree(Number* num) {
    int sum = 0;
    for (int i = 0; i < num->digits_whole; i++) {
        sum += num->whole_part[i];
    }

    if (sum / 10 <= 0) {
        switch (sum) {
            case 3:
            case 6:
            case 9:
                return 1;
            default:
                return 0;
        }
    } else {
        Number *temp = setNumberFromInt(sum);
        if (isDivisibleByThree(temp)) {
            free(temp);
            return 1;
        } else {
            free(temp);
            return 0;
        }
    }
}

int isDivisibleByFive(Number* num) {
    if (num->whole_part[0] == 5 || num->whole_part[0] == 0) {
        return 1;
    } else {
        return 0;
    }
}



int pow(int number, int power) {
    int orig_number = number;
    for (int i = 0; i < power-1; i++) {
        number *= orig_number;
    }
    return number;
}


// converting Number ADT to int
int toInt(Number* num) {
    int int_repr = 0;
    for (int i = num->digits_whole; i > 1; i--) {
        int_repr += num->whole_part[i - 1] * pow(10, (i - 1));
    }
    int_repr += num->whole_part[0];
    return int_repr;
}


Number* getAbsoluteValue(Number* num) {
    // if num > 0
    if (!num->negative) {
        return num;
    // else if num <= 0
    } else {
        Number *ret_num = (Number*) calloc(1, sizeof(Number));
        assign(ret_num, num);
        ret_num->negative = 0;
        return ret_num;
    }
}

Number* getFloorNumber(Number* num) {
    if (num->digits_decimal == 1 && num->decimal_part[0] == 0) {
        return num;
    } else {
        // TODO solve memory leak
        Number* ret_num = (Number*) calloc(1, sizeof(Number));
        assign(ret_num, num);
        ret_num->digits_decimal = 1;
        ret_num->decimal_part[0] = 0;
        return ret_num;
    }
}


int isZero(Number* num) {
    return (!getWholeLen(num) && !getDecimalLen(num));
}

int isOne(Number* num) {
    return (!getDecimalLen(num) && getWholeLen(num) == 1 && num->whole_part[0] == 1);
}

int isInteger(Number* num) {
    return (num->digits_decimal == 1 && num->decimal_part[0] == 0);
}

void multiplyByInt(Number* res, Number* num1, int integer) {

    // init to zero
    //Number* num2 = setNewNumber();
    Number* num2 = (Number*) calloc(1, sizeof(Number));

    while(integer != 0) {
        num2->digits_whole++;
        num2->whole_part[num2->digits_whole-1] = integer % 10;
        integer /= 10;
    }

    multiply(res, num1, num2);
    free(num2);
}
// // utility functions




// FIXME division works until +-35 digits are put in the result.
// FIXME After that, the program freezes.
// FIXME hence the temporary guard if condition is added to stop 
// FIXME division after the resulting number reaches 35 digits.
void divide(Number* res, Number* num1, Number* num2) {

//    Number* res = setNewNumber();
    // make res to be zero
    makeZero(res);

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
//    Number* remainder = num1;



    // sets how many times the divisor is subtracted from remainder
    // ie sets the whole number = remainder / divisor
    int counter = 0;
//

     // temp hack to speed it up
    int iter = 0;
    while (tmp->digits_whole > num2->digits_whole) {
        counter = 0;
//        if (iter == 10){
//            exit(1);
//        }
        Number* multipl = setNewNumber();
        Number* temp2 = setNewNumber();
        Number *ten = setNumberFromChar((char *) "10.0");
        double mult;
        int mul;
        int diff_in_tens;

          mult = (double)tmp->whole_part[tmp->digits_whole-1] / ((double)num2->whole_part[num2->digits_whole-1]+1);
         mult *= 10;
         mul = (int)mult;
         if (mul < 10) {
             multipl = setNumberFromDouble((double)mul);
         } else {
             multipl = setNumberFromDouble((double)mul);
         }
        multiply(temp2, num2, multipl);
        counter += mul;
        diff_in_tens = tmp->digits_whole - temp2->digits_whole;

        if (diff_in_tens == 0) {
            minusEquals(tmp, temp2);
        } else {
            Number *temp3 = setNewNumber();
            assign(temp3, temp2);
            multiplyEquals(temp3, raiseByPow(ten, diff_in_tens));

            if (compareGreaterThan(temp3, tmp)) {
                diff_in_tens--;
            }
            free(temp3);
            multiplyEquals(temp2, raiseByPow(ten, diff_in_tens));
            for (int i = 0; i < diff_in_tens; i++) {
                counter *= 10;
            }
            minusEquals(tmp, temp2);

        }
        Number* temp1 = setNewNumber();
        assign(temp1, one);
        multiplyByInt(temp1, temp1, counter);
        plusEquals(res, temp1);
        free(temp1);

        free(multipl);
        free(temp2);
        free(ten);
        iter++;
    }

    counter = 0;

    int quotient;

    int rs = compare(tmp, num2);

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
//        return one;
        free(ten);
        free(zero_one);
        plusEquals(res, one);
        free(one);
        return;
    }


    Number* remainder = setNewNumber();
    assign(remainder, tmp);

    if (!quotient) {
        multiplyEquals(one, zero_one);
        multiplyEquals(tmp, ten);
        multiplyEquals(remainder, ten);
    }



    while (1) {
        minusEquals(tmp, num2);
        // if remainder is not yet divided into equal parts or does
        // not yet become negative, continue the division
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !(tmp->negative)) {
            plusEquals(res, one);
//            res = add(res, one, 0);
            counter++;
            continue;
        // stop if the remainder becomes equal to zero (ie becomes divided
        // into equal parts
        } else if (isZero(tmp)) {
//            res = add(res, one, 0);
            plusEquals(res, one);
            counter++;
            free(one);
            free(ten);
            free(zero_one);
            free(tmp);
            // FIXME memory crash if this line is added
//            free(remainder);
            return;
        } else {
            // if the divisor (second number) is greater than the remainder,
            // multiply the remainder by ten and continue the division loop.
            if (counter == 0) {
                // tmp becomes remainder again
                assign(tmp, remainder);

                // the remainder is multiplied by ten
                multiplyEquals(tmp, ten);
                multiplyEquals(remainder, ten);

                // enter a zero to the result, which means that the remainder
                // was smaller than the divisor
                
                // TODO ar nereiktu pirma digits_decimal++ padaryti?
                if (res->digits_decimal > 1) {
                    res->decimal_part[(res->digits_decimal)++] = 0;
                }
                multiplyEquals(one, zero_one);

                continue;
            }
            // FIXME temporary guard, else the program stops running 
            // FIXME (gets stuck)
            // TODO do smth about this magic number
            if (res->digits_decimal >= 200) {
                free(one);
                free(ten);
                free(zero_one);
                // FIXME memory crash if this lines is added
//                free(remainder);
                free(tmp);
                fixNumber(res);
                return;
            }
            // get the new remainder (remainder -= divisor * (remainder / divisor))
            //
            //
            Number* temp1 = setNewNumber();
            assign(temp1, num2);
            multiplyByInt(temp1, temp1, counter);
            minusEquals(remainder, temp1);

            //one->decimal_part[one->digits_decimal-1] = 0;
            //one->decimal_part[(one->digits_decimal)++] = 1;
            multiplyEquals(one, zero_one);
            counter = 0;

            // tmp becomes remainder again
            assign(tmp, remainder);

            multiplyEquals(remainder, ten);
            multiplyEquals(tmp, ten);

        }
    }
}


Number* modulus(Number* num1, Number* num2) {

    if (isZero(num1)) {
        Number* zero = setNewNumber();
        return zero;
    } else if (isZero(num2)) {
        printf("ERROR: Division from zero in modulus expression!\n");
        exit(1);
    }


    // compare absolute values. return whether num1 > num2
    int cmp_abs = compareNumbers(getAbsoluteValue(num1), getAbsoluteValue(num2));

    // if the absolute values of numbers are equal, return zero
    if (cmp_abs == 3) {
        Number *zero = setNewNumber();
        return zero;
    }

    // shows if num1 > num2 (value=1) or vice a versa (value=0)
    int cmp_gt;


    /* Finding which number is bigger, based on which absolute value
     * is bigger and either the number is positive or negative
     * (this saves computation time by avoiding another full comparison
     * between numbers) */

    // if |num1| > |num2|
    if (cmp_abs == 1) {
        // if num1 > 0
        if (!num1->negative) {
            // num1 > num2
            cmp_gt = 1;
        // else if num1 < 0
        } else {
            // num1 < num2
            cmp_gt = 0;
        }
    // else if |num1| < |num2|
    } else if (cmp_abs == 2) {
        // if num2 > 0
        if (!num2->negative) {
            // num1 < num2
            cmp_gt = 0;
        // else if num2 < 0
        } else {
            // num1 > num2
            cmp_gt = 1;

        }
    }

    // if num1 < num2
    if (cmp_gt == 0) {
        // if num2 < 0
        if (num2->negative) {
            Number* ret_num = modulus(getAbsoluteValue(num1), getAbsoluteValue(num2));
            ret_num->negative = 1;
            return ret_num;
        // else if num2 > 0
        } else {
            // if num1 > 0
            if (!num1->negative) {
                return num1;
            }
            // else if |num1| < |num2|
            else if (cmp_abs == 2) {
                Number* temp = setNewNumber();
                subtractNumbers(temp, num2, getAbsoluteValue(num1));
               return temp;
            }
            // else if |num1| > |num2|
            else if(cmp_abs == 1) {
                // if |num1|/num2 is integer
                Number*temp = setNewNumber();
                divideNumbers(temp, getAbsoluteValue(num1), num2);
                if (isInteger(temp)) {
                    Number* zero = setNewNumber();
                    free(temp);
                    return zero;
                // else, if the quotient is not an integer
                } else {
                    Number* temp01 = setNewNumber();
                    Number* temp02 = setNewNumber();
                    Number* one = setNumberFromChar((char*) ONE);
                    divideNumbers(temp01, getAbsoluteValue(num1), num2);
                    // return |(floor(|num1|/num2)+1)*num2| - |num1|
                    addNumbers(temp02, getFloorNumber(temp01), one);
                    multiplyNumbers(temp01, temp02, num2);
                    subtractNumbers(temp02, getAbsoluteValue(temp01), getAbsoluteValue(num1));
                    free(temp);
                    free(temp01);
                    return temp02;
                }
            }
        }
    // else if num1 > num2
    } else if (cmp_gt == 1) {
        // if num2 < 0
        if (num2->negative) {
            // if num1 > 0
            if (!num1->negative) {
                // if |num1| < |num2|
                if (cmp_abs == 2) {
                    Number* temp = setNewNumber();
                    addNumbers(temp, num1, num2);
                    return temp;
                // else if |num1| > |num2|
                } else {
                    Number *one = setNumberFromChar((char *) ONE);

                    Number* temp01 = setNewNumber();
                    Number* temp02 = setNewNumber();
                    divideNumbers(temp01, num1, num2);
                    addNumbers(temp02, getFloorNumber(getAbsoluteValue(temp01)), one);
                    multiplyNumbers(temp01, temp02, num2);
                    addNumbers(temp02, temp01, num1);
                    free(temp01);
                    return temp02;
                }
            }
            // else if num1 < 0
            else {
                // ret_num = -(modulus(|num1|,|num2|)
                // FIXME inf recursion
                Number* ret_num = modulus(getAbsoluteValue(num1), getAbsoluteValue(num2));
                ret_num->negative = 1;
                return ret_num;
            }
        // else if num2 > 0
        } else {
            //return num1 - floor(num1/num2)*num2
            Number* temp01 = setNewNumber();
            Number* temp02 = setNewNumber();
            divideNumbers(temp01, num1, num2);
            multiply(temp02, getFloorNumber(temp01), num2);
            subtractNumbers(temp01, num1, temp02);
            free(temp02);
            return temp01;
        }
    }

}

/* functions to be tested */
Number* factorial(Number* num) {

    Number* one = setNumberFromChar((char*) ONE);

    if (isZero(num)) {
        return one;
    }

    int negative = num->negative;
    num->negative = 0;
    Number* ret_num = setNewNumber();
    assign(ret_num, num);
    ret_num->negative = 0;

    int numToInt = toInt(ret_num);

    Number* diff = setNewNumber();
    assign(diff, one);
    Number* temp = setNewNumber();

    for (int i = 1; i < numToInt-1; i++) {
        multiplyByInt(diff, one, i);
        subtractNumbers(temp, num, diff);
        multiplyEquals(ret_num, temp);
    }

    free(temp);
    num->negative = negative;
    ret_num->negative = negative;
    return ret_num;
}

int isPrime(Number* num) {
    Number* two = setNumberFromChar((char*)"2.0");

    if (num->digits_whole == 1) {
        switch (num->whole_part[0]) {
            case 2:
            case 3:
            case 5:
            case 7:
                return 1;
            default:
                return 0;
        }
    }

    if (isDivisibleByTwo(num) || isDivisibleByThree(num) || isDivisibleByFive(num)) {
        return 0;
    }

    for (Number*i = setNumberFromChar((char *) "7.0"); compareLessThanOrEqual(raiseByPow(i, 2), num); plusEquals(i, two)) {
        if (isZero(modulus(num, i))) {
            return 0;
        }
    }
    return 1;
}

Number* nextPrime(Number* num) {
    if (num->negative || isZero(num)) {
        return setNumberFromChar((char *) "2.0");
    } else {
        num = getFloorNumber(num);

        Number* temp = setNewNumber();
        assign(temp, num);
        increment(temp);

        while (!isPrime(temp)) {
            increment(temp);
        }

        return temp;
    }
}

Number* raiseByPow(Number* num, int power) {
    if (power == 0) {
        Number* one = setNumberFromChar((char*)ONE);
        return one;
    }
    Number* ret_val = setNewNumber();
    assign(ret_val, num);

    Number* orig_num = setNewNumber();
    assign(orig_num, num);

    for (int i = 0; i < power-1; i++) {
        multiplyEquals(ret_val, orig_num);
    }
    free(orig_num);
    return ret_val;
}

// works only with integers
int* CanonicalForm(Number* num) {
    debug("#####################################");
    int *result = (int *) calloc(1, 12 * sizeof(int));
    result[0] = 2;
    result[2] = 3;
    result[4] = 5;
    result[6] = 7;
    result[8] = 11;
    result[10] = 13;


    Number *temp = setNewNumber();
    assign(temp, num);
    Number *modulo = setNewNumber();


    int power;
    Number *divisor = setNewNumber();
    for (int i = 10; i >= 0; i = i - 2) {
        power = 0;
        modulo = modulus(temp, setNumberFromInt(result[i]));

        while (isZero(modulo)) {
            divide(divisor, temp, setNumberFromInt(result[i]));
            assign(temp, divisor);
            modulo = modulus(temp, setNumberFromInt(result[i]));
            power++;
        }

        result[i + 1] = power;
    }
    debug("after");

    // debug code
//    for (int i = 0; i < 12; i++) {
//        printf("%d ", result[i]);
//    }

//    free(temp);
    free(modulo);
    free(divisor);
    return result;
}

Number* getLog(int prime_num) {

    // TODO remove this temporary hack and count each LOG using Log() function;
    switch (prime_num) {
        case 2:
            static Number* LOG_2 = setNumberFromChar((char*)"0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542001481020570685733685520235758130557032670751635");
            return LOG_2;
        case 3:
            static Number* LOG_3 = setNumberFromChar((char*)"1.098612288668109691395245236922525704647490557822749451734694333637494293218608966873615754813732088787970029065957865742368004225930519821052801870767");
            return LOG_3;
        case 5:
            static Number* LOG_5 = setNumberFromChar((char*)"1.609437912434100374600759333226187639525601354268517721912647891474178987707657764630133878093179610799966303021715562899724005229324676199633616617463");
            return LOG_5;
        case 7:
            static Number* LOG_7 = setNumberFromChar((char*)"1.945910149055313305105352743443179729637084729581861188459390149937579862752069267787658498587871526993061694205851140911723752257677786843148958095163");
            return LOG_7;
        case 11:
            static Number* LOG_11 = setNumberFromChar((char*)"2.397895272798370544061943577965129299821706853937417175218567709130573623913236713075054708002634791414715725888137998522255569158595787395355302390801");
            return LOG_11;
        case 13:
            static Number* LOG_13 = setNumberFromChar((char*)"2.564949357461536736053487441565318604805267944760207116419045510663464667324410179399574663440489488769258192092762721631532154491986587013825268116972");
            return LOG_13;
        default:
            printf("wrong number passed to getLog()");
            exit(1);
    }
}


Number* Log(Number* num) {
    debug("------------------------------------");

    // TODO add validation for negative input
    if (isOne(num)) {
        return setNewNumber();
    }
    if (isInteger(num)) {
        if (!isPrime(num)) {
            debug("not prime");
            Number *temp = setNewNumber();
            Number *result = setNewNumber();
            Number *part_of_sum = setNewNumber();
            assign(temp, num);

            debug("here");
            int *canonical = CanonicalForm(num);
            debug("here2");
            for (int i = 0; i < 12; i = i + 2) {
                part_of_sum = setNumberFromInt(canonical[i + 1]);
                if (isZero(part_of_sum)) {
                    continue;
                }
                multiplyEquals(part_of_sum, getLog(canonical[i]));
                plusEquals(result, part_of_sum);
            }

            free(temp);
            free(part_of_sum);

            if (!isZero(result)) {
                return result;
            }
        }
    } else {
        Number *temp = setNewNumber();
        Number *ten = setNumberFromInt(10);
        Number* semi_res = setNewNumber();
        assign(temp, num);
        int times = 0;
        while (!isInteger(temp)) {
            debug("multiply");
            multiplyEquals(temp, ten);
            times++;
        }
        printEntry(temp);
        semi_res = Log(temp);
        printEntry(semi_res);
        temp = Log(setNumberFromInt(10*times));
        minusEquals(semi_res, temp);
        free(ten);
        free(temp);
        return semi_res;
    }


    Number *step = setNewNumber();
    Number *one = setNumberFromChar((char *) ONE);
    Number *two = setNumberFromChar((char *) "2.0");

    Number *powe = setNumberFromChar((char *) ONE);

    Number *y = setNewNumber();
    Number *z = setNewNumber();
    Number* temp1 = setNewNumber();
    Number* temp2 = setNewNumber();
    addNumbers(temp1, num, one);
    subtractNumbers(temp2, num, one);
    divideNumbers(z, temp1, temp2);
    Number *ret_num = setNewNumber();

    divideNumbers(step, raiseByPow(temp2, 2), raiseByPow(temp1, 2));

    free(temp1);
    free(temp2);

    int count = 0;

    while (count < 400) {
//        debug("Log: %d", count);
        multiplyEquals(z, step);
        divideNumbers(y, one, powe);
        multiplyEquals(y, z);
        plusEquals(ret_num, y);
        plusEquals(powe, two);
        count++;
    }
    multiplyEquals(ret_num, two);
    free(step);
    free(one);
    free(powe);
    free(y);
    free(z);
    return ret_num;
}

Number* Sine(Number* num) {
    Number* step = setNewNumber();
    int n = 1;

    int change_sign = 0;
    while (n <= 200) {
//        debug("Sine: %d", n);
        Number* temp1 = setNumberFromInt(n);
        Number* temp2 = setNewNumber();
        divide(temp2, raiseByPow(num, n), factorial(temp1));
        if (change_sign) {
            minusEquals(step, temp2);
            change_sign = 0;
        } else {
            plusEquals(step, temp2);
            change_sign = 1;
        }
        free(temp1);
        free(temp2);
        n += 2;
    }
    return step;
}

Number* getAvg(Number* num[], int size) {
    Number* avg = setNewNumber();
    for (int i = 0; i < size; i++) {
        plusEquals(avg, num[i]);
    }
    divideEquals(avg, setNumberFromInt(size));
    return avg;
}

int findNum(Number** data, int size, Number* value) {
    for (int i = 0; i < size; i++) {
        Number* numSearched = data[i];

        if (compareEqual(numSearched, value)) {
            return 1;
        }
    }
    return 0;
}


void swap(Number* bigger, Number* smaller) {
    Number *temp = setNewNumber();
    assign(temp, smaller);
    assign(smaller, bigger);
    assign(bigger, temp);
    free(temp);
}

void sortNums(Number** target, int size) {
    int i = 0;
    int j = 0;

    int count_operations = 1;

    for (i = 0; i < size; i++) {
        if (count_operations == 0)
            break;
        count_operations = 0;
        for (j = 0; j < size - 1; j++) {
            if (compareGreaterThan(target[j], target[j+1])) {
                swap(target[j], target[j + 1]);
                count_operations++;
            }
        }
        for (j = size - 1; j > 0; j--) {
            if (compareLessThan(target[j], target[j-1])) {
                swap(target[j], target[j - 1]);
                count_operations++;
            }
        }
    }
}





void setMaxPrecision(Number* num, int precision) {
    TempNumber *temp = (TempNumber *) calloc(1, sizeof(TempNumber));
    int whole_len = getWholeLen(num);
    int decimal_len = getDecimalLen(num);

    temp->digits_whole = whole_len + decimal_len;

    for (int i = 0; i < decimal_len; i++) {
        temp->whole_part[decimal_len - 1 - i] = num->decimal_part[i];
    }
    for (int i = 0; i < whole_len; i++) {
        temp->whole_part[decimal_len + i] = num->whole_part[i];
    }

    // TODO rm magic numbers
    int rounded_index = temp->whole_part[temp->digits_whole - precision - 1];

    num->digits_decimal = precision - whole_len;
    for (int i = temp->digits_whole - whole_len-1, j = 0; i > temp->digits_whole - precision; i--, j++) {
        num->decimal_part[j] = temp->whole_part[i];
    }

    if (rounded_index >= 5) {
        Number* increment_val = setNewNumber();
        increment_val->digits_decimal = num->digits_decimal;
        increment_val->decimal_part[increment_val->digits_decimal-1] = 1;
        plusEquals(num, increment_val);
    }
}



void setPrecision(Number* num, int precision) {
    int negative = num->negative;
    num->negative = 0;

    if (isZero(num)) {
        return;
    }

    if (getWholeLen(num) == 0 && num->decimal_part[0] == 0) {
        Number *ten = setNumberFromChar((char *) "10.0");
        int zero_count = 1;
        int initial_precision;
        while (num->decimal_part[zero_count] == 0) {
            zero_count++;
        }
        multiplyEquals(num, raiseByPow(ten, zero_count));

        if (precision > 0) {
            setAbsolutePrecision(num, precision);
        // else if (precision < 0);
        } else {
            precision = -precision;
            setAbsolutePrecision(num, precision - zero_count);
        }
        divideEquals(num, raiseByPow(ten, zero_count));
        num->negative = negative;
        return;
    }

    if (precision > 0) {
        setAbsolutePrecision(num, precision);
    // else if (precision < 0);
    } else {
        setDecimalPrecision(num, -precision);
    }
    num->negative = negative;
}




void setDecimalPrecision(Number* num, int precision) {
    int dec_num = num->digits_decimal;
    if (dec_num <= precision) {
        return;
    } else if (dec_num > precision) {
        if (num->digits_whole == 1 && num->whole_part[0] == 0) {
            for (int i = 0; i < dec_num; i++) {
                if (num->decimal_part[i] == 0) {
                    precision--;
                } else {
                    setAbsolutePrecision(num, precision);
                    return;
                }
            }
            setAbsolutePrecision(num, precision);
            return;
        } else {
            setAbsolutePrecision(num, num->digits_whole + precision);
            return;
        }
    } else {
        for(int i = num->digits_decimal; i < precision; i++) {
            num->decimal_part[i] = 0;
        }
        num->digits_decimal = precision;
        return;
    }
}


// this operation is irreversible!
// negative precision means how many numbers after the comma there will be,
// without altering the precision of the whole part. The remaining free space
// is filled with zeroes
void setAbsolutePrecision(Number* num, int precision) {

    // TODO rm magic numbers
    if (getWholeLen(num) + getDecimalLen(num) >= 500 && (getDecimalLen(num) != 0 && num->decimal_part[0] != 0)) {
        setMaxPrecision(num, precision);
        return;
    }
    Number *ten = setNumberFromChar((char *) "10.0");
    // TODO case when higher precision is added (?)
    // TODO check precision for negative values and zero
    // TODO wrap num->digits_whole in a variable
    // TODO fixNumber might be needed
    if (num->digits_whole >= precision) {
        if (num->digits_whole > precision) {
            int last_index = num->digits_whole - precision;
            int rounded_index = last_index - 1;
            if (num->whole_part[rounded_index] < 5) {
                for (int i = rounded_index; i >= 0; i--) {
                    num->whole_part[i] = 0;
                }
                // else if num->whole_part[rounded_index >= 5)
            } else {
                Number *roundingTens = raiseByPow(ten, rounded_index + 1);
                Number *numberToBeSubtracted = setNewNumber();
                assign(numberToBeSubtracted, num);
                numberToBeSubtracted->digits_whole = rounded_index + 1;
                Number* numberToAddWhenRounding = setNewNumber();
                subtractNumbers(numberToAddWhenRounding, roundingTens, numberToBeSubtracted);
                plusEquals(num, numberToAddWhenRounding);

            }
        }
        if (num->decimal_part[0] > 5) {
            increment(num);
        }
        // FIXME memory leak
        num->digits_decimal = 1;
        num->decimal_part[0] = 0;
    } else if (num->digits_whole < precision) {
        // TODO shift comma manually
        Number* ShiftedComma = setNewNumber();
        multiplyNumbers(ShiftedComma, num, raiseByPow(ten, num->digits_decimal));
        setAbsolutePrecision(ShiftedComma, precision);

        //divideEquals(ShiftedComma, raiseByPow(ten, num->digits_decimal));
        Number* temp = setNewNumber();
        temp->digits_whole = ShiftedComma->digits_whole - num->digits_decimal;
        temp->digits_decimal = num->digits_decimal;

        for (int i = ShiftedComma->digits_whole-1, j = 0; i >= num->digits_decimal; i--, j++) {
            temp->whole_part[temp->digits_whole-1-j] = ShiftedComma->whole_part[i];
        }

        for (int i = num->digits_decimal-1, j = 0; i >= 0; i--, j++) {
            temp->decimal_part[j] = ShiftedComma->whole_part[i];
        }

        fixNumber(temp);
        assign(num, temp);
        // TODO do without ShiftedComma variable
        free(temp);
        free(ShiftedComma);
    }
}




void freeTable() {
    for (int i = 0; i < table->capacity; i++) {
        free(table->numbers[i]);
    }
    free(table->numbers);
    free(table);
}

