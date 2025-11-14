#include <stdio.h>
#include <stdlib.h>

#include "lfinput.h"

typedef struct {
    long cap;
    long dur;
    long flv;
    long tex;
    long cal;
} Ingredient;

static long long_max(long a, long b) {
    return a > b ? a : b;
}

void advent2015day15(void) {
    size_t input_sz = 0;
    char **input = get_lines("input/15", &input_sz);

    Ingredient ing[input_sz]; for (size_t i = 0; i < input_sz; ++i) {
        char n[16];
        sscanf(input[i], "%s capacity %ld, durability %ld, flavor %ld, texture %ld, calories %ld",
            n, 
            &ing[i].cap,
            &ing[i].dur,
            &ing[i].flv,
            &ing[i].tex, 
            &ing[i].cal
        );
    }

    long max = 0, max_healthy = 0;
    for (long p0 = 0; p0 < 100; ++p0) {
        for (long p1 = 0; p1 < 100; ++p1) {
            for (long p2 = 0; p2 < 100; ++p2) {
                for (long p3 = 0; p3 < 100; ++p3) {
                    if (p0 + p1 + p2 + p3 != 100) {
                        continue;
                    }
                    long cap = long_max(ing[0].cap * p0 + ing[1].cap * p1 + ing[2].cap * p2 + ing[3].cap * p3, 0);
                    long dur = long_max(ing[0].dur * p0 + ing[1].dur * p1 + ing[2].dur * p2 + ing[3].dur * p3, 0);
                    long flv = long_max(ing[0].flv * p0 + ing[1].flv * p1 + ing[2].flv * p2 + ing[3].flv * p3, 0);
                    long tex = long_max(ing[0].tex * p0 + ing[1].tex * p1 + ing[2].tex * p2 + ing[3].tex * p3, 0);
                    long cal = ing[0].cal * p0 + ing[1].cal * p1 + ing[2].cal * p2 + ing[3].cal * p3;
                    long score = cap * dur * flv * tex;
                    if (score > max) {
                        max = score;
                    }
                    if (cal == 500 && score > max_healthy) {
                        max_healthy = score;
                    }
                }
            }
        }
    }

    printf("%ld\n", max);
    printf("%ld\n", max_healthy);

    del_lines(input);
}
