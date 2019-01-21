/*
 * Copyright © 2019 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file LICENSE in the source
 * distribution of this software for license terms.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "toyrand.h"

int main(int argc, char **argv) {
    assert(argc == 2);
    uint64_t count = atol(argv[1]);
    uint32_t result = 0;
    struct toyrand_pool *pool = toyrand_make_pool(0);
    for (uint64_t i = 0; i < count; i++)
        result ^= toyrand32(pool);
    printf("0x%08x\n", result);
    toyrand_free_pool(pool);
    return 0;
}
