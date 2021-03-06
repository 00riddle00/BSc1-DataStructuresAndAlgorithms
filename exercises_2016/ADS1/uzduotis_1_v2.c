/*=============================================================================
 |
 |  Assignment:  Program #1
 |  Task number:  #13
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 3rd group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  April 26th, 2016
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |   To Compile:  gcc -Wall -xc -g -lm -std=c99 uzduotis_1.c -o uzduotis_1
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  A program which removes words from the text which have a
 |                numeral in the middle
 |
 |  Constraints:  [1] Currently the program recognizes only a single separator
 |                (and ignores it from the word char count) symbol after a word.
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

#include <ctype.h>
#include <string.h>


#define MAX_LINE_SIZE 255


// Remove target words (having a numeral in the middle)
// and write the contents of the input file with target words
// removed to the output file
//
//::params: input - input file (text file)
//::params: output - output file (text file)
void rm_target_words(FILE *input, FILE *output);


int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Input and output file is required.\n"
                       "USAGE: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        printf("Such input file does not exist.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");

    if (!output) {
        printf("Cannot write to output file (output file should be a "
                       "simple text file).\n");
        fclose(input);
        return 1;
    }

    rm_target_words(input, output);

    fclose(input);
    fclose(output);

    return 0;

}

void rm_target_words(FILE *input, FILE *output) {

    char line[MAX_LINE_SIZE];

    int i;
    int c;

    while (fgets(line, sizeof(line), input)) {
        i = 0;
        while (line[i]) {

            if (!ispunct(line[i]) && !isspace(line[i])) {
                c = i;

                while (isalpha(line[c]) || isdigit(line[c])) {
                    c++;
                }
                if (!(((c - i) % 2 == 1) && isdigit(line[((c + i) / 2)]))) {
                    while(i < c) {
                        fprintf(output, "%c", line[i]);
                        i++;
                    }
                }
                i = c;
            } else {
                fprintf(output, "%c", line[i]);
                i++;
            }
        }
    }
    printf("Success!\n");
}

