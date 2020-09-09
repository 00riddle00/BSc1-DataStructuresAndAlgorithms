#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "dbg.h"
#include "hash_table.h"
#include "binary_search_tree.h"

int main() {

    Elem table[P];
    init(table);

    insert(table, 1234, 'a');
    insert(table, 5021, 'b');
    insert(table, 7423, 'c');
    insert(table, 2000, 'd');
    insert(table, 9043, 'e');
    insert(table, 6296, 'f');
    insert(table, 6620, 'g');
    insert(table, 2013, 'h');

    print(table);

    int index = find(table, 1234);
    if (index != -1) {
        printf("Found %d: index in a table is %d\n", 1234, index);
    } else {
        printf("Element %d not found\n", 1234);
    }
}
