#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include "pcre2.h"

#if defined __linux__ || defined __APPLE__
#include <openssl/md5.h>
#else
#include <md5.h>
#endif

#include "advent_utility.h"

char *md5_str(const char *input) {
    unsigned char digest[16];

#if defined __linux__ || defined __APPLE__
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input, strlen(input));
    MD5_Final(digest, &context);
#else
    struct MD5Context context;
    MD5Init(&context);
    MD5Update(&context, input, strlen(input));
    MD5Final(digest, &context);
#endif

    char *md5string = malloc(33);
    for (int i = 0; i < 16; ++i) {
        snprintf(&md5string[i * 2], 33, "%02x", (unsigned int) digest[i]);
    }
    return md5string;
}

Vector *string_to_int_vector(const char *input_string, const char *delim) {
    char *copy = strdup(input_string);
    char *token = strtok(copy, delim);
    Vector *v = malloc(sizeof(Vector));
    vec_init(v, free);

    while (token != NULL) {
        int *i = malloc(sizeof(int));
        *i = atoi(token);
        vec_push(v, i);
        token = strtok(NULL, delim);
    }

    free(copy);
    return v;
}

int int_comp(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

char **get_matches(char *in, char *pat, size_t *sz, size_t max_matches) {
    pcre2_code *re;
    PCRE2_SPTR pattern = (PCRE2_SPTR)pat;
    int errnum;
    size_t erroff;
    PCRE2_SPTR8 substr;
    size_t substr_sz;
    PCRE2_SPTR subject = (PCRE2_SPTR)in;
    size_t subject_sz = strlen(in);

    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroff, NULL);
    if (re == NULL) {
        char buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int) erroff, buffer);
        return NULL;
    }

    char **matches = NULL;
    matches = malloc(sizeof(char *) * max_matches);
    if (matches == NULL) {
        printf("failed to malloc matches\n");
        pcre2_code_free(re);
        return NULL;
    }

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern_8(re, NULL);
    int rc = pcre2_match(re, subject, subject_sz, 0, 0, match_data, NULL);
    if (rc < 0) {
        switch (rc) {
            case PCRE2_ERROR_NOMATCH:
                printf("PCRE2 no matches\n");
            break;
            default:
                printf("PCRE2 matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);
        pcre2_code_free(re);
        return NULL;
    }

    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
    *sz = 0;
    for (int i = 0; i < rc; ++i) {
        substr = subject + ovector[2*i];
        substr_sz = ovector[2*i+1] - ovector[2*i];
        matches[*sz] = (char *) malloc(substr_sz + 1);
        strncpy(matches[*sz], substr, substr_sz);
        *sz += 1;
    }

    // Now loop through rest of the matches, if there are any
    for (;;) {
        uint32_t options = 0;
        PCRE2_SIZE start_offset = ovector[1];

        // Check for empty match
        if (ovector[0] == ovector[1]) {
            if (ovector[0] == subject_sz) {
                break;
            }
            options = PCRE2_NOTEMPTY_ATSTART | PCRE2_ANCHORED;
        }

        rc = pcre2_match(re, subject, subject_sz, start_offset, options, match_data, NULL);
        if (rc == PCRE2_ERROR_NOMATCH) {
            // All matches have been found
            if (options == 0) {
                break;
            }

            // Handle newlines
            ovector[1] = start_offset + 1;
            if (start_offset < subject_sz - 1 &&
                //subject[start_offset] == '\r' &&
                subject[start_offset + 1] == '\n') {
                ovector[1] += 1;
            }
            continue;
        }

        // Other failures, non-recoverable
        if (rc < 0) {
            printf("PCRE2 match-matching error %d\n", rc);
            pcre2_match_data_free(match_data);
            pcre2_code_free(re);
            free_matches(matches, *sz);
            return NULL;
        }


        for (int i = 0; i < rc; ++i) {
            substr = subject + ovector[2*i];
            substr_sz = ovector[2*i+1] - ovector[2*i];
            matches[*sz] = (char *) malloc(substr_sz + 1);
            strncpy(matches[*sz], substr, substr_sz);
            *sz += 1;
        }
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    return matches;
}

void free_matches(char **matches, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        free(matches[i]);
    }
    free(matches);
}

void turn_right(enum Direction *d) {
    *d = *d == DIR_WEST ? DIR_NORTH : *d + 1;
}

void turn_left(enum Direction *d) {
    *d = *d == DIR_NORTH ? DIR_WEST : *d - 1;
}
