// author: BEAUFILS Noah
// date: march/26/2024

#include "algorithm.h"
#include <stdio.h> /* I/O functions */

int	main(int ac, char *av[]) {

	if (ac < 2)
		return 1;

	for (int i = 1; i < ac; i++) {
		char	hash[33] = { 0 };
		printf("%s=\"%s\"\n", av[i], md5(av[i], hash));
	}
	return 1;
}
