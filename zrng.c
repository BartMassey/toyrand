#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "zrng.h"

struct pool *make_pool(void) {
    struct pool *pool = malloc(sizeof *pool);
    assert(pool);
    pool->w = 0;
    pool->i = 0;
    int fd = open("/dev/urandom", O_RDONLY, 0);
    if (fd == -1) {
        perror("zrng: open /dev/urandom");
        exit(1);
    }
    int nread = read(fd, (char *) &pool->z, sizeof pool->z);
    if (nread != sizeof pool->z) {
        perror("zrng: read /dev/urandom");
        exit(1);
    }
    return pool;
}

