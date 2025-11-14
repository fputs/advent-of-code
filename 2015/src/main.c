#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <bsd/stdlib.h>
#else
#include <stdlib.h>
#endif

#include "advent.h"

int main(int argc, char **argv) {
    int day = 0;
    printf("Day: ");
    scanf("%d", &day);
    if (day < 1 || day > 25) {
        printf("Invalid day\n");
        return 1;
    }
    solutions2015[day - 1]();
    return 0;
}
