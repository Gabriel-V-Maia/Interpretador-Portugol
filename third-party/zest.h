#ifndef ZEST_H
#define ZEST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef void (*test_function_t)(void);

typedef struct {
    const char *name;
    test_function_t func;
} zest_test;

typedef struct {
    const char *folder_name;
    uint8_t     logging;
    const char *log_file;
    int         passed;
    int         failed;
    size_t      num_tests;
    zest_test   tests[];
} zest_params;


#define ZEST_TEST(name)  void name(void)
#define ZEST_ENTRY(name) { #name, name }


#define ZEST_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "  FAIL  %s:%d  %s\n", __FILE__, __LINE__, #expr); \
            return; \
        } \
    } while (0)

#define ZEST_ASSERT_EQ(a, b)  ZEST_ASSERT((a) == (b))
#define ZEST_ASSERT_NEQ(a, b) ZEST_ASSERT((a) != (b))
#define ZEST_ASSERT_NULL(p)   ZEST_ASSERT((p) == NULL)
#define ZEST_ASSERT_NOTNULL(p) ZEST_ASSERT((p) != NULL)
#define ZEST_ASSERT_STR_EQ(a, b) ZEST_ASSERT(strcmp((a), (b)) == 0)


#ifdef ZEST_IMPLEMENTATION

static zest_params *zest_make_config(const char *folder_name,
                                     uint8_t logging,
                                     const char *log_file,
                                     zest_test tests[],
                                     size_t num_tests)
{
    zest_params *p = malloc(sizeof(zest_params) + sizeof(zest_test) * num_tests);
    if (!p) return NULL;

    p->folder_name = folder_name;
    p->logging     = logging;
    p->log_file    = logging ? log_file : NULL;
    p->passed      = 0;
    p->failed      = 0;
    p->num_tests   = num_tests;
    memcpy(p->tests, tests, sizeof(zest_test) * num_tests);
    return p;
}

static void zest_run(zest_params *p)
{
    if (!p) return;

    FILE *log = NULL;
    if (p->logging && p->log_file) {
        log = fopen(p->log_file, "w");
    }

    printf("\nzest: running %zu tests\n\n", p->num_tests);

    for (size_t i = 0; i < p->num_tests; i++) {
        printf("  [ RUN ] %s\n", p->tests[i].name);
        p->tests[i].func();
        printf("  [ OK  ] %s\n", p->tests[i].name);
        p->passed++;

        if (log) {
            fprintf(log, "PASS %s\n", p->tests[i].name);
        }
    }

    printf("\n─────────────────────────────\n");
    printf("  passed: %d  failed: %d\n\n", p->passed, p->failed);

    if (log) {
        fprintf(log, "\npassed: %d  failed: %d\n", p->passed, p->failed);
        fclose(log);
    }

    free(p);
}

#endif /* ZEST_IMPLEMENTATION */

#define ZEST_RUN(folder, logging, logfile, ...)                          \
    do {                                                                 \
        zest_test _tests[] = { __VA_ARGS__ };                           \
        size_t _n = sizeof(_tests) / sizeof(_tests[0]);                 \
        zest_params *_p = zest_make_config(folder, logging, logfile,    \
                                           _tests, _n);                 \
        zest_run(_p);                                                    \
    } while (0)

#endif /* ZEST_H */
