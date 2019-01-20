#include <stdint.h>

#define POOL_SIZE 13

struct pool {
    uint64_t w;
    uint32_t z[POOL_SIZE];
    uint32_t i;
};

extern struct pool *make_pool(void);

static inline uint32_t zrand32(struct pool *pool) {
    uint32_t i = pool->i;
    uint32_t j = i + 1;
    if (j >= POOL_SIZE)
        j -= POOL_SIZE;
    uint64_t w = pool->w + 0xb5ad4eceda1ce2a9;
    uint64_t zi = pool->z[i];
    uint64_t zj = pool->z[j];
    uint32_t r = ((zi + w) * (zj + w)) >> 32;
    pool->z[i] = r;
    pool->w = w;
    pool->i = j;
    return r;
}
