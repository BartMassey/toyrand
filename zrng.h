#include <stdint.h>

#define POOL_SIZE 17

struct pool {
    uint32_t z[POOL_SIZE];
    uint32_t i;
};

extern struct pool *make_pool(void);

static inline uint32_t zrand32(struct pool *pool) {
    uint32_t i = pool->i;
    uint32_t z = pool->z[i];
    uint32_t j;
    j = i + 1 + (z & (POOL_SIZE - 2));
    if (j >= POOL_SIZE)
        j -= POOL_SIZE;
    uint32_t r = z ^ pool->z[j];
    pool->z[i] = r;
    i++;
    if (i >= POOL_SIZE)
        i -= POOL_SIZE;
    pool->i = i;
    return r;
}
