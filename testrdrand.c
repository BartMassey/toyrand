/*
 * Copyright © 2019 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file LICENSE in the source
 * distribution of this software for license terms.
 */

/* Check that the inline asm `rdrand` is actually OK. */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "rdrand.h"

int main() {
#ifndef RDRAND
    fprintf(stderr, "testrdrand: RDRAND disabled\n");
    return 1;
#endif

    assert(has_rdrand());

    for (int i = 0; i < 20; i++)
        printf("%016lx\n", rdrand64_checked());
    printf("\n");

    uint32_t x = 0;
    for (int i = 0; i < 10000000; i++)
        x ^= rdrand32();
    printf("%08x\n", x);
    return 0;
}
