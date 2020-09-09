/*=============================================================================
 |
 |  Assignment:  Exercise 7
 |
 |       Author:  Tomas Giedraitis
 |  Study group:  VU MIF INFO, 1st group
 |     Contacts:  tomasgiedraitis@gmail.com
 |        Class:  Algorithms and Data Structures
 |         Date:  March 18th, 2017
 |
 |     Language:  GNU C (using gcc on Lenovo Y50-70, OS: Arch Linux x86_64)
 |     Version:   0.0
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  Sorting algortihm testing program using pseudo randomly 
 |                generated number array. User can specify array length, 
 |                its min and max elements, the least number of repeating 
 |                values. User can also choose how many arrays to be tested.
 |
 |  Exercise 6:   Also implement own sorting algorithm with O(n^2) worst case
 |                complexity, which would be better than other O(n^2) 
 |                algorithms though (Shaker sort, Bubble sort, Insertion,
 |                Selection sorts, Comb sort, Shell sort. Could be optimized
 |                Shell sort, or any other implementation.
 |
 |  Exercise 7:   Also implement quicksort without median, with median, and 
 |                with random median, as well as merge sort, heap sort and
 |                tree sort (optional) algorithms, and test their speed, 
 |                comparisons and assignments.
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

/* Explanations
 *
 a)  naivus rikiavimo algoritmas, kuris perbėga visą n dydžio masyvą n kartų,
 lygindamas greta esan čius elementus tarpusavyje ir keisdamas juos
 vietomis, jei tvarka netinkama
 b)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 remiasi faktu, kad į - asis masyvo perbėgimas į - ąjį pagal dydį elementą
 „nutempia“ į galutinę jo poziciją, ir naujo perbėgimo metu savo vietoje
 esančio elemento nebetikrina
 c)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 papildomai stebi, ar duomenys tapo išrikiuoti, sekdamas ar perbėgimo
 metu buvo atliktas nors vienas sukeitimas, ir jei ne – vadinasi tęsti
 nebereikia
 d)  lyginimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 įsidėmi paskutinio sukeitimo vietą, ir remdamasis faktu, kad visi
 tolesni elementai jau yra savo vietoje, rikiuoja tik galimai nesurikiuotą
 masyvo dalį
 e)  priskyrimo operacijų kiekį optimizuojantis rikiavimo algoritmas, kuris
 gali keisti vietomis daugiau negu du elementus, t.y. vieną iš keistinų
 elementų jis pastumia iškart, o kitą įrašo į masyvą tiktai tuo atveju,
 jei jo tuojau pat nebereikės st umti iš tos pozicijos vėl
 f)  „dvipusio“ rikiavimo algoritmas, kuris vieno perbėgimo metu didina
 lyginamų elementų indeksus, o kito perbėgimo metu juos mažina
 (žr. bidirectional bubble sort, shaker sort)
 x) toliau - mišrūs burbuliuko rikiavimo metodai, sujungiant a)-f) savybes
 vienokia ar kitokia tvarka
 g) greitojo rikiavimo metodas (angl. quicksort)
 h) Įterpimo metodas (angl. insertion sort)
 i) Išrinkimo metodas (angl. selection sort)
 j) Sąlajos metodas (angl. merge sort)
 */

// TODO add these sorts ((+) means already added)

/*(+) Bubble_sort*/
/*(+++++) Bubble_sort optimizations (14)*/
/*(+++) Quicksort (3) (pivot first, median/random median)*/
/*(+) Insertion sort*/
/*(+) Selection sort*/
/*(+) Merge sort*/
/*(+) Heap sort*/

/*(+)Gnome sort*/
/*(+)Comb sort*/
/*(+)Shell sort*/

/* Implement hybrid algorithm O(n^2), 
/ * but better than Shaker/Gnome/Comb/Shell sort*/
/* can be optimized Shell sort*/

/*(-)Tree sort*/
/*(-)Smooth sort*/
/*(-)Intro sort*/
/*(-)Tim sort*/
/*(-)Bucket Sort*/
/*(+)Radix Sort */
/*(-)Counting Sort*/
/*(-)Cubesort*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dbg.h"

#include "lib_riddle.h"
#include "lib_sorting.h"

#define MAX_ITER 10000
#define MAX_ALGO 100


typedef struct {
    char* pointerName;
    int pointerMemory;
} PointerStats;

typedef struct {
    PointerStats* memJournal;
    int JournalPointerCount;
    int memUsed;
    int memUsedByJournal;
} MemoryStats;


typedef struct {
    int no;
    int is_sorted;
    int comp_count;
    int assign_count;
    double clocks_total;
    double time_spent;
} Iteration;

typedef struct {
    char* type;
    char* complexity;
    int iter_count;
    int rank;
    int avg_comp;
    int avg_assign;
    double avg_clocks;
    double avg_time;
    Iteration* iterations[MAX_ITER];
} Algorithm;

typedef struct {
    char* date;
    char* arch;
    char* compiler;
    Algorithm* algorithms[MAX_ALGO];
} Results;

// a typedef creates a fake type, in this
// case for a sort function pointer
typedef int* (*sort_pointer)(int* target, int size);

// function pointer to a quicksort function
typedef int* (*quicksort_pointer)(int* target, int first, int last);
typedef void (*quicksort_pointer_2)(int* target, int first, int last);

// function pointer to a mergesort function
typedef void (*mergesort_pointer)(int* target, int* working_array, int size);


void filldata(int* data, int size, int min, int max, int repeat);
void test_sort( int* data, int size, sort_pointer func, Algorithm* Algo, int no);
void test_quicksort( int* data, int size, quicksort_pointer func, Algorithm* Algo, int no);
void test_mergesort( int* data, int size, mergesort_pointer func, Algorithm* Algo, int no);
void print_algo(Algorithm* Algo);
void calculate_average(Algorithm* Algo);
Algorithm** rank_algorithms(Algorithm** target, int first, int last);

/* Newly added algoritms (Exercise 6) */

/* Gnome Sort */
int* GnomeSort(int* target, int size);
/* Comb sort*/
int newgap(int gap);
int* combsort(int* a, int aSize);
/* Shell sort */
int* shellSort(int* intArray, int size);
int largest(int* intArray, int size);
int* radixSort(int* intArray, int size);

MemoryStats memoryStats;

int array_count;
int algo_count;


int main(int argc, char* argv[])
{
    srand(time(NULL));

    Results* Res = malloc(sizeof(Results));

    Res->date = "2017-12-16";
    Res->arch = "Arch Linux x86_64";
    Res->compiler = "gcc";
    
    algo_count = 25;

    // creating algorithm structures
    Algorithm* Algo1 = malloc(sizeof(Algorithm));
    Algo1->type = "bubble_sort_a";
    Algo1->complexity = "O (n^2)";

    Algorithm* Algo2 = malloc(sizeof(Algorithm));
    Algo2->type = "bubble_sort_b";
    Algo2->complexity = "O (n^2)";

    Algorithm* Algo3 = malloc(sizeof(Algorithm));
    Algo3->type = "bubble_sort_c";
    Algo3->complexity = "O (n^2)";

    Algorithm* Algo4 = malloc(sizeof(Algorithm));
    Algo4->type = "bubble_sort_d";
    Algo4->complexity = "O (n^2)";

    Algorithm* Algo5 = malloc(sizeof(Algorithm));
    Algo5->type = "bubble_sort_e";
    Algo5->complexity = "O (n^2)";

    Algorithm* Algo6 = malloc(sizeof(Algorithm));
    Algo6->type = "bubble_sort_f (Shaker sort)";
    Algo6->complexity = "O (n^2)";

    Algorithm* Algo7 = malloc(sizeof(Algorithm));
    Algo7->type = "bubble_sort_b_and_c";
    Algo7->complexity = "O (n^2)";

    Algorithm* Algo8 = malloc(sizeof(Algorithm));
    Algo8->type = "bubble_sort_b_and_e";
    Algo8->complexity = "O (n^2)";

    Algorithm* Algo9 = malloc(sizeof(Algorithm));
    Algo9->type = "bubble_sort_b_and_f";
    Algo9->complexity = "O (n^2)";

    Algorithm* Algo10 = malloc(sizeof(Algorithm));
    Algo10->type = "bubble_sort_c_and_e";
    Algo10->complexity = "O (n^2)";

    Algorithm* Algo11 = malloc(sizeof(Algorithm));
    Algo11->type = "bubble_sort_c_and_f";
    Algo11->complexity = "O (n^2)";

    Algorithm* Algo12 = malloc(sizeof(Algorithm));
    Algo12->type = "bubble_sort_e_and_f";
    Algo12->complexity = "O (n^2)";

    Algorithm* Algo13 = malloc(sizeof(Algorithm));
    Algo13->type = "bubble_sort_b_and_e_and_f";
    Algo13->complexity = "O (n^2)";

    Algorithm* Algo14 = malloc(sizeof(Algorithm));
    Algo14->type = "bubble_sort_b_and_c_and_e_and_f";
    Algo14->complexity = "O (n^2)";

    Algorithm* Algo15 = malloc(sizeof(Algorithm));
    Algo15->type = "quicksort_pivot_first";
    Algo15->complexity = "O (n logn n)";

    Algorithm* Algo16 = malloc(sizeof(Algorithm));
    Algo16->type = "quicksort_median";
    Algo16->complexity = "O (n logn n)";

    Algorithm* Algo17 = malloc(sizeof(Algorithm));
    Algo17->type = "quicksort_random_and_median";
    Algo17->complexity = "O (n logn n)";

    Algorithm* Algo18 = malloc(sizeof(Algorithm));
    Algo18->type = "insertion_sort";
    Algo18->complexity = "O (2n)";

    Algorithm* Algo19 = malloc(sizeof(Algorithm));
    Algo19->type = "selection_sort";
    Algo19->complexity = "O (2n)";

    Algorithm* Algo20 = malloc(sizeof(Algorithm));
    Algo20->type = "top down merge sort";
    Algo20->complexity = "O (n log n)";

    Algorithm* Algo21 = malloc(sizeof(Algorithm));
    Algo21->type = "heap sort";
    Algo21->complexity = "O (n log n)";

    Algorithm* Algo22 = malloc(sizeof(Algorithm));
    Algo22->type = "gnome sort";
    Algo22->complexity = "O(n^2)";

    Algorithm* Algo23 = malloc(sizeof(Algorithm));
    Algo23->type = "comb sort";
    Algo23->complexity = "O(n^2)";

    Algorithm* Algo24 = malloc(sizeof(Algorithm));
    Algo24->type = "shell sort";
    Algo24->complexity = "O(n^2) (worst known gap sequence), O(n*log^2(n)) (best known gap sequence)";

    Algorithm* Algo25 = malloc(sizeof(Algorithm));
    Algo25->type = "radix sort";
    Algo24->complexity = "O(wn)";

    Res->algorithms[0] = Algo1;
    Res->algorithms[1] = Algo2;
    Res->algorithms[2] = Algo3;
    Res->algorithms[3] = Algo4;
    Res->algorithms[4] = Algo5;
    Res->algorithms[5] = Algo6;
    Res->algorithms[6] = Algo7;
    Res->algorithms[7] = Algo8;
    Res->algorithms[8] = Algo9;
    Res->algorithms[9] = Algo10;
    Res->algorithms[10] = Algo11;
    Res->algorithms[11] = Algo12;
    Res->algorithms[12] = Algo13;
    Res->algorithms[13] = Algo14;
    Res->algorithms[14] = Algo15;
    Res->algorithms[15] = Algo16;
    Res->algorithms[16] = Algo17;
    Res->algorithms[17] = Algo18;
    Res->algorithms[18] = Algo19;
    Res->algorithms[19] = Algo20;
    Res->algorithms[20] = Algo21;
    Res->algorithms[21] = Algo22;
    Res->algorithms[22] = Algo23;
    Res->algorithms[23] = Algo24;
    Res->algorithms[24] = Algo25;

    memoryStats.memJournal = malloc(10 * sizeof(int));

    memoryStats.memUsedByJournal = 10;

    memoryStats.JournalPointerCount = 0;

    printf("Mem used total: %d\n", memoryStats.memUsed);

    int size;
    int min;
    int max;
    int repeat;

    array_count = get_pos_num("How many arrays would you like to test? > ", 0);
    size = get_pos_num("What is the size of each array? > ", 0);
    min = get_pos_num("What is the minimum number in each array? > ", 0);
    max = get_pos_num("What is the maximum number in each array? > ", 0);

    while (1) {
        printf("How many repeating values there will be AT LEAST? > ");
        if (scanf("%d", &repeat) == 1 && repeat >= 0
            && repeat <= (max - min + 1) && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Please enter a positive integer or zero, which is not "
                   "greater than the "
                   "size of the array\n");
        }
    }

    for (int i = 0; i < array_count; i++) {
        int* data = malloc(size * sizeof(int));

        filldata(data, size, min, max, repeat);
        if (data == NULL)
            die("Atminties problema");

        //---------------------------USING FUNCTION POINTERS-----------------//
        test_sort(data, size, &bubble_sort_a, Algo1, i + 1);
        test_sort(data, size, &bubble_sort_b, Algo2, i + 1);
        test_sort(data, size, &bubble_sort_c, Algo3, i + 1);
        test_sort(data, size, &bubble_sort_d, Algo4, i + 1);
        test_sort(data, size, &bubble_sort_e, Algo5, i + 1);
        test_sort(data, size, &bubble_sort_f, Algo6, i + 1);
        test_sort(data, size, &bubble_sort_b_and_c, Algo7, i + 1);
        test_sort(data, size, &bubble_sort_b_and_e, Algo8, i + 1);
        test_sort(data, size, &bubble_sort_b_and_f, Algo9, i + 1);
        test_sort(data, size, &bubble_sort_c_and_e, Algo10, i + 1);
        test_sort(data, size, &bubble_sort_c_and_f, Algo11, i + 1);
        test_sort(data, size, &bubble_sort_e_and_f, Algo12, i + 1);
        test_sort(data, size, &bubble_sort_b_and_e_and_f, Algo13, i + 1);
        test_sort(data, size, &bubble_sort_b_and_c_and_e_and_f, Algo14, i + 1);
        test_quicksort(data, size, &quicksort, Algo15, i + 1);
        test_quicksort(data, size, &QuickSortMedian, Algo16, i + 1);
        test_quicksort(data, size, &QuickSortRandomAndMedian, Algo17, i + 1);
        test_sort(data, size, &insertion_sort, Algo18, i + 1);
        test_sort(data, size, &selection_sort, Algo19, i + 1);
        test_mergesort(data, size, &TopDownMergeSort, Algo20, i + 1);
        test_sort(data, size, &heapSort, Algo21, i + 1);
        test_sort(data, size, &GnomeSort, Algo22, i + 1);
        test_sort(data, size, &combsort, Algo23, i + 1);
        test_sort(data, size, &shellSort, Algo24, i + 1);
        test_sort(data, size, &radixSort, Algo25, i + 1);

        free(data);
        debug("%d iter", i);
    }

    calculate_average(Algo1);
    calculate_average(Algo2);
    calculate_average(Algo3);
    calculate_average(Algo4);
    calculate_average(Algo5);
    calculate_average(Algo6);
    calculate_average(Algo7);
    calculate_average(Algo8);
    calculate_average(Algo9);
    calculate_average(Algo10);
    calculate_average(Algo11);
    calculate_average(Algo12);
    calculate_average(Algo13);
    calculate_average(Algo14);
    calculate_average(Algo15);
    calculate_average(Algo16);
    calculate_average(Algo17);
    calculate_average(Algo18);
    calculate_average(Algo19);
    calculate_average(Algo20);
    calculate_average(Algo21);
    calculate_average(Algo22);
    calculate_average(Algo23);
    calculate_average(Algo24);
    calculate_average(Algo25);

    for (int i = 0; i < algo_count; i++) {
        print_algo(Res->algorithms[i]);
    }

    Algorithm** target = malloc(algo_count * sizeof(Algorithm));

    target[0] = Algo1;
    target[1] = Algo2;
    target[2] = Algo3;
    target[3] = Algo4;
    target[4] = Algo5;
    target[5] = Algo6;
    target[6] = Algo7;
    target[7] = Algo8;
    target[8] = Algo9;
    target[9] = Algo10;
    target[10] = Algo11;
    target[11] = Algo12;
    target[12] = Algo13;
    target[13] = Algo14;
    target[14] = Algo15;
    target[15] = Algo16;
    target[16] = Algo17;
    target[17] = Algo18;
    target[18] = Algo19;
    target[19] = Algo20;
    target[20] = Algo21;
    target[21] = Algo22;
    target[22] = Algo23;
    target[23] = Algo24;
    target[24] = Algo25;

    target = rank_algorithms(target, 0, algo_count-1);

    printf("Fastest algorithms (ranking):\n");
    printf("=============================\n");

    for (int i = 0; i < algo_count; i++) {
        printf("%d. ", i + 1);
        printf("%s\n", target[i]->type);
        printf("Average time: %f\n", target[i]->avg_time);
        printf("---------------------------------\n");
    }

    printf("================================\n");
    printf("Date: %s\n", Res->date);
    printf("Architecture: %s\n", Res->arch);
    printf("Compiler: %s\n", Res->compiler);
    printf("================================\n");

    printf("Mem used total: %d\n", memoryStats.memUsed);


    free(Res);


    for (int i = 0; i < array_count; i++) {
        free(Algo1->iterations[i]);
    }
    free(Algo1);

    for (int i = 0; i < array_count; i++) {
        free(Algo2->iterations[i]);
    }
    free(Algo2);

    for (int i = 0; i < array_count; i++) {
        free(Algo3->iterations[i]);
    }
    free(Algo3);

    for (int i = 0; i < array_count; i++) {
        free(Algo4->iterations[i]);
    }
    free(Algo4);

    for (int i = 0; i < array_count; i++) {
        free(Algo5->iterations[i]);
    }
    free(Algo5);

    for (int i = 0; i < array_count; i++) {
        free(Algo6->iterations[i]);
    }
    free(Algo6);

    for (int i = 0; i < array_count; i++) {
        free(Algo7->iterations[i]);
    }
    free(Algo7);

    for (int i = 0; i < array_count; i++) {
        free(Algo8->iterations[i]);
    }
    free(Algo8);

    for (int i = 0; i < array_count; i++) {
        free(Algo9->iterations[i]);
    }
    free(Algo9);

    for (int i = 0; i < array_count; i++) {
        free(Algo10->iterations[i]);
    }
    free(Algo10);

    for (int i = 0; i < array_count; i++) {
        free(Algo11->iterations[i]);
    }
    free(Algo11);
    
    for (int i = 0; i < array_count; i++) {
        free(Algo12->iterations[i]);
    }
    free(Algo12);

    for (int i = 0; i < array_count; i++) {
        free(Algo13->iterations[i]);
    }
    free(Algo13);
    
    for (int i = 0; i < array_count; i++) {
        free(Algo14->iterations[i]);
    }
    free(Algo14);

    for (int i = 0; i < array_count; i++) {
        free(Algo15->iterations[i]);
    }
    free(Algo15);
    
    for (int i = 0; i < array_count; i++) {
        free(Algo16->iterations[i]);
    }
    free(Algo16);

    for (int i = 0; i < array_count; i++) {
        free(Algo17->iterations[i]);
    }
    free(Algo17);

    for (int i = 0; i < array_count; i++) {
        free(Algo18->iterations[i]);
    }
    free(Algo18);

    for (int i = 0; i < array_count; i++) {
        free(Algo19->iterations[i]);
    }
    free(Algo19);

    for (int i = 0; i < array_count; i++) {
        free(Algo20->iterations[i]);
    }
    free(Algo20);

    for (int i = 0; i < array_count; i++) {
        free(Algo21->iterations[i]);
    }
    free(Algo21);

    for (int i = 0; i < array_count; i++) {
        free(Algo22->iterations[i]);
    }
    free(Algo22);

    for (int i = 0; i < array_count; i++) {
        free(Algo23->iterations[i]);
    }
    free(Algo23);

    for (int i = 0; i < array_count; i++) {
        free(Algo24->iterations[i]);
    }
    free(Algo24);

    for (int i = 0; i < array_count; i++) {
        free(Algo25->iterations[i]);
    }
    free(Algo25);

    free(target);
    free(memoryStats.memJournal);
}


void filldata(int* data, int size, int min, int max, int repeat)
{
    int i;

    for (i = 0; i < size; i++) {
        data[i] = min + rand() % (max - min + 1);
    }

    if (repeat > 1) {
        int repeat_value = min + rand() % (max - min + 1);

        int indexes[repeat];

        int x;

        // Non-duplicate number generation

        i = 0;
        while (i < repeat) {
            int index = rand() % size;

            for (x = 0; x < i; x++) {
                if (indexes[x] == index) {
                    break;
                }
            }
            if (x == i) {
                indexes[i++] = index;
            }
        }

        for (i = 0; i < repeat; i++) {
            data[indexes[i]] = repeat_value;
        }
    }
}


void test_sort(int* data, int size, sort_pointer func, Algorithm* Algo, int no)
{

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int* target = NULL;
    target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    Iteration* Iter = malloc(sizeof(Iteration));
    if (Iter == NULL) {
        exit(1);
    }
    Iter->no = no;

    if (is_sorted(func(target, size), size)) {
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
        
    };

    Algo->iterations[no - 1] = Iter;

    if (target == NULL) {
        debug("Target is NULL");
    }

    free(target);
}


void test_quicksort(int* data, int size, quicksort_pointer func, Algorithm* Algo, int no) {

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int* target = NULL;
    target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    Iteration* Iter = malloc(sizeof(Iteration));
    Iter->no = no;

    if (is_sorted(func(target, 0, size), size)) {
        debug("ISSORTED");
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
    };

    Algo->iterations[no - 1] = Iter;

    free(target);
}

void test_mergesort(
    int* data, int size, mergesort_pointer func, Algorithm* Algo, int no)
{

    count_ncomp = 0;
    count_assign = 0;

    begin = clock();

    int *target = NULL;
    target = malloc(size * sizeof(int));
    if (!target)
        die("Memory error.");

    memcpy(target, data, size * sizeof(int));

    int* working_array = calloc(size, sizeof(int));
    if (!working_array)
        die("Memory error.");

    func(target, working_array, size);

    Iteration* Iter = malloc(sizeof(Iteration));
    Iter->no = no;

    if (is_sorted(target, size)) {
        end = clock();
        clocks = (double)(end - begin);
        time_spent = clocks / CLOCKS_PER_SEC;

        Iter->is_sorted = 1;
        Iter->comp_count = count_ncomp;
        Iter->assign_count = count_assign;
        Iter->clocks_total = clocks;
        Iter->time_spent = time_spent;
    } else {
        Iter->is_sorted = 0;
    }

    Algo->iterations[no - 1] = Iter;

    free(working_array);
    free(target);
}



void print_algo(Algorithm* Algo)
{

    printf("Algorithm type: %s\n", Algo->type);
    printf("Time complexity: %s\n", Algo->complexity);
    printf("----------------------------------\n");
    for (int i = 0; i < array_count; i++) {
        if (!Algo->iterations[i]->is_sorted) {
            printf("Not sorted");
        } else {
            printf("no: %d\n", Algo->iterations[i]->no);
            printf("is_sorted: True\n");
            printf("comp_count: %d\n", Algo->iterations[i]->comp_count);
            printf("assign count: %d\n", Algo->iterations[i]->assign_count);
            printf("clocks total: %f\n", Algo->iterations[i]->clocks_total);
            printf("time spent: %f\n", Algo->iterations[i]->time_spent);
        }
        printf("----------------------------------\n");
    }
    printf("Iteration count: %d\n", Algo->iter_count);
    printf("Average compare count: %d\n", Algo->avg_comp);
    printf("Average assign count: %d\n", Algo->avg_assign);
    printf("Average clocks: %f\n", Algo->avg_clocks);
    printf("Average time spent: %f\n", Algo->avg_time);

    printf("===================================\n");
}

void calculate_average(Algorithm* Algo)
{
    int sum_comp = 0;
    int sum_assign = 0;
    double sum_clocks = 0;
    double sum_time = 0;
    int sorted_count = array_count;

    for (int i = 0; i < array_count; i++) {

        debug("is sorted %d", Algo->iterations[i]->is_sorted);
        debug("Array count: %d", i);

        if (!Algo->iterations[i]->is_sorted) {
            sorted_count--;
        } else {
            sum_comp += Algo->iterations[i]->comp_count;
            sum_assign += Algo->iterations[i]->assign_count;
            sum_clocks += Algo->iterations[i]->clocks_total;
            sum_time += Algo->iterations[i]->time_spent;
        }
    }
    if (sorted_count > 0) {
        Algo->avg_comp = sum_comp / sorted_count;
        Algo->avg_assign = sum_assign / sorted_count;
        Algo->avg_clocks = (double)(sum_clocks / sorted_count);
        Algo->avg_time = (double)(sum_time / sorted_count);
        Algo->iter_count = sorted_count;
    }
}

Algorithm** rank_algorithms(Algorithm** target, int first, int last)
{

    Algorithm* temp;
    int pivot, j, i;

    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (
                target[i]->avg_time <= target[pivot]->avg_time && i < last) {
                i++;
            }
            while (target[j]->avg_time > target[pivot]->avg_time) {
                j--;
            }
            if (i < j) {
                temp = target[i];
                target[i] = target[j];
                target[j] = temp;
            }
        }

        temp = target[pivot];
        target[pivot] = target[j];
        target[j] = temp;

        rank_algorithms(target, first, j - 1);
        rank_algorithms(target, j + 1, last);
    }
    return target;
}



int* GnomeSort(int* target, int size) {
	for (int i = 1; i < size; ) {
		if (target[i - 1] <= target[i]) {

            count_ncomp++;

			++i;
        } else {
			int tmp = target[i];
			target[i] = target[i - 1];
			target[i - 1] = tmp;

            count_assign += 3;

			--i;
			if (i == 0)
				i = 1;
		}
	}
    return target;
}


/*

 * C Program to Perform Comb Sort on Array of Integers

 */


/*Function to find the new gap between the elements*/

int newgap(int gap) {
    gap = (gap * 10) / 13;

    if (gap == 9 || gap == 10) {
        gap = 11;
    }

    if (gap < 1) {
        gap = 1;
    }

    return gap;
}

/*Function to implement the combsort*/

int* combsort(int* a, int aSize) {

    int gap = aSize;
    int temp, i;

    for (;;) {

        gap = newgap(gap);
        int swapped = 0;

        for (i = 0; i < aSize - gap; i++) {
            int j = i + gap;

            if (a[i] > a[j]) {

                count_ncomp++;

                temp = a[i];
                a[i] = a[j];
                a[j] = temp;

                count_assign += 3;

                swapped  =  1;
            }

        }

        if (gap  ==  1 && !swapped) {
            break;
        }

    }

    return a;
}



int* shellSort(int* intArray, int size) {
   int inner, outer;
   int valueToInsert;
   int interval = 1;
   int elements = size;
   int i = 0;

   while(interval <= elements/3) {
      interval = interval*3 +1;
   }

   while(interval > 0) {
      for(outer = interval; outer < elements; outer++) {
         valueToInsert = intArray[outer];
         inner = outer;

         count_assign++;

         while(inner > interval -1 && intArray[inner - interval] >= valueToInsert) {

            count_ncomp += 2;

            intArray[inner] = intArray[inner - interval];
            inner -=interval;

            count_assign++;
         }

         intArray[inner] = valueToInsert;

         count_assign++;
      }

      interval = (interval -1) /3;
      i++;
   }

   return intArray;
}

int* radixSort(int* intArray, int size) {
    int k, i, j, temp, t, n;
    int min = 0;
 
    int* intArray1 = calloc(size, sizeof(int));
    for (int a = 0; a < size; a++) {
        intArray1[i] = intArray[i];
    }

    for (k = 0; k < 3; k++)
    {    
        for (i = 0; i < size; i++)
        {
            min = intArray[i] % 10;        // To find minimum lsd 
            t = i;
            for (j = i + 1; j < size; j++)    
            {
                if (min > (intArray[j] % 10))
                {
                    min = intArray[j] % 10; 
                    t = j;
                }
            }
            temp = intArray1[t];
            intArray1[t] = intArray1[i];
            intArray1[i] = temp;
            temp = intArray[t];
            intArray[t] = intArray[i];
            intArray[i] = temp;

        }
        for (j = 0; j < size; j++)        // to find MSB 
            intArray[j] = intArray[j] / 10;
    }
    return intArray;
}
