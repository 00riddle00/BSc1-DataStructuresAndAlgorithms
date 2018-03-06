#ifndef HELPERS_H
#define HELPERS_H


#include <stdio.h>
#include <stdlib.h>

// input processing functions
char* get_word(char* message, char* output);
char* get_text(char* message, char* output);
int get_num(char* message);
int get_pos_num(char* message, int zero_allowed);
int get_num_interval(char* message, char* err_msg, int min, int max);
char** get_tokens(
    char* message, int max_tokens, int line_length, char** tokens);
int choice(const char* message);

// function working with arrays
void fill_array(int* data, int size, int max);
void print_array(int* data, int size, char* message);

// sorting helper functions
void swap(int* a, int* b);
void swap_three(int* a, int* b, int* c);
int is_sorted(int* data, int size);

// memory functions
void getmemory(int** data, char* ptrName, int memory_size);
void freememory(int** data, char* ptrName);
void die(char* message);

#endif
