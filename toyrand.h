/*
 * Copyright © 2019 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file LICENSE in the source
 * distribution of this software for license terms.
 */

#include <stdint.h>

#define DEFAULT_NPOOL 16

struct toyrand_pool {
    uint64_t w;
    uint32_t *pool;
    size_t i, npool;
};

extern struct toyrand_pool *toyrand_make_pool(size_t pool_size);

extern void toyrand_free_pool(struct toyrand_pool *pool);

static inline uint32_t toyrand32(struct toyrand_pool *pool) {
    size_t i = pool->i;
    size_t j = i + 1;
    if (j >= pool->npool)
        j = 0;
    uint64_t w = pool->w;
    uint64_t zi = pool->pool[i];
    uint64_t zj = pool->pool[j];
    uint32_t r = (zi * zj + w) >> 16;
    pool->pool[i] = r;
    if (j == 0)
        w += 0xb5ad4eceda1ce2a9;
    pool->w = w;
    pool->i = j;
    return r;
}

/* https://lemire.me/blog/2016/06/30/fast-random-shuffling/ */
static inline uint32_t
toyrand_randrange32(struct toyrand_pool *pool, uint32_t n) {
    uint64_t r = toyrand32(pool);
    uint64_t m = (uint64_t) r * (uint64_t) n;
    if ((uint32_t) m < n) {
        uint32_t t = -n % n;
        while ((uint32_t) m < t) {
            r = toyrand32(pool);
            m = (uint64_t) r * (uint64_t) n;
        }
    }
    return m >> 32;
}
