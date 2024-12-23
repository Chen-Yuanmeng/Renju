#ifndef __XORSHIFT_H
#define __XORSHIFT_H

#include <stdint.h>
#include <stdio.h>

typedef struct xorshift32_state {
    uint64_t a;
} Xorshift64;

uint64_t xorshift64_next(Xorshift64 *state);
unsigned long long xorshift64_rand(Xorshift64* rng);

#endif
