// author: BEAUFILS Noah
// date: march/26/2024

#ifndef __ALGORITHM
#define __ALGORITHM	1

#include "typeBits.h"

/////////////// pseudorandom number generator (PRNG) ///////////////

// Linear congruential generator (LCG) algorithm

u32b_t		rand( void );
void		srand( u32b_t seed );
u32b_t		rand_r( u32b_t *seedp );

// Mersenne Twister (MT19937) algorithm

u32b_t		mt_rand( void );
void		mt_srand( u32b_t seed );
u32b_t		mt_rand_r( u32b_t *mt, u16b_t *mti );

////////////////////////// hash functions //////////////////////////

/* dest must be at least 32 bits long */
const char	*md5(char * restrict raw, char *dest);

/* dest must be at least 64 bits long */
// const char *sha256(char * restrict raw, char *dest);

#endif /* algorithm.h */