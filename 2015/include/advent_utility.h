#ifndef ADVENT_H_UTILITY_
#define ADVENT_H_UTILITY_

#include "lfvector.h"

#define DEFAULT_DELIM " \t\n\r\f\v"

#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)

char *md5_str(const char *);
Vector *string_to_int_vector(const char *input_string, const char *delim);
int int_comp(const void *a, const void *b);
char **get_matches(char *in, char *pat, size_t *sz, size_t max_matches);
void free_matches(char **matches, size_t sz);

enum Direction {
    DIR_NORTH = 0,
    DIR_EAST = 1,
    DIR_SOUTH = 2,
    DIR_WEST = 3,
};

void turn_right(enum Direction *d);
void turn_left(enum Direction *d);

#endif
