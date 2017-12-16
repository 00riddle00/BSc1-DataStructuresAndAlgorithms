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
        return 1;
    }

    rm_target_words(input, output);

    fclose(input);
    fclose(output);

    return 0;

}

void rm_target_words(FILE *input, FILE *output) {

    char line[MAX_LINE_SIZE];
    char *word;

    // word count in a line
    int count;
    // current character index in the word
    int c;
    // separator symbols
    char *symbols = ".,;:?!/()=+-<>*%$#^&_-|[]{}\"\'";
    char symbol;

    while (fgets(line, sizeof(line), input)) {
        count = 0;

        word = strtok(line, " \n");
        while (word != NULL) {
            c = 0;
            symbol = 0;
            while (word[c]) {
                // check if there is a separator after a word
                if (strchr(symbols, word[c])) {
                    symbol = word[c];
                    word[c] = 0;
                    break;
                }
                c++;
            }

            // check if char count in word is odd and the
            // middle char is a numeral
            if ((c % 2 == 1) && isdigit(word[c / 2])) {
                if (symbol) {
                    fprintf(output, "%c", symbol);
                }
            } else {
                // print whitespace before word if it
                // is not the beginning of the line
                if (count) {
                    fprintf(output, " %s", word);
                } else {
                    fprintf(output, "%s", word);
                }
                if (symbol) {
                    fprintf(output, "%c", symbol);
                }
            }

            // get next token (word)
            word = strtok(NULL, " ");
            count++;
        }
    }
    printf("Success!\n");
};
