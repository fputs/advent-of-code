#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <bsd/stdlib.h>
#endif

#include "lfinput.h"
#include "lfmath.h"

#define GRID_SZ 1000

typedef struct {
    int mode; /* 0 = on, 1 = off, 2 = toggle */
    int x0;
    int y0;
    int x1;
    int y1;
} s1503;

static void get_coords(char *s, int *x, int *y) {
    char buf[8];
    char *c = s;
    int i = 0;
    const char *errstr = NULL;

    while (*c != ',') {
        buf[i++] = *c;
        ++c;
    }
    buf[i] = '\0';
    *x = (int)strtonum(buf, 0, 999, &errstr);
    if (NULL != errstr) {
        exit(1);
    }

    memset(buf, 0, sizeof(char) * 8);
    i = 0;
    ++c;
    while (*c != '\0') {
        buf[i++] = *c;
        ++c;
    }
    buf[i] = '\0';
    *y = (int)strtonum(buf, 0, 999, &errstr);
    if (NULL != errstr) {
        exit(1);
    }
}

static int run(s1503 *ins, size_t sz, int p1) {
    int grid[GRID_SZ][GRID_SZ];
    memset(grid, 0, sizeof(int) * GRID_SZ * GRID_SZ);

    for (size_t i = 0; i < sz; ++i) {
        for (int x = ins[i].x0; x <= ins[i].x1; ++x) {
            for (int y = ins[i].y0; y <= ins[i].y1; ++y) {
                switch (ins[i].mode) {
                case 0: /* on */
                    if (p1) { grid[x][y] = 1; }
                    else {grid[x][y] += 1; }
                    break;

                case 1: /* off */
                    if (p1) { grid[x][y] = 0; }
                    else {grid[x][y] = max_int(0, grid[x][y] - 1); }
                    break;

                case 2: /* toggle */
                    if (p1) { grid[x][y] = grid[x][y] == 1 ? 0 : 1; }
                    else {grid[x][y] += 2; }
                    break;
                }
            }
        }
    }

    int c = 0;
    for (int x = 0; x < GRID_SZ; ++x) {
        for (int y = 0; y < GRID_SZ; ++y) {
            c += grid[x][y];
        }
    }
    return c;
}

void advent2015day06(void) {
    size_t sz = 0;
    char **input = get_lines("input/06", &sz);
    s1503 ins[sz];
    for (size_t i = 0; i < sz; ++i) {
        char *s = malloc(sizeof(char) * 64);
        strncpy(s, input[i], 64);
        size_t sp_sz = 0;
        char **sp = split(s, &sp_sz, " ");

        if (sp_sz == 4) {
            ins[i].mode = 2;
            get_coords(sp[1], &ins[i].x0, &ins[i].y0);
            get_coords(sp[3], &ins[i].x1, &ins[i].y1);
        } else {
            if (strcmp(sp[1], "on") == 0) {
                ins[i].mode = 0;
            } else {
                ins[i].mode = 1;
            }
            get_coords(sp[2], &ins[i].x0, &ins[i].y0);
            get_coords(sp[4], &ins[i].x1, &ins[i].y1);
        }

        del_split(sp);
    }
    del_lines(input);

    printf("%d\n", run(ins, sz, 1));
    printf("%d\n", run(ins, sz, 0));
}
