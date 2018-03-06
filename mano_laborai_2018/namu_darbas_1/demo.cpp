/*=============================================================================
 | Program for testing Big Numbers ADT without the user input
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Header file with useful debugging macros
#include "dbg.h"

#include "numbers.h"


int main() {
    Number* num1 = setNumberFromChar((char*)"81234812384091238.8901234");
    Number* num2 = setNumberFromChar((char*)"-12380441238423.82431432");

    Number* res;
    int cmp;

    res = addNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81222431942852815.06580908") == 0 && "Addition test01 failed");

    res = subtractNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81247192825329662.71443772") == 0 && "Subtraction test01 failed");
    
    res = multiplyNumbers(num1, num2);
    assert(strcmp(numToChar(res), "-1005722821235625557767394406067.695067825187088") == 0 && "Multiplication test01 failed");

    // TODO division testing
    // ...
    // ...
    
    cmp = compareEqual(num1, num2);
    assert(cmp == 0 && "compareEqual test01 failed");

    cmp = compareNotEqual(num1, num2);
    assert(cmp == 1 && "compareNotEqual test01 failed");

    cmp = compareGreaterThan(num1, num2);
    assert(cmp == 1 && "compareGreaterThan test01 failed");

    cmp = compareLessThan(num1, num2);
    assert(cmp == 0 && "compareLessThan test01 failed");

    cmp = compareGreaterThanOrEqual(num1, num2);
    assert(cmp == 1 && "compareGreaterThanOrEqual test01 failed");

    cmp = compareLessThanOrEqual(num1, num2);
    assert(cmp == 0 && "compareLessThanOrEqual test01 failed");
    
    assign(num1, num2);
    assert(strcmp(numToChar(num1), numToChar(num2)) == 0 && "Assign test01 failed");

}

