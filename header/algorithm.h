// author: BEAUFILS Noah
// date: march/26/2024

#ifndef __ALGORITHM
#define __ALGORITHM	1

#include "typeBits.h"

/////////////// pseudorandom number generator (PRNG) ///////////////

// Linear congruential generator (LCG) algorithm

u32b_t		rand( void ); /* function that create a pseudorandom number from the global seed */
void		srand( u32b_t seed ); /* function to change the working seed */
u32b_t		rand_r( u32b_t *seedp ); /* function that create a pseudorandom number from the given seed */

// Mersenne Twister (MT19937) algorithm

u32b_t		mt_rand( void );
void		mt_srand( u32b_t seed );
u32b_t		mt_rand_r( u32b_t *mt, u16b_t *mti );

#endif /* algorithm.h */