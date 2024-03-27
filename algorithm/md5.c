// author: BEAUFILS Noah
// date: march/27/2024

#include "typeBits.h"

#ifndef MD5_F
#define MD5_F

	#define S11 7
	#define S12 12
	#define S13 17
	#define S14 22
	#define S21 5
	#define S22 9
	#define S23 14
	#define S24 20
	#define S31 4
	#define S32 11
	#define S33 16
	#define S34 23
	#define S41 6
	#define S42 10
	#define S43 15
	#define S44 21

	/* '^' = XOR ; '&' = AND ; '|' = OR ; '~' = NOT */

	// #define F(B, C, D) (((B) & (C)) | ((~B) & (D)))
	#define F(B, C, D) ((D) ^ ((B) & ((C) ^ (D)))) // For improved efficiency

	// #define G(B, C, D) (((B) & (D)) | ((C) & (~D)))
	#define G(B, C, D) ((C) ^ ((D) & ((B) ^ (C)))) // For improved efficiency

	#define H(B, C, D) ((B) ^ (C) ^ (D))
	#define I(B, C, D) ((C) ^ ((B) | ~(D)))

	#define ROTLEFT(word, bits) (((word) << (bits)) | ((word) >> (32 - (bits))))

	// Rotation is separate from addition to prevent recomputation

	#define FF(A, B, C, D, x, s, ac) {				\
		(A) += F((B), (C), (D)) + (x) + (ac);		\
		(A) = ROTLEFT((A), (s));					\
		(A) += (B);									\
	}

	#define GG(A, B, C, D, x, s, ac) {				\
		(A) += G((B), (C), (D)) + (x) + (ac);		\
		(A) = ROTLEFT((A), (s));					\
		(A) += (B);									\
	}

	#define HH(A, B, C, D, x, s, ac) {				\
		(A) += H((B), (C), (D)) + (x) + (ac);		\
		(A) = ROTLEFT((A), (s));					\
		(A) += (B);									\
	}

	#define II(A, B, C, D, x, s, ac) {				\
		(A) += I((B), (C), (D)) + (x) + (ac);		\
		(A) = ROTLEFT((A), (s));					\
		(A) += (B);									\
	}

#endif

///////////////////////////////////////////////////////////////////

static inline u32b_t	len(const char *str) {
	u32b_t	ret = 0;
	for (; str && str[ret]; ret++) {}
	return ret;
}

static inline void		insert(void *ptr, const void *dest, u32b_t len) {

	for (u_fast32b_t i = 0; i < len; i++)
		*(unsigned char *)(ptr + i) = *(const unsigned char *)(dest + i);
}

static void	decode(u32b_t output[], const u8b_t input[], u32b_t len) {

	for (u_fast32b_t i = 0, j = 0; j < len; i++, j += 4) {
		output[i] = ((u32b_t)input[j]) | (((u32b_t)input[j + 1]) << 8) |
			(((u32b_t)input[j + 2]) << 16) | (((u32b_t)input[j + 3]) << 24);
	}
}

static void	encode(u8b_t output[], const u32b_t input[], u32b_t len) {

	for (u_fast32b_t i = 0, j = 0; j < len; i++, j += 4) {

		/* (0xff) = (255) = (8 bits max) */
		output[j + 0] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8) & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}

// apply MD5 algo on a block
static void	transform(const u8b_t block[64], u32b_t *state) {

	u32b_t	M[16];
	decode(M, block, 64);

	u32b_t	a = state[0];
	u32b_t	b = state[1];
	u32b_t	c = state[2];
	u32b_t	d = state[3];

	/* Round 1 */
	FF (a, b, c, d, M[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, M[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, M[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, M[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, M[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, M[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, M[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, M[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, M[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, M[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, M[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, M[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, M[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, M[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, M[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, M[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, M[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, M[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, M[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, M[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, M[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, M[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, M[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, M[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, M[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, M[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, M[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, M[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, M[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, M[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, M[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, M[12], S24, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH (a, b, c, d, M[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, M[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, M[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, M[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, M[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, M[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, M[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, M[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, M[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, M[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, M[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, M[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, M[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, M[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, M[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, M[ 2], S34, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II (a, b, c, d, M[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, M[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, M[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, M[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, M[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, M[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, M[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, M[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, M[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, M[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, M[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, M[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, M[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, M[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, M[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, M[ 9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	for (u_fast8b_t i = 0; i < 16; i++)
		M[i] = 0;
}

static void	update(const u8b_t input[], u32b_t	length, u8b_t *buffer, u32b_t *count, u32b_t *state) {

	u32b_t	index = (u32b_t)((count[0] >> 3) & 0x3F); // same as (_count[0] / 8) % 64

	if ((count[0] += (length << 3)) < (length << 3)) // (length << 3) = (length * 8)
		count[1]++;
	count[1] += (length >> 29);

	// number of bytes we need to fill in buffer
	u32b_t	partLen = 64 - index;
	u32b_t	i = 0;

	if (length >= partLen)
	{
		// fill buffer first, transform
		insert(&buffer[index], input, partLen);
		transform(buffer, state);

		// transform chunks of blocksize (64 bytes)
		for (i = partLen; i + 64 <= length; i += 64)
			transform(&input[i], state);
		index = 0;
	}
	insert(&buffer[index], &input[i], length - i);
}

static void	finalize(u8b_t *buffer, u32b_t *count, u32b_t *state) {

	const static u8b_t	padding[64] = { // 0x80 -> 10000000
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	// Save number of bits
	u8b_t	bits[8];
	encode(bits, count, 8);

	// pad out to 56 mod 64.
	u32b_t	index = (u32b_t)((count[0] >> 3) & 0x3F);
	u32b_t	padLen = (index < 56) ? (56 - index) : (120 - index);

	update(padding, padLen, buffer, count, state);

	// Append length (before padding)
	update(bits, 8, buffer, count, state);
}

const char *md5(char * restrict raw, char *dest) {

	u8b_t	buffer[64];
	u32b_t	count[2] = { 0 };
	u32b_t	state[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

	update((const u8b_t *)raw, len(raw), buffer, count, state);
	finalize(buffer, count, state);

	u8b_t	digest[16];
	char	hex[3] = { 0 };
	encode(digest, state, 16);

	/* convert the message digest to hexadecimal */
	for (u_fast8b_t i = 0; i < 16; i++) {
		hex[0] = (digest[i] < 16) ? '0' : "0123456789abcdef"[(digest[i] - (digest[i] % 16)) / 16];
		hex[1] = "0123456789abcdef"[digest[i] % 16];
		insert(&dest[i * 2], hex, 2);
	}

	return dest;
}
