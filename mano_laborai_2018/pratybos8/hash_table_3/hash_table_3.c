/*=============================================================================
 |
 |  Assignment:  Exercise 8
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  March 25th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Hash table implementation with custom hash function
 |                
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |                The output is each algorithm's each iteration, with
 |                comparison and assignment counts, and also processor
 |                clock times and average completion time, in seconds.
 |                Finally, the average data of each algorithm is presented.
 |                At the end, the algorithms are sorted from best to worst
 |                by their average time.
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct {
    int key;
    char value[10];
} Elem;



const int P = 127;

int hash(char value[10]) {
    return (int)value[0] % P;
}

void init(Elem table[]) {

    for (int i = 0; i < P; i++) {
        table[i].key = i; 
        table[i].value[0] = '&';
    }
}

int insert(Elem table[], char new_value[10]) {
    int H = hash(new_value);

    while (table[H].value[0] != '&') {
        // linear probing
        H = (H + 1) % P;
    }

    for (int i = 0; i < 10; i++) {
        table[H].value[i] = new_value[i];
    }
    return H;
}

int find(Elem table[], char searched_value[10]) {
    int H = hash(searched_value);
    int found;

    while ((strcmp(table[H].value, searched_value) != 0) && table[H].value[0] != '&') {
        H = (H + 1) % P;
    }

    if (strcmp(table[H].value, searched_value) == 0) {
        return H;
    } else {
        return -1;
    }
}

void print(Elem table[]) {

    printf("-------------\n");
    printf("Hash table:\n");
    printf("-------------\n");

    for (int i = 0; i < P; i++) {
        if (table[i].value[0] == '&') {
            printf("%3d: (empty)\n", i);
        } else {
            printf("%3d: %10s\n", i, table[i].value);
        }
                      
    }
    printf("-------------\n");
}


int main() {

    Elem table[P];
    init(table);

    int key1 = insert(table, "india");
    int key2 = insert(table, "europe");

    printf("key1: %d, key2: %d\n", key1, key2);

    int index = find(table, "india");
    if (index != -1) {
        printf("Found '%s': index in a table is %d\n", "india", index);
    } else {
        printf("Element '%s' not found\n", "india");
    }

    print(table);
}
