#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lfinput.h"
#include "lfmath.h"

void advent2015day02(void) {
    size_t sz = 0;
    char **lines = get_lines("input/02", &sz);
    int paper = 0, ribbon = 0;

    for (size_t i = 0; i < sz; i++) {
        char *t = strtok(lines[i], "x");
        int w = atoi(t);
        t = strtok(NULL, "x");
        int l = atoi(t);
        t = strtok(NULL, "x");
        int h = atoi(t);

        paper += 2 * l * w + 2 * w * h + 2 * h * l + min_int(w * l, min_int(l * h, h * w));
        ribbon += l * w * h + min_int(w + w + h + h, min_int(h + h + l + l, l + l + w + w));
    }

    printf("%d\n%d\n", paper, ribbon);
    del_lines(lines);
}
