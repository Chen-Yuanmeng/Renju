// This code is taken from https://en.wikipedia.org/wiki/Xorshift.

#include "xorshift.h"

/* The state must be initialized to non-zero */
uint64_t xorshift64_next(Xorshift64 *state) {
	uint64_t x = state->a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return state->a = x;
}

// Usage:
// ```
// Xorshift64 rng;
// rng.a = 123456789; // seed
// unsigned long long random_number = xorshift64_rand(&rng);
// ```
unsigned long long xorshift64_rand(Xorshift64* rng) {
	return xorshift64_next(rng) & 0xffffffffffffffffull;
}
