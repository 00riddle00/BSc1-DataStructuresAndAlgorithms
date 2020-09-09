/*=============================================================================
 |
 |  Assignment:  Exercise 9
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  May 4th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Implement finding Levenstein distance between two strings,
 |                and a simple spellchecker.
 |                
 |	    Input:    Command line input by user
 |
 |	    Output:   Prompt messages, validation errors and final results
 |                are displayed one per line to the standard output.
 |
 | Version
 | updates:     Currently this is the intial version
 |
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dbg.h"
#include "helpers.h"

static char dictionary[10][10] = {
    "welcome",
    "this",
    "is",
    "just",
    "a",
    "testing",
    "program"
};

int minimum(int a, int b, int c) {
    int min;

    if (a<b && a<c) {
        min = a;
    } else if (b<c && b<a){
        min = b;
    } else {
        min = c;
    }
    return min;
}


// len_s and len_t are the number of characters in string s and t respectively
int LevenshteinDistance(const char *s, int len_s, const char *t, int len_t)
{
  int cost;

  /* base case: empty strings */
  if (len_s == 0) return len_t;
  if (len_t == 0) return len_s;

  /* test if last characters of the strings match */
  if (s[len_s-1] == t[len_t-1])
      cost = 0;
  else
      cost = 1;

  /* return minimum of delete char from s, delete char from t, and delete char from both */
  return minimum(LevenshteinDistance(s, len_s - 1, t, len_t    ) + 1,
                 LevenshteinDistance(s, len_s    , t, len_t - 1) + 1,
                 LevenshteinDistance(s, len_s - 1, t, len_t - 1) + cost);
}

char* check_match(char str[]) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(dictionary[i], str) == 0) {
            return str;
        }
    }

    for (int i = 0; i < 7; i++) {
        if (strlen(dictionary[i]) - strlen(str) <= 1) {
            int res = LevenshteinDistance(dictionary[i], strlen(dictionary[i]), str, strlen(str));
            if (res == 0) {
                return str;
            } else if (res <= 2) {
                char prompt[50];
                sprintf(prompt, "Did you mean \"%s\" instead of \"%s\"?", dictionary[i], str);
                if (choice(prompt)) {
                    strcpy(str, dictionary[i]);
                    return str;
                } else {
                    return str;
                }
            }
        }
    }


    printf("invalid word: \"%s\"\n", str);
    return str;

}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

void check_spelling(char str[]) {
  char new_str[strlen(str)];
  printf("Your string is:\n\"%s\"\n", str);
  printf("------Spellcheck in progress...\n");
  waitFor(3);
  char *pch;

  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    pch = check_match(pch);

    if (strlen(new_str) == 0) {
        sprintf(new_str, "%s%s", new_str, pch);
    } else {
        sprintf(new_str, "%s %s", new_str, pch);
    }
    pch = strtok (NULL, " ,.-");
  }
  printf("------Spellcheck completed.\n");
  printf("Your new string is:\n\"%s\"\n", new_str);
  sprintf(str, new_str);
}


int main() {
    char text[] = "aweclomebc this is kusa a texting pogram.";
    check_spelling(text);

    return 0;
}



