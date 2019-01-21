#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "zrng.h"

struct pool *make_pool(size_t npool) {
    assert(npool != 1);
    if (npool == 0)
        npool = DEFAULT_NPOOL;
    struct pool *pool = malloc(sizeof *pool);
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

void free_pool(struct pool *pool) {
    free(pool->pool);
    free(pool);
}
