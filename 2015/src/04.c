#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lfinput.h"
#include "advent_utility.h"

static int is_five(char *test) {
    char *t = test;
    for (int i = 0; i < 5; ++i, ++t) {
        if (*t != '0') {
            return 0;
        }
    }
    return 1;
}

static int is_six(char *test) {
    char *t = test;
    for (int i = 0; i < 6; ++i, ++t) {
        if (*t != '0') {
            return 0;
        }
    }
    return 1;
}

void advent2015day04(void) {
    char *input = get_input("input/04");
    int c = 0, five = 0, six = 0;

    while (!five || !six) {
        int sz = strlen(input) + 8;
        char test[sz];
        snprintf(test, sz, "%s%d", input, c);
        char *md5 = md5_str(test);

        if (!five && is_five(md5)) {
            five = c;
            printf("%d\n", five);
        }
        if (is_six(md5)) {
            six = c;
        }

        free(md5);
        ++c;
    }

    printf("%d\n", six);
    free(input);
}
