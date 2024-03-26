// author: BEAUFILS Noah
// date: march/26/2024

#include "algorithm.h"
#include <stdio.h> /* I/O functions */

int	main(int ac, char *av[]) {

	(void)ac;
	(void)av;
	mt_srand(4678);
	for (int i = 0; i < 100; i++)
		printf("%u\n", mt_rand());
}
