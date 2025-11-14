#include <stdio.h>
#include <stdlib.h>

#include "lfset.h"
#include "lfinput.h"
#include "lfutility.h"

static int part_two(char *input) {
    int sx = 0, sy = 0, rx = 0, ry = 0, is_santa = 1;
    int *x, *y;
    char *c = input;

    Set *houses = malloc(sizeof(Set));
    set_init(houses, Point_cmp_v, free);

    while (*c != '\0') {
        if (is_santa) {
            x = &sx;
            y = &sy;
        } else {
            x = &rx;
            y = &ry;
        }
        is_santa = is_santa == 1 ? 0 : 1;

        switch (*c) {
        case '^':
            ++(*y);
            break;
        case 'v':
            --(*y);
            break;
        case '>':
            ++(*x);
            break;
        case '<':
            --(*x);
            break;
        }
        set_insert(houses, Point_new_p(*x, *y));
        ++c;
    }

    int sz = houses->size;
    set_destroy(houses);

    return sz;
}

static int part_one(char *input) {
    int x = 0, y = 0;
    char *c = input;

    Set *houses = malloc(sizeof(Set));
    set_init(houses, Point_cmp_v, free);

    while (*c != '\0') {
        switch (*c) {
        case '^':
            ++y;
            break;
        case 'v':
            --y;
            break;
        case '>':
            ++x;
            break;
        case '<':
            --x;
            break;
        }
        set_insert(houses, Point_new_p(x, y));
        ++c;
    }

    int sz = houses->size;
    set_destroy(houses);

    return sz;
}

void advent2015day03(void) {
    char *input = get_input("input/03");

    printf("%d\n", part_one(input));
    printf("%d\n", part_two(input));

    free(input);
}
