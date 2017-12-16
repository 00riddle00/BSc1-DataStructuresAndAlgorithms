/* Compiler: gcc */
/* CFLAGS=-Wall -xc -g */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getsize(int *size);
void getmemory(int **data, char* ptrName, int size);
void freememory(int **data, char* ptrName);
void filldata(int *data, int size);
void print(int *data, int size);
void die();

typedef struct {
    char* pointerName;
    int pointerMemory;
} PointerStats;


typedef struct {
    PointerStats *memJournal;
    int JournalPointerCount;
    int memUsed;
    int memUsedByJournal;
} MemoryStats;


MemoryStats memoryStats;

int main(int argc, char *argv[]) {

    memoryStats.memJournal = malloc(10*sizeof(int));

    memoryStats.memUsedByJournal = 10;

    memoryStats.JournalPointerCount = 0;

    printf("Mem used total: %d\n", memoryStats.memUsed);

    clock_t begin = clock();

    int size;
    printf("Įveskite masyvo dydį\n> ");
    getsize(&size);

    int *data = NULL;

    getmemory(&data, "data", size * sizeof(int));
    if (data == NULL) die("Atminties problema");

    filldata(data, size);
    if (data == NULL) die("Atminties problema");

    printf("Mem used total: %d\n", memoryStats.memUsed);

    print(data, size);

    freememory(&data, "data");

    clock_t end = clock();

    double time_spent = (double)(end - begin);
    double time_avg = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("time spent %f\n", time_spent);
    printf("time avg %f\n", time_avg);

    printf("Mem used total: %d\n", memoryStats.memUsed);
    free(memoryStats.memJournal);

    return 0;

}


void getsize(int *size) {
    scanf("%d", size);
}


void getmemory(int **data, char* ptrName, int memory_size) {

    int exists = 0;

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memJournal[i].pointerMemory += memory_size;
            exists = 1;
            break;
        }
    }

    if (!exists) {
        memoryStats.memJournal[memoryStats.JournalPointerCount++].pointerName = ptrName;
        memoryStats.memJournal[memoryStats.JournalPointerCount].pointerMemory = memory_size;
    }

    memoryStats.memUsed += memory_size;

    *data = malloc(memory_size);
}


void freememory(int **data, char* ptrName) {

    for (int i = 0; i < memoryStats.JournalPointerCount; i++) {
        if (memoryStats.memJournal[i].pointerName == ptrName) {
            memoryStats.memUsed -= memoryStats.memJournal[i].pointerMemory;
            memoryStats.memJournal[i].pointerMemory = 0;
            break;
        }
    }

    free(*data);
}



void filldata(int *data, int size) {
    srand(time(NULL));
    int i;

    for (i = 0; i < size; i++) {
        data[i] = rand();
    }
}


void print(int *data, int size) {
    int i;
    printf("Jūsų sugeneruoti skaičiai:\n");
    for (i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }
}

void die(char *message) {
    printf("%s\n", message);
    exit(1);
}
