/*
 * Copyright © 2019 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file LICENSE in the source
 * distribution of this software for license terms.
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "toyrand.h"

#define NBLOCK 256

uint32_t buf[NBLOCK];

int main(int argc, char **argv) {
    uint64_t count = 0;
    int ascii = 0;
    size_t npool = 0;

    argc--, argv++;
    while (argc > 0) {
        if (!strcmp(argv[0], "-a")) {
            ascii = 1;
            argc--, argv++;
            continue;
        }
        
        if (!strcmp(argv[0], "-n") && argc > 1) {
            count = atol(argv[1]);
            argc -= 2, argv += 2;
            continue;
        }
        
        if (!strcmp(argv[0], "-p") && argc > 1) {
            npool = atol(argv[1]);
            if (npool < 2 || (npool & (npool - 1))) {
                fprintf(stderr, "toyprint: pool size must be "
                        "power of 2 greater than 2\n");
                return 1;
            }
            argc -= 2, argv += 2;
            continue;
        }
        
        fprintf(stderr, "toyprint: usage: "
                "toyprint [-a] [-n <count>] [-p <npool>]\n");
        return 1;
    }

    struct toyrand_pool *pool = toyrand_make_pool(npool);
    assert(pool);
    for (uint64_t j = 0; count == 0 || j < count; j += NBLOCK) {
        int n = NBLOCK;
        if (count != 0 && j + NBLOCK >= count)
            n = count - j;
        for (int i = 0; i < n; i++)
            buf[i] = toyrand32(pool);
        if (ascii) {
            for (int i = 0; i < n; i++)
                printf("0x%08x\n", buf[i]);
        } else {
            int result = write(1, (char *) buf, n * sizeof *buf);
            if (result != n * sizeof *buf) {
                perror("toyprint: write");
                return -1;
            }
        }
    }
    toyrand_free_pool(pool);
    return 0;
}
