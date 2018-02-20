// Stack - Reverse a string
#include <iostream>
#include <cstring>
#include <stack> // stack from standard template library (STL)
using namespace std;

// OOP implementation
/*class Stack*/
//{
    //private:
        //char A[101];
        //int top;
    //public:
        //void Push(int x);
        //void Pop();
        //int Top();
        //bool isEmpty();
//};

void Reverse(char C[], int n)
{
    //Stack S; <-- our implementation
    stack<char> S; // <-- STL implementation
    
    // loop for push
    for(int i=0; i < n; i++) {
        S.push(C[i]);
    }
    // loop for pop
    for (int i = 0; i < n; i++) {
        C[i] = S.top(); // overwrite the character at index i.
        S.pop(); // perform pop.
    }
}

int main() {
    char C[51];
    printf("Enter a string");
    //gets(C);  // <-- nesuveikia
    strcpy(C, "hello"); 
    printf("\nThe string is: hello\n");
    Reverse(C, strlen(C));
    printf("Output = %s\n", C);

    return 0;
}
