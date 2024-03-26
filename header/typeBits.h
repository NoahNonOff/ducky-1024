// author: BEAUFILS Noah
// date: march/26/2024

#ifndef __TYPEBITS
#define __TYPEBITS	1

/*
	__extension__ : is a compiler-specific extension that tells the compiler
	to accept code constructs that might not strictly conform to the C standard.

	__WORDSIZE : is a compiler-specific macro that is often used to indicate the
	size of a machine word on the target platform. It typically represents the
	number of bits in a machine word, which is the native unit of data processing
	for the CPU architecture.
*/

/* signed types */
typedef signed char				s8b_t;
typedef signed short int		s16b_t;
typedef signed int				s32b_t;
#if __WORDSIZE == 64
typedef long int				s64b_t;
#else
__extension__
typedef signed long long int	s64b_t;
#endif

/* unsigned types */
typedef unsigned char			u8b_t;
typedef unsigned short int		u16b_t;
typedef unsigned int			u32b_t;
#if __WORDSIZE == 64
typedef unsigned long int		u64b_t;
#else
__extension__
typedef unsigned long long int	u64b_t;
#endif

/* fast types */
#ifndef FAST_TYPE

// signed
typedef signed char				s_fast8b_t;
#if __WORDSIZE == 64
typedef long int				s_fast16b_t;
typedef long int				s_fast32b_t;
typedef long int				s_fast64b_t;
#else
typedef int						s_fast16b_t;
typedef int						s_fast32b_t;
__extension__
typedef long long int			s_fast64b_t;
#endif

//unsigned
typedef unsigned char			u_fast8b_t;
#if __WORDSIZE == 64
typedef unsigned long int		u_fast16b_t;
typedef unsigned long int		u_fast32b_t;
typedef unsigned long int		u_fast64b_t;
#else
typedef unsigned int			u_fast16b_t;
typedef unsigned int			u_fast32b_t;
__extension__
typedef unsigned long long int	u_fast64b_t;
#endif

#define FAST_TYPE	1
#endif 

/* conversion macros */
#ifndef TYPE_CONVERSION

// signed
#define s8b_c(c)	c
#define s16b_c(c)	c
#define s32b_c(c)	c
#if __WORDSIZE == 64
#define s64b_c(c)	c ## L
#else
#define s64b_c(c)	c ## LL
#endif

// unsigned
#define u8b_c(c)	c
#define u16b_c(c)	c
#define u32b_c(c)	c ## U
#if __WORDSIZE == 64
#define u64b_c(c)	c ## UL
#else
#define u64b_c(c)	c ## ULL
#endif

#define TYPE_CONVERSION	1
#endif /* TYPE_CONVERSION */

#endif /* typebits.h */