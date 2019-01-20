#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "zrng.h"

int main(int argc, char **argv) {
    assert(argc == 2);
    uint64_t count = atol(argv[1]);
    uint32_t result = 0;
    struct pool *pool = make_pool();
    for (uint64_t i = 0; i < count; i++)
        result ^= zrand32(pool);
    printf("%d\n", result);
    return 0;
}
