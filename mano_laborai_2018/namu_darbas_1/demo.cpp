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

    res = addNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81222431942852815.06580908") == 0 && "Addition test01 failed");

    res = subtractNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81247192825329662.71443772") == 0 && "Subtraction test01 failed");
    
    res = multiplyNumbers(num1, num2);
    assert(strcmp(numToChar(res), "-1005722821235625557767394406067.695067825187088") == 0 && "Multiplication test01 failed");

    res = divideNumbers(num1, num2);
    assert(strcmp(numToChar(res), "-6561.544198600258072584801336513697992925982204711190874405227531521729371470501450875341584693541694678610733689628050801447636391038159947299252507253926596300570699756129255217355600294010456506944330918") == 0 && "Division test01 failed");

    // TODO modulus testing
    // ...
    // ...

    int cmp;

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

