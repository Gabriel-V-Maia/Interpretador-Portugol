#include "../third-party/zest.h"
#include <stdio.h>
#include <string.h>

ZEST_TEST(test_fib_output) {
    FILE *f = popen("./build/portugol.out examples/fibbonaci.por", "r");
    ZEST_ASSERT_NOTNULL(f);
    char output[64];
    fgets(output, sizeof(output), f);
    pclose(f);
    // fibonacci(10) = 55
    ZEST_ASSERT_STR_EQ(output, "55\n");
}
