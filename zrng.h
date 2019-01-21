#include <stdint.h>

#define DEFAULT_NPOOL 16

struct pool {
    uint64_t w;
    uint32_t *pool;
    size_t i, npool;
};

extern struct pool *make_pool(size_t pool_size);

extern void free_pool(struct pool *pool);

static inline uint32_t zrand32(struct pool *pool) {
    size_t i = pool->i;
    size_t j = i + 1;
    if (j >= pool->npool)
        j = 0;
    uint64_t w = pool->w + 0xb5ad4eceda1ce2a9;
    uint64_t zi = pool->pool[i];
    uint64_t zj = pool->pool[j];
    uint32_t r = (zi * zj + w) >> 16;
    pool->pool[i] = r;
    pool->w = w;
    pool->i = j;
    return r;
}
