#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mod.h"

int main(int argc, char *argv[]) {

    struct Stack s = create_stack();
    assert(&s);

    // iterative variable
    int i;

    int numbers[3] = {15, 4, 18};

    // push test
    for (i = 0; i < 3; i++) {
        push(&s, &numbers[i], sizeof(int));
    };

    assert(get_count(&s) == 3);

    printf("numbers: ");
    for (i = 0; i <= s.max; i++) {
        printf("%d ", *(int *) (s.data[i]));
    }
    printf("\n");

    // pop test
    void *last_elem = pop(&s);
    assert(last_elem);

    assert(get_count(&s) == 2);

    // get nth elem test
    void *nth_elem = get_nth_element(&s, 1);
    assert(nth_elem);

    assert(get_count(&s) == 2);

    for (i = 0; i <= (s.max);) {
        free(s.data[i++]);
    }

    free(s.data);
    free(last_elem);

    return 0;
}
