#ifndef HASH_TABLE_H
#define HASH_TABLE_H

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

typedef struct {
    int key;
    char value;
} Elem;

// description
const int P = 1009;

// description
int hash(int key);
// description
void init(Elem table[]);
// description
int insert(Elem table[], int new_key, char new_value);
// description
int find(Elem table[], int searched_key);
// description
void print(Elem table[]);

#endif
