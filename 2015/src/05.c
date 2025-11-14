#include <stdio.h>
#include <stdlib.h>

#include <lfinput.h>

void advent2015day05(void) {
    /* Sometimes, grep really is the best tool */
    const char *p1 = capture_system(
            "grep -E \"(.*[aeiou]){3}\" ./input/2015/05 | grep \"\\(.\\)\\1\" | egrep -v \"(ab|cd|pq|xy)\" | wc -l", 0);
    const char *p2 = capture_system("grep \"\\(..\\).*\\1\" ./input/2015/05 | grep \"\\(.\\).\\1\" | wc -l", 0);

    printf("%s%s", p1, p2);

    free(p1);
    free(p2);
}
