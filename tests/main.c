#define ZEST_IMPLEMENTATION
#include "../third-party/zest.h"
#include "test_fibonacci.c"

int main(void) {
    ZEST_RUN("tests/", 1, "tests.log",
        ZEST_ENTRY(test_fib_output)
    );
    return 0;
}
