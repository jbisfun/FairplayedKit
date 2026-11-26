// Linux: link with -Wl,--wrap=malloc,--wrap=calloc and -lz.
#include "zipio.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned fail_at, allocations;
void *__real_malloc(size_t);
void *__real_calloc(size_t, size_t);
static int fail(void) {
    if (++allocations != fail_at) return 0;
    errno = ENOMEM;
    return 1;
}
void *__wrap_malloc(size_t n) { return fail() ? NULL : __real_malloc(n); }
void *__wrap_calloc(size_t n, size_t size) { return fail() ? NULL : __real_calloc(n, size); }

int main(int argc, char **argv) {
    assert(argc == 4);
    char error[256];
    for (unsigned i = 1; i <= 4; i++) {
        allocations = 0;
        fail_at = i;
        error[0] = 0;
        assert(zip_extract_all(argv[1], argv[2], error, sizeof error) == -1);
        assert(strstr(error, "out of memory"));
    }
    fail_at = 0;
    assert(zip_extract_all(argv[1], argv[2], error, sizeof error) == 0);
    for (unsigned i = 1; i <= 4; i++) {
        allocations = 0;
        fail_at = i;
        error[0] = 0;
        assert(zip_create_from_dir(argv[2], argv[3], error, sizeof error) == -1);
        assert(strstr(error, "out of memory"));
    }
    fail_at = 0;
    assert(zip_create_from_dir(argv[2], argv[3], error, sizeof error) == 0);
    puts("ZIP allocation checks passed");
}
