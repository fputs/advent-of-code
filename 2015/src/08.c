#include <stdio.h>
#include <string.h>

#include "lfinput.h"

static size_t part_one(char** input, size_t sz) {
    size_t code = 0, mem = 0;

    for (size_t i = 0; i < sz; ++i) {
        code += strlen(input[i]);
        for (size_t j = 1; j < strlen(input[i]) - 1; ++j) {
            if (input[i][j] == '\\') {
                if (input[i][j + 1] == '\"' || input[i][j + 1] == '\\') {
                    ++j;
                } else {
                    j += 3;
                }
            }
            ++mem;
        }
    }

    return code - mem;
}

static size_t part_two(char** input, size_t sz) {
    size_t code = 0, encoded = 0;

    for (size_t i = 0; i < sz; ++i) {
        code += strlen(input[i]);
        encoded += 6;
        for (size_t j = 1; j < strlen(input[i]) - 1; ++j) {
            if (input[i][j] == '\\' || input[i][j] == '\"') {
                ++encoded;
            }
            ++encoded;
        }
    }

    return encoded - code;
}

void advent2015day08(void) {
    size_t sz = 0;
    char **input = get_lines("input/08", &sz);

    printf("%zu\n", part_one(input, sz));
    printf("%zu\n", part_two(input, sz));

    del_lines(input);
}
