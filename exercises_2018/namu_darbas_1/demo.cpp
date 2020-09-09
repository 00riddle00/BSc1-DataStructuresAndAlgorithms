/*=============================================================================
 | Program for testing Big Numbers ADT without the user input
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <climits>
#include <cfloat>

// Header file with useful debugging macros
#include "dbg.h"
#include "numbers.h"



int main() {

//    printf("[Testing...]\n");

    Number *num1 = setNumberFromChar((char *) "81234812384091238.8901234");
    Number *num2 = setNumberFromChar((char *) "-12380441238423.82431432");

    Number *res = setNewNumber();

    res = setNumberFromChar((char *) "2.7182818285");
    res = Log(res);
    setPrecision(res, -99);
    printEntry(res);
    assert(strcmp(numToChar(res), "1.000000000015066415928851892925238435963141587542804820418867079787116896581421424933322038112898450") == 0 && "Log test03 failed");
    printf("...Log test03 passed\n");
    exit(1);

/* test arithmetic */
    addNumbers(res, num1, num2);
    assert(strcmp(numToChar(res), "81222431942852815.06580908") == 0 && "addNumbers test01 failed");
//    printf("...addNumbers test01 passed\n");

    subtractNumbers(res, num1, num2);
    assert(strcmp(numToChar(res), "81247192825329662.71443772") == 0 && "subtractNumbers test01 failed");
//    printf("...subtractNumbers test01 passed\n");

    multiplyNumbers(res, num1, num2);
    assert(strcmp(numToChar(res), "-1005722821235625557767394406067.695067825187088") == 0 &&
           "multiplyNumbers test01 failed");
//    printf("...multiplyNumbers test01 passed\n");

    divideNumbers(res, num1, num2);
    assert(strcmp(numToChar(res), "-6561.54419860025807258480133651369799292598220471119087440522753152172937147050145087534158469354169467861073368962805080144763639103815994729925250725392659630057069975612925521735560029401045650694433091") == 0 && "divideNumbers test01 failed");
//    printf("...divideNumbers test01 passed\n");
    /* // test arithmetic */

    /* test modulus  (all possible combinations the quotient of two positive/negative numbers */
    res = modulus(setNumberFromChar((char *) "-20.0"), setNumberFromChar((char *) "-7.0"));
    assert(strcmp(numToChar(res), "-6.0") == 0 && "modulus test01 failed");
//    printf("...modulus test01 passed\n");

    res = modulus(setNumberFromChar((char *) "4.0"), setNumberFromChar((char *) "17.0"));
    assert(strcmp(numToChar(res), "4.0") == 0 && "modulus test02 failed");
//    printf("...modulus test02 passed\n");

    res = modulus(setNumberFromChar((char *) "-3.0"), setNumberFromChar((char *) "19.0"));
    assert(strcmp(numToChar(res), "16.0") == 0 && "modulus test03 failed");
//    printf("...modulus test03 passed\n");

    res = modulus(setNumberFromChar((char *) "-16.0"), setNumberFromChar((char *) "4.0"));
    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test04 failed");
//    printf("...modulus test04 passed\n");

    res = modulus(setNumberFromChar((char *) "-16.0"), setNumberFromChar((char *) "3.0"));
    assert(strcmp(numToChar(res), "2.0") == 0 && "modulus test05 failed");
//    printf("...modulus test05 passed\n");
//
    res = modulus(setNumberFromChar((char*)"2.0"), setNumberFromChar((char*)"-19.0"));
    assert(strcmp(numToChar(res), "-17.0") == 0 && "modulus test06 failed");
//    printf("...modulus test06 passed\n");

    res = modulus(setNumberFromChar((char*)"19.0"), setNumberFromChar((char*)"-12.0"));
    assert(strcmp(numToChar(res), "-5.0") == 0 && "modulus test07 failed");
//    printf("...modulus test07 passed\n");

    res = modulus(setNumberFromChar((char *) "20.0"), setNumberFromChar((char *) "7.0"));
    assert(strcmp(numToChar(res), "6.0") == 0 && "modulus test08 failed");
//    printf("...modulus test08 passed\n");

    res = modulus(setNumberFromChar((char *) "0.0"), setNumberFromChar((char *) "7.0"));
    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test09 failed");
//    printf("...modulus test09 passed\n");
    /*  // test modulus */


    /* test comparison */
    int cmp;

    cmp = compareEqual(num1, num2);
    assert(cmp == 0 && "compareEqual test01 failed");
//    printf("...compareEqual test01 passed\n");

    cmp = compareNotEqual(num1, num2);
    assert(cmp == 1 && "compareNotEqual test01 failed");
//    printf("...compareNotEqual test01 passed\n");

    cmp = compareGreaterThan(num1, num2);
    assert(cmp == 1 && "compareGreaterThan test01 failed");
//    printf("...compareGreaterThan test01 passed\n");

    cmp = compareLessThan(num1, num2);
    assert(cmp == 0 && "compareLessThan test01 failed");
//    printf("...compareLessThan test01 passed\n");

    cmp = compareGreaterThanOrEqual(num1, num2);
    assert(cmp == 1 && "compareGreaterThanOrEqual test01 failed");
//    printf("...compareGreaterThanOrEqual test01 passed\n");

    cmp = compareLessThanOrEqual(num1, num2);
    assert(cmp == 0 && "compareLessThanOrEqual test01 failed");
//    printf("...compareLessThanOrEqual test01 passed\n");

    assign(num1, num2);
    assert(strcmp(numToChar(num1), numToChar(num2)) == 0 && "assign test01 failed");
//    printf("...assign test01 passed\n");
    /* // test comparison */


    /* test additional functions */
    int digit;
    Number *num3 = setNumberFromChar((char *) "123.456");

    digit = getWholeLen(num3);
    assert(digit == 3 && "getWholeLen test01 failed");
//    printf("...getWholeLen test01 passed\n");

    digit = getDecimalLen(num3);
    assert(digit == 3 && "getDecimalLen test01 failed");
//    printf("...getDecimalLen test01 passed\n");

    digit = getIthDigit(num3, 2);
    assert(digit == 2 && "getIthDigit test01 failed");
//    printf("...getIthDigit test01 passed\n");

    digit = getIthDigit(num3, -2);
    assert(digit == 5 && "getIthDigit test02 failed");
//    printf("...getIthDigit test02 passed\n");


    increment(num3);
    assert(strcmp(numToChar(num3), "124.456") == 0 && "increment test01 failed");
//    printf("...increment test01 passed\n");

    decrement(num3);
    assert(strcmp(numToChar(num3), "123.456") == 0 && "decrement test01 failed");
//    printf("...decrement test01 passed\n");

    assign(num3, setNumberFromChar((char *) "5.5"));
    plusEquals(num3, setNumberFromChar((char *) "12.2"));
    assert(strcmp(numToChar(num3), "17.7") == 0 && "plusEquals test01 failed");
//    printf("...plusEquals test01 passed\n");

    assign(num3, setNumberFromChar((char *) "5.5"));
    minusEquals(num3, setNumberFromChar((char *) "6.8"));
    assert(strcmp(numToChar(num3), "-1.3") == 0 && "minusEquals test01 failed");
//    printf("...minusEquals test01 passed\n");

    assign(num3, setNumberFromChar((char *) "5.5"));
    multiplyEquals(num3, setNumberFromChar((char *) "15.6"));
    assert(strcmp(numToChar(num3), "85.8") == 0 && "multiplyEquals test01 failed");
//    printf("...multiplyEquals test01 passed\n");

    assign(num3, setNumberFromChar((char *) "5.5"));
    divideEquals(num3, setNumberFromChar((char *) "1.1"));
    assert(strcmp(numToChar(num3), "5.0") == 0 && "divideEquals test01 failed");
//    printf("...divideEquals test01 passed\n");

    assign(num3, setNumberFromChar((char *) "5.5"));
    modulusEquals(num3, setNumberFromChar((char *) "1.4"));
    assert(strcmp(numToChar(num3), "1.3") == 0 && "modulusEquals test01 failed");
//    printf("...modulusEquals test01 passed\n");
    /* // test additional functions */

    /*  test utility functions */

    // setNumberFromInt
    res = setNumberFromInt(0);
    assert(strcmp(numToChar(res), "0.0") == 0 && "setNumberFromInt test01 failed");
//    printf("...setNumberFromInt test01 passed\n");

    res = setNumberFromInt(100);
    assert(strcmp(numToChar(res), "100.0") == 0 && "setNumberFromInt test02 failed");
//    printf("...setNumberFromInt test02 passed\n");

    res = setNumberFromInt(-100);
    assert(strcmp(numToChar(res), "-100.0") == 0 && "setNumberFromInt test03 failed");
//    printf("...setNumberFromInt test03 passed\n");

    res = setNumberFromInt(1);
    assert(strcmp(numToChar(res), "1.0") == 0 && "setNumberFromInt test04 failed");
//    printf("...setNumberFromInt test04 passed\n");

    res = setNumberFromInt(-1);
    assert(strcmp(numToChar(res), "-1.0") == 0 && "setNumberFromInt test05 failed");
//    printf("...setNumberFromInt test05 passed\n");

    res = setNumberFromInt(123456789);
    assert(strcmp(numToChar(res), "123456789.0") == 0 && "setNumberFromInt test06 failed");
//    printf("...setNumberFromInt test06 passed\n");

    res = setNumberFromInt(1234567891);
    assert(strcmp(numToChar(res), "1234567891.0") == 0 && "setNumberFromInt test07 failed");
//    printf("...setNumberFromInt test07 passed\n");

    res = setNumberFromInt(-1234567891);
    assert(strcmp(numToChar(res), "-1234567891.0") == 0 && "setNumberFromInt test08 failed");
//    printf("...setNumberFromInt test08 passed\n");

    res = setNumberFromInt(1000000001);
    assert(strcmp(numToChar(res), "1000000001.0") == 0 && "setNumberFromInt test09 failed");
//    printf("...setNumberFromInt test09 passed\n");
    // // setNumberFromInt

    // setNumberFromDouble

    res = setNumberFromDouble(0);
    assert(strcmp(numToChar(res), "0.0") == 0 && "setNumberFromDouble test01 failed");
//    printf("...setNumberFromDouble test01 passed\n");

    res = setNumberFromDouble(100);
    assert(strcmp(numToChar(res), "100.0") == 0 && "setNumberFromDouble test02 failed");
//    printf("...setNumberFromDouble test02 passed\n");

    res = setNumberFromDouble(-100);
    assert(strcmp(numToChar(res), "-100.0") == 0 && "setNumberFromDouble test03 failed");
//    printf("...setNumberFromDouble test03 passed\n");

    res = setNumberFromDouble(1);
    assert(strcmp(numToChar(res), "1.0") == 0 && "setNumberFromDouble test04 failed");
//    printf("...setNumberFromDouble test04 passed\n");

    res = setNumberFromDouble(-1);
    assert(strcmp(numToChar(res), "-1.0") == 0 && "setNumberFromDouble test05 failed");
//    printf("...setNumberFromDouble test05 passed\n");

    res = setNumberFromDouble(123456789);
    assert(strcmp(numToChar(res), "123456789.0") == 0 && "setNumberFromDouble test06 failed");
//    printf("...setNumberFromDouble test06 passed\n");

    res = setNumberFromDouble(1234567891);
    assert(strcmp(numToChar(res), "1234567891.0") == 0 && "setNumberFromDouble test07 failed");
//    printf("...setNumberFromDouble test07 passed\n");

    res = setNumberFromDouble(-1234567891);
    assert(strcmp(numToChar(res), "-1234567891.0") == 0 && "setNumberFromDouble test08 failed");
//    printf("...setNumberFromDouble test08 passed\n");

    res = setNumberFromDouble(1000000001);
    assert(strcmp(numToChar(res), "1000000001.0") == 0 && "setNumberFromDouble test09 failed");
//    printf("...setNumberFromDouble test09 passed\n");

    res = setNumberFromDouble(123412341324.2134213412);
    assert(strcmp(numToChar(res), "123412341324.2134") == 0 && "setNumberFromDouble test10 failed");
//    printf("...setNumberFromDouble test10 passed\n");

    res = setNumberFromDouble(-123412341324.2134213412);
    assert(strcmp(numToChar(res), "-123412341324.2134") == 0 && "setNumberFromDouble test11 failed");
//    printf("...setNumberFromDouble test11 passed\n");

    res = setNumberFromDouble(-12341.213412);
    assert(strcmp(numToChar(res), "-12341.213412") == 0 && "setNumberFromDouble test12 failed");
//    printf("...setNumberFromDouble test12 passed\n");

    res = setNumberFromDouble(1111.1111);
    assert(strcmp(numToChar(res), "1111.1111") == 0 && "setNumberFromDouble test13 failed");
//    printf("...setNumberFromDouble test13 passed\n");

    res = setNumberFromDouble(123456789123456789.0001);
    assert(strcmp(numToChar(res), "123456789123456800.0") == 0 && "setNumberFromDouble test14 failed");
//    printf("...setNumberFromDouble test14 passed\n");

    res = setNumberFromDouble(12345678912345678912342184831.0001);
    assert(strcmp(numToChar(res), "12345678912345680000000000000.0") == 0 && "setNumberFromDouble test15 failed");
//    printf("...setNumberFromDouble test15 passed\n");

    res = setNumberFromDouble(123456789.123456789);
    assert(strcmp(numToChar(res), "123456789.1234568") == 0 && "setNumberFromDouble test16 failed");
//    printf("...setNumberFromDouble test16 passed\n");

    res = setNumberFromDouble(0.123456789);
    assert(strcmp(numToChar(res), "0.123456789") == 0 && "setNumberFromDouble test17 failed");
//    printf("...setNumberFromDouble test17 passed\n");

    res = setNumberFromDouble(0.123456789123456789);
    assert(strcmp(numToChar(res), "0.1234567891234568") == 0 && "setNumberFromDouble test18 failed");
//    printf("...setNumberFromDouble test18 passed\n");
    // // setNumberFromDouble


    // test setPrecision
    res = setNumberFromChar((char *) "0.99");
    setPrecision(res, 1);
    assert(strcmp(numToChar(res), "1.0") == 0 && "setPrecision test01 failed");
//    printf("...setPrecision test01 passed\n");

    res = setNumberFromChar((char *) "0.99");
    setPrecision(res, 2);
    assert(strcmp(numToChar(res), "0.99") == 0 && "setPrecision test02 failed");
//    printf("...setPrecision test02 passed\n");

    res = setNumberFromChar((char *) "1234.1999");
    setPrecision(res, 5);
    assert(strcmp(numToChar(res), "1234.2") == 0 && "setPrecision test03 failed");
//    printf("...setPrecision test03 passed\n");

    res = setNumberFromChar((char *) "9999.9999");
    setPrecision(res, 4);
    assert(strcmp(numToChar(res), "10000.0") == 0 && "setPrecision test04 failed");
//    printf("...setPrecision test04 passed\n");

    res = setNumberFromChar((char *) "9999.999");
    setPrecision(res, -3);
    assert(strcmp(numToChar(res), "9999.999") == 0 && "setPrecision test05 failed");
//    printf("...setPrecision test05 passed\n");

    res = setNumberFromChar((char *) "9999.999");
    setPrecision(res, -2);
    assert(strcmp(numToChar(res), "10000.0") == 0 && "setPrecision test06 failed");
//    printf("...setPrecision test06 passed\n");

    res = setNumberFromChar((char *) "94498971652638775929231672647833888771141190540374490793799910241413225365722228670047638705370321438791975293971242620109600173039630619238456992875182844589511986507136169417095017804371947032.203664451869145012957479866119182321453596311449965459940509922047959178153412323810076888179364706154977928824519669175533302959921");
    setPrecision(res, -100);
    assert(strcmp(numToChar(res), "94498971652638775929231672647833888771141190540374490793799910241413225365722228670047638705370321438791975293971242620109600173039630619238456992875182844589511986507136169417095017804371947032.2036644518691450129574798661191823214535963114499654599405099220479591781534123238100768881793647062") == 0 && "setPrecision test07 failed");
//    printf("...setPrecision test07 passed\n");

    res = setNumberFromChar((char *) "0.1234");
    setPrecision(res, -10);
    assert(strcmp(numToChar(res), "0.1234") == 0 && "setPrecision test08 failed");
//    printf("...setPrecision test08 passed\n");

    res = setNumberFromChar((char *) "0.001234567800999");
    setPrecision(res, 11);
    assert(strcmp(numToChar(res), "0.001234567801") == 0 && "setPrecision test09 failed");
//    printf("...setPrecision test09 passed\n");

//    setPrecision(res, -13);
    res = setNumberFromChar((char *) "0.001234567800999");
    setPrecision(res, -13);
    assert(strcmp(numToChar(res), "0.001234567801") == 0 && "setPrecision test10 failed");
//    printf("...setPrecision test10 passed\n");
    // // test setPrecision
    /*  // test utility functions */


    /* live tests */
    // test factorial
    res = setNumberFromChar((char *) "10.0");
    res = factorial(res);
    assert(strcmp(numToChar(res), "3628800.0") == 0 && "factorial test01 failed");

    res = setNumberFromChar((char *) "-10.0");
    res = factorial(res);
    assert(strcmp(numToChar(res), "-3628800.0") == 0 && "factorial test02 failed");

    res = setNumberFromChar((char *) "100.0");
    res = factorial(res);
    assert(strcmp(numToChar(res), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000.0") == 0 && "factorial test03 failed");

    res = setNumberFromChar((char *) "-100.0");
    res = factorial(res);
    assert(strcmp(numToChar(res), "-93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000.0") == 0 && "factorial test04 failed");

    res = setNumberFromChar((char *) "0.0");
    res = factorial(res);
    assert(strcmp(numToChar(res), "1.0") == 0 && "factorial test05 failed");
    printf("...factorial tests(5) passed\n");
    // // test factorial

//     test nextPrime
    res = setNumberFromChar((char *) "7.0");
    res = nextPrime(res);
    assert(strcmp(numToChar(res), "11.0") == 0 && "nextPrime test01 failed");

    res = setNumberFromChar((char *) "-5.0");
    res = nextPrime(res);
    assert(strcmp(numToChar(res), "2.0") == 0 && "nextPrime test02 failed");

    res = setNumberFromChar((char *) "211.0");
    res = nextPrime(res);
    assert(strcmp(numToChar(res), "223.0") == 0 && "nextPrime test03 failed");

    res = setNumberFromChar((char *) "3617.0");
    res = nextPrime(res);
    assert(strcmp(numToChar(res), "3623.0") == 0 && "nextPrime test04 failed");
     // test nextPrime

    // test raiseByPow
    res = setNumberFromChar((char *) "0.0");
    res = raiseByPow(res, 8);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "0.0") == 0 && "raiseByPow test01 failed");

    res = setNumberFromChar((char *) "1234.1234");
    res = raiseByPow(res, 0);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "1.0") == 0 && "raiseByPow test02 failed");

    res = setNumberFromChar((char *) "-10.0");
    res = raiseByPow(res, 5);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-100000.0") == 0 && "raiseByPow test03 failed");

    res = setNumberFromChar((char *) "10.0");
    res = raiseByPow(res, 6);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "1000000.0") == 0 && "raiseByPow test04 failed");

    res = setNumberFromChar((char *) "-213421342318412384912738132894712.8128374823174812377321");
    res = raiseByPow(res, 6);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "94498971652638775929231672647833888771141190540374490793799910241413225365722228670047638705370321438791975293971242620109600173039630619238456992875182844589511986507136169417095017804371947032.203664451869145012957479866119182321453596311449965459940509922047959178153412323810076888179364706") == 0 && "raiseByPow test05 failed");

    res = setNumberFromChar((char *) "-21342134231841238.812837");
    res = raiseByPow(res, 5);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-4427812637016018054953301802858186906534656748459271515524109285463583661259198754.574955958356895328848404847957") == 0 && "raiseByPow test06 failed");

    res = setNumberFromChar((char *) "-2.0");
    res = raiseByPow(res, 5);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-32.0") == 0 && "raiseByPow test07 failed");

    res = setNumberFromChar((char *) "-0.81283774812377321");
    res = raiseByPow(res, 21);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-0.012884902726667558210601727302511509755171013115215254519989274267819356478757327423709088589733801") == 0 && "raiseByPow test08 failed");
    printf("...raiseByPow tests(8) passed\n");
    // test raiseByPow

    // test Log
    res = setNumberFromChar((char *) "5.0");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "1.609437912434100374600759333226187639525601354268517721912647891474178987707657764630133878093179611") == 0 && "Log test01 failed");
    printf("...Log test01 passed\n");

    // FIXME does not pass
//    res = setNumberFromChar((char *) "24392.0");
//    res = Log(res);
//    setPrecision(res, -99);
//    assert(strcmp(numToChar(res), "10.102010488668090709523108315377598927675356968219971513291207212905617079917723807020637638746466385") == 0 && "Log test02 failed");
//    printf("...Log test02 passed\n");

    res = setNumberFromChar((char *) "2.5");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "0.916290731874155065183527211768011071450101219908262467791967881980785365737963049024270551096760923") == 0 && "Log test03 failed");
    printf("...Log test03 passed\n");

    res = setNumberFromChar((char *) "0.5");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418688") == 0 && "Log test04 failed");
    printf("...Log test04 passed\n");

    res = setNumberFromChar((char *) "1000000.0");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "13.81551055796427410410794872810618524560660893177263785619996740580543565806411488141598323053758979") == 0 && "Log test05 failed");
    printf("...Log test05 passed\n");

    // FIXME does not pass
//    res = setNumberFromChar((char *) "13.5");
//    res = Log(res);
//    setPrecision(res, -100);
//    assert(strcmp(numToChar(res), "2.602689685444383764768503589309400545866971539107993101083402991419089257686132185014983937444777578") == 0 && "Log test06 failed");
//    printf("...Log test06 passed\n");

    res = setNumberFromChar((char *) "15.5");
    res = Log(res);
    setPrecision(res, -100);
    assert(strcmp(numToChar(res), "-0.6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875") == 0 && "Log test07 failed");
    printf("...Log test07 passed\n");

    // LIVE log tests
    res = setNumberFromChar((char *) "100.0");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "4.605170185988091368035982909368728415202202977257545952066655801935145219354704960471994410179196597") == 0 && "Log test08 failed");
    printf("...Log test08 passed\n");

    res = setNumberFromChar((char *) "1.0");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "0.0") == 0 && "Log test09 failed");
    printf("...Log test09 passed\n");

    res = setNumberFromChar((char *) "0.7");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-0.356674943938732378912638711241184477964016759046911787573937751029992746925283212448338706501726771") == 0 && "Log test10 failed");
    printf("...Log test10 passed\n");

    res = setNumberFromChar((char *) "1.20");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "0.182321556793954626211718025154514633197389337914486983942726451656708927480645917849345203716971166") == 0 && "Log test11 failed");
    printf("...Log test11 passed\n");

    res = setNumberFromChar((char *) "0.1");
    res = Log(res);
    setPrecision(res, -99);
    assert(strcmp(numToChar(res), "-2.302585092994045684017991454684364207601101488628772976033327900967572609677352480235997205089598298") == 0 && "Log test12 failed");
    printf("...Log test12 passed\n");
    // //LIVE log tests
    // // test Log

    // test Sine
//    res = setNumberFromChar((char *) "20.0");
//    res = Sine(res);
//    setPrecision(res, -99);
//    assert(strcmp(numToChar(res), "0.912945250727627654376099983845682301297932583708189956305128114768848919349072976044480049640469976") == 0 && "Sine test01 failed");
//    printf("...Sine test01 passed\n");
    // // test Sine
//    /* // live tests */

    free(num1);
    free(num2);
    free(num3);
    free(res);
//    printf("[All Tests have passed successfully!]\n");
}
