#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "uthash.h"
#include "lfinput.h"
#include "lfbool.h"

#ifdef __linux__
#include <bsd/stdlib.h>
#else
#include <stdlib.h>
#endif

struct Wire {
    char name[8];
    uint16_t val;
    UT_hash_handle hh;
};

struct Wire *wires = NULL;

static void set_wire(const char *name, int v) {
    struct Wire *w;
    HASH_FIND_STR(wires, name, w);
    if (w == NULL) {
        w = malloc(sizeof(struct Wire));
        strlcpy(w->name, name, 8);
        HASH_ADD_STR(wires, name, w);
    }
    w->val = v;
}

static struct Wire *get_wire(const char *name) {
    struct Wire *w = NULL;
    HASH_FIND_STR(wires, name, w);
    return w;
}

static void clear_wires() {
    struct Wire *c, *t;
    HASH_ITER(hh, wires, c, t) {
        HASH_DEL(wires, c);
        free(c);
    }
}

static uint16_t get_val(const char* n) {
    const char *errstr;

    uint16_t v = strtonum(n, 0, 1 << 16, &errstr);
    if (errstr == NULL) {
        return v;
    };

    struct Wire *w = get_wire(n);
    if (w == NULL) {
        return 0;
    }
    return w->val;
}

void advent2015day07(void) {
    size_t sz = 0;
    char **input = get_lines("input/07", &sz);
    size_t i = 0;
    int a_set = LFFALSE;

    while (!a_set) {
        int sz = strlen(input[i]) + 1;
        char *buf = malloc(sizeof(char) * sz);
        strlcpy(buf, input[i], sz);
        size_t sp_sz = 0;
        char **sp = split(buf, &sp_sz, " ");

        if (sp_sz == 3) {
            uint16_t a = get_val(sp[0]);
            if (a != 0) {
                set_wire(sp[2], a);
            }
        } else if (sp_sz == 4) {
            uint16_t a = get_val(sp[0]);
            if (a != 0) {
                set_wire(sp[2], ~a);
            }
        } else {
            uint16_t a = get_val(sp[0]);
            uint16_t b = get_val(sp[2]);
            if (a != 0 && b != 0) {
                if (strcmp(sp[1], "AND") == 0) {
                    set_wire(sp[4], a & b);
                } else if (strcmp(sp[1], "OR") == 0) {
                    set_wire(sp[4], a | b);
                } else if (strcmp(sp[1], "LSHIFT") == 0) {
                    set_wire(sp[4], a << b);
                } else if (strcmp(sp[1], "RSHIFT") == 0) {
                    set_wire(sp[4], a >> b);
                }
            }
        }

        uint16_t a = get_val("a");
        if (a != 0) {
            a_set = LFTRUE;
        }

        del_split(sp);
        ++i;
        if (i == sz) {
            i = 0;
        }
    }

    printf("%u\n", get_wire("a")->val);
    del_lines(input);
    clear_wires();
}
