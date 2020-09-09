#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>


// other includes and definitions
/* YOUR CODE HERE */
#include "numbers.h"


using namespace std;

// define your datatype here
typedef Number* myType;

// convert from string to myType
myType convert(string s){
	/* YOUR CODE HERE */
    return setNumberFromChar((char*)s.c_str());
}
// convert from myType to string
string toStr(myType m){
	/* YOUR CODE HERE */
	char* num = numToChar(m);
	return string(num);
}

// compute a factorial
myType myFactorial(int n);

// finds the next prime, bigger than n					
myType myPrime(myType n); 	

// finds d to the power of (positive) p					
myType myPow(double d, int p); 	

// finds (natural) logarithm of d				
myType myLog(double d); 

// finds sinus of d						
myType mySin(double d); 

// finds square root of d						
myType mySqrt(double d); 

// finds a value of PI with n digits of precision (zeroes afterwards)						
myType myPi(int n); 		

// computes an average of n valus in an array 					
myType myAvg(myType *data, int n); 		

// search for a value in an array of n numbers and return an index		
int myFind(myType *data, int n, myType value); 	

// sorts data in an array of n numbers by (optimized) bubble sort algorithm
void mySort(myType *data, int n); 				

myType myFactorial(int n){
	/* YOUR CODE HERE */
    return factorial(setNumberFromInt(n));
}
myType myPrime(myType n){
	/* YOUR CODE HERE */
    return nextPrime(n);
}
myType myPow(double d, int p){
	/* YOUR CODE HERE */
    return raiseByPow(setNumberFromDouble(d), p);
}
myType myLog(double d){
	/* YOUR CODE HERE */
    myType res = Log(setNumberFromDouble(d));
    setPrecision(res, -99);
    return res;

}
myType mySin(double d){
	/* YOUR CODE HERE */
	myType res = Sine(setNumberFromDouble(d));
	setPrecision(res, -99);
	return res;
}
myType mySqrt(double d){
	/* YOUR CODE HERE */
} 
myType myPi(int n){
	/* YOUR CODE HERE */
}
myType myAvg(myType *data, int n){
	/* YOUR CODE HERE */
    return getAvg(data, n);
}
int myFind(myType *data, int n, myType value){
	/* YOUR CODE HERE */
	return findNum(data, n, value);
}
void mySort(myType *data, int n){
	/* YOUR CODE HERE */
	sortNums(data, n);
}

/* DO NOT MODIFY CODE BELOW */

int main(){
	while(1){
		int x = -1;
		cin >> x;	
		if (x == 0)
			break;
		string s;
		double d;
		int n;
		myType *data = NULL;
		string output;
		switch(x){
			case 1:
				cin >> n;
				cout << (output = toStr(myFactorial(n))) << endl;
				break;
			case 2:
				cin >> s;
				cout << (output = toStr(myPrime(convert(s)))) << endl;
				break;
			case 3:
				int p;
				cin >> d >> p;
				cout << (output = toStr(myPow(d, p))) << endl;
				break;
			case 4:
				cin >> d;
				cout << (output = toStr(myLog(d))) << endl;
				break;
			case 5:
				cin >> d;
				cout << (output = toStr(mySin(d))) << endl;
				break;
			case 6:
				cin >> d;
				cout << (output = toStr(mySqrt(d))) << endl;
				break;
			case 7:
				cin >> n;
				cout << (output = toStr(myPi(n))) << endl;
				break;
			case 8:
				cin >> n;	
				data = new myType[n];		
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cout << (output = toStr(myAvg(data, n))) << endl;
				delete [] data;
				break;
			case 9:
				cin >> n;			
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cin >> s;
				int f;			
				cout << (f = myFind(data, n, convert(s))) << endl;
				delete [] data;
				break;
			case 10:
				cin >> n;			
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				mySort(data, n);
				for(int i = 0; i < n; ++i){
					cout << (output = toStr(data[i])) << endl;
				}
				delete [] data;
				break;
		}
	}
	return 0;	
}
