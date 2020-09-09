
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

struct _PointerStats {
    char* pointerName;
    int pointerMemory;
};

struct _MemoryStats {
    struct _PointerStats* memJournal;
    int JournalPointerCount;
    int memUsed;
    int memUsedByJournal;
};

struct _MemoryStats memoryStats;

char* get_word(char* message, char* output)
{

    while (1) {
        printf("%s", message);
        if (scanf("%s", output) == 1 && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a string, or too many arguments\n");
        }
    }

    return output;
}

char* get_text(char* message, char* output)
{

    while (1) {
        printf("%s", message);

        if (scanf("%[^\n]%*c", output) == 1) {
            break;
        } else {
            while (getchar() != EOF && getchar() != '\n')
                ;
            printf("Please make sure that your text is in normal format\n");
        }
    }
    return output;
}

int get_num(char* message)
{
    int num;

    while (1) {
        printf("%s", message);
        if (scanf("%d", &num) == 1 && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a number\n");
        }
    }

    return num;
}

int get_pos_num(char* message, int zero_allowed)
{
    int num;
    int margin;

    if (zero_allowed) {
        margin = 0;
    } else {
        margin = 1;
    }

    while (1) {
        printf("%s", message);
        if (scanf("%d", &num) == 1 && getchar() == '\n') {
            if (num >= margin) {
                break;
            } else {
                printf("Error: number is not positive");
                if (zero_allowed) {
                    printf(" or zero");
                }
                printf("\n");
            }
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a number\n");
        }
    }

    return num;
}

int get_num_interval(char* message, char* err_msg, int min, int max)
{
    int num;

    while (1) {
        printf("%s", message);
        if (scanf("%d", &num) == 1 && num >= min && num <= max
            && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("%s\n", err_msg);
        }
    }

    return num;
}

char** get_tokens(
    char* message, int max_tokens, int line_length, char** tokens)
{

    char* pch;
    int count;

    char line[line_length];

    while (1) {
        printf("%s", message);

        fgets(line, sizeof(line), stdin);

        count = 0;

        pch = strtok(line, " \n");
        while (pch != NULL) {

            if (count < max_tokens) {
                // malloc() is used in strdup;
                tokens[count] = pch ? strdup(pch) : pch;
                if (!pch)
                    die((char*)"Memory error");
            }

            pch = strtok(NULL, " \n");
            count++;
        }
        // Validate argument count

        if (count == 0) {
            printf("The input is empty.\n");
            continue;
        }

        if (count > max_tokens) {
            printf("Too many arguments\n");
            char** it;
            for (it = tokens; it && *it; ++it) {
                free(*it);
            }
            continue;
        }

        break;
    }

    return tokens;
}

int choice(const char* message)
{

    while (1) {
        printf("%s", message);
        printf(" [Y/n] ");
        char decision;

        if (scanf("%c", &decision) == 1 && getchar() == '\n') {

            switch (decision) {
            case 'y':
            case 'Y':
                return 1;
            case 'n':
            case 'N':
                return 0;
            default:
                printf("Invalid action, only: Y=yes, N=no\n");
            }

        } else {
            while (getchar() != '\n')
                ;
            printf("Invalid action, only: Y=yes, N=no\n");
        }
    }
}

void fill_array(int* data, int size, int max)
{
    for (int i = 0; i < size; i++) {
        data[i] = rand() % max + 1;
    }
}

void print_array(int* data, int size, char* message)
{
    printf("------------------------\n");
    printf("%s\n", message);
    for (int i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }
    printf("------------------------\n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_three(int* a, int* b, int* c)
{
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
}

int is_sorted(int* data, int size)
{

    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            break;
        if (data[i] > data[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void getmemory(int** data, char* ptrName, int memory_size)
{

    int exists = 0;

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memJournal[i].pointerMemory += memory_size;
            exists = 1;
            break;
        }
    }

    if (!exists) {
        memoryStats.memJournal[memoryStats.JournalPointerCount++].pointerName
            = ptrName;
        memoryStats.memJournal[memoryStats.JournalPointerCount].pointerMemory
            = memory_size;
    }

    memoryStats.memUsed += memory_size;

    *data = (int*)malloc(memory_size);
}

void freememory(int** data, char* ptrName)
{

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memUsed -= memoryStats.memJournal[i].pointerMemory;
            memoryStats.memJournal[i].pointerMemory = 0;
            break;
        }
    }

    free(*data);
}

void die(char* message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}
