// author: BEAUFILS Noah
// date: march/26/2024

#include "typeBits.h"

/////////// Linear congruential generator (LCG) algorithm ///////////

#ifndef RAND_MAX
# define RAND_MAX 2147483647
#endif

static u32b_t	g_lgcSeed = 1; /* the default seed */

/* LCG (Linear congruential generator) algorithm */
static u32b_t	lgc(u32b_t *seed) {

	/* num N = (((num N-1) * a) + c) % m */
	(*seed) = (((*seed) * 1103515245) + 12345) % RAND_MAX;
	return (u32b_t)(*seed);
}

void		srand(u32b_t seed) { g_lgcSeed = seed; }
u32b_t		rand(void) { return (lgc(&g_lgcSeed)); }
u32b_t		rand_r(u32b_t *seedp) { return (lgc(seedp)); }

/////////////// Mersenne Twister algorithm (MT19937) ////////////////

// period parameter
# define N 624
# define M 397
# define MATRIX_A	0x9908b0dfUL
# define UPPER_MASK	0x80000000UL
# define LOWER_MASK	0x7fffffffUL

// tempering parameters
#define TEMPERING_MASK_B		0x9d2c5680UL
#define TEMPERING_MASK_C		0xefc60000UL
#define TEMPERING_SHIFT_U(y)	(y >> 11)
#define TEMPERING_SHIFT_S(y)	(y << 7)
#define TEMPERING_SHIFT_T(y)	(y << 15)
#define TEMPERING_SHIFT_L(y)	(y >> 18)

static u32b_t		g_mt[N]; // array for state vector
static u16b_t		g_mti = N + 1; // N+1 means mt[] haven't been initialized yet
static u32b_t		g_mtSeed = 4357; /* the default seed */

inline static	void	setMatrice(u32b_t *mt, u16b_t *mti) {

	mt[0] = g_mtSeed & 0xffffffff;
	for ((*mti) = 1; (*mti) < N; (*mti)++)
		mt[(*mti)] = (69069 * mt[(*mti) - 1]) & 0xffffffff;
}

static u32b_t		mt19937(u32b_t *mt, u16b_t *mti) {

	u32b_t	y = 0;
	static u32b_t	mag01[2] = { 0x0, MATRIX_A };

	if ((*mti) >= N) {

		u_fast16b_t	i = 0;
		if ((*mti) == N + 1) { setMatrice(mt, mti); } // default seed
		for (; i < N - M; i++) {
			y = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
			mt[i] = mt[i + M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (; i < N - 1; i++) {
			y = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
			mt[i] = mt[i + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

		(*mti) = 0;
	}
	y = mt[(*mti)++];
	y ^= TEMPERING_SHIFT_U(y);
	y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
	y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
	y ^= TEMPERING_SHIFT_L(y);

	return y;
}

void		mt_srand(u32b_t seed) { g_mtSeed = seed; }
u32b_t		mt_rand(void) { return (mt19937(g_mt, &g_mti)); }
u32b_t		mt_rand_r(u32b_t *mt, u16b_t *mti) { return (mt19937(mt, mti)); }