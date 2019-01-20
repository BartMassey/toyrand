#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "zrng.h"

#define NBLOCK 256

uint32_t buf[NBLOCK];

int main(int argc, char **argv) {
    uint64_t count = 0;
    int ascii = 0;

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
        
        fprintf(stderr, "zprint: usage: zprint [-a] [-n <count]");
        return 1;
    }

    struct pool *pool = make_pool();
    for (uint64_t j = 0; count == 0 || j < count; j += NBLOCK) {
        int n = NBLOCK;
        if (count != 0 && j + NBLOCK >= count)
            n = count - j;
        for (int i = 0; i < n; i++)
            buf[i] = zrand32(pool);
        if (ascii) {
            for (int i = 0; i < n; i++)
                printf("0x%08x\n", buf[i]);
        } else {
            int result = write(1, (char *) buf, n * sizeof *buf);
            if (result != n * sizeof *buf) {
                perror("zprint: write");
                return -1;
            }
        }
    }
    return 0;
}
