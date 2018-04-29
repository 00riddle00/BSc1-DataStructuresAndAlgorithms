/*=============================================================================
 |
 |  Assignment:  Exercise 8
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  April 28th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Hash table ADT
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
#include <math.h>

#include "dbg.h"
#include "hash_table.h"

int hash(int key) {
    return key % P;
}

void init(Elem table[]) {

    for (int i = 0; i < P; i++) {
        table[i].key = INT_MAX; // the field is free, if table[i].key == INT_MAX 
                            // the field is taken, if table[i].key != INT_MAX 
    }
}

int insert(Elem table[], int new_key, char new_value) {
    int H = hash(new_key);

    int i = 1;
    while (table[H].key != INT_MAX) {
        // quadratic probing
        H = (int)(H + pow(i,2) - pow(i-1,2)) % P;
        i++;
    }

    int found;
    table[H].key = new_key;
    table[H].value = new_value;
    return H;
}

int find(Elem table[], int searched_key) {
    int H = hash(searched_key);

    while (table[H].key != searched_key && table[H].key != INT_MAX) {
        H = (H + 1) % P;
    }

    if (table[H].key == searched_key) {
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
        if (table[i].key == INT_MAX) {
            printf("%2d: (empty)\n", i);
        } else {
            printf("%2d: %7d\n", i, table[i].key);
        }
                      
    }
    printf("-------------\n");
}

