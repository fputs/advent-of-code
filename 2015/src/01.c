#include <stdio.h>
#include <stdlib.h>

#include "lfinput.h"

void advent2015day01(void) {
    char *input = get_input("input/01");
    char *c = input;
    int f = 0, b = 0, s = 1;

    while (*c != '\0') {
        if (*c == '(') {
            ++f;
        } else {
            --f;
        }

        if (f == -1 && b == 0) {
            b = s;
        }

        ++c;
        ++s;
    }

    printf("%d\n%d\n", f, b);
    free(input);
}
