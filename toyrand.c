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
#include <unistd.h>

#include "toyrand.h"

struct toyrand_pool *toyrand_make_pool(size_t npool) {
    if (npool == 0)
        npool = DEFAULT_NPOOL;
    else
        /* Pool must be at least two and be a power of two. */
        assert(npool >= 2 && (npool & (npool - 1)) == 0);
    struct toyrand_pool *pool = malloc(sizeof *pool);
    assert(pool);
    pool->pool = malloc(npool * sizeof *pool->pool);
    assert(pool->pool);
    pool->w = 0;
    pool->i = 0;
    int fd = open("/dev/urandom", O_RDONLY, 0);
    if (fd == -1) {
        perror("zrng: open /dev/urandom");
        exit(1);
    }
    size_t nbpool = npool * sizeof *pool->pool;
    int nread = read(fd, (char *) pool->pool, nbpool);
    if (nread != nbpool) {
        perror("zrng: read /dev/urandom");
        exit(1);
    }
    return pool;
}

void toyrand_free_pool(struct toyrand_pool *pool) {
    free(pool->pool);
    free(pool);
}
