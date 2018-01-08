/*=============================================================================
 |
 |  Assignment:  Program #2
 |  Task number:  #13
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 3rd group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  April 28th, 2016
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -xc -g -lm -std=c99 uzduotis_2.c -o uzduotis_2
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A program which sorts numbers in an increasing order,
 |                using quicksort algorithm.
 |
 |	    Input:    The program takes two command line arguments: input and
 |                output file (text files)
 |
 |	    Output:   Validation errors are displayed to the standard output.
 |                If program executes successfully, user's defined output
 |                file (text file) is created with the new data in it.
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/


#include <stdio.h>
#include <stdlib.h>

#include <errno.h>


// function which sorts numbers by increasing order,
// using quicksort method.
//
// ::params: x - number array
// ::params: first - index of the first element in the array
// ::params: second - index of the last element in the array
void quicksort(int *x, int first, int last);

// function which exits the program. Called on validation errors
// or memory errors.
//
// ::params: message - error message to be displayed
void die(char *message);


int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Input and output file is required.\n"
                       "USAGE: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        die("Such input file does not exist.\n");
    }

    FILE *output = fopen(argv[2], "w");

    if (!output) {
        fclose(input);
        die("Cannot write to output file (output file should be a "
                       "simple text file).\n");
    }

    int *num_array = NULL;
    num_array = malloc(10 * sizeof(int));

    if (!num_array) {
        die("Memory error!\n");
    }

    int i = 0;

    int count = 0;

    while (fscanf(input, "%d,", &num_array[count++]) == 1) {
        if (count % 10 == 0) {
            // incrementing array memory, to hold 10 more integers.
            num_array = realloc(num_array, (count + 10) * sizeof(int));
            if (!num_array) {
                die("Memory error!\n");
            }
        }
    }

    quicksort(num_array, 0, count - 2);

    for (i = 0; i < count - 1; i++) {
        fprintf(output, "%d ", num_array[i]);
    }
    printf("Success!\n");

    free(num_array);

    fclose(input);
    fclose(output);

    return 0;
}


void quicksort(int *x, int first, int last) {
    int pivot, j, temp, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (x[i] <= x[pivot] && i < last)
                i++;
            while (x[j] > x[pivot])
                j--;
            if (i < j) {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }

        temp = x[pivot];
        x[pivot] = x[j];
        x[j] = temp;
        quicksort(x, first, j - 1);
        quicksort(x, j + 1, last);

    }
}


void die(char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("%s\n", message);
    }
    exit(1);
}
