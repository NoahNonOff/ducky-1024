// author: BEAUFILS Noah
// date: march/26/2024

#include "algorithm.h"
#include <stdio.h> /* I/O functions */

#ifdef TEST

int	main(int ac, char *av[]) {

	if (ac < 2)
		return 1;

	for (int i = 1; i < ac; i++) {
		char	hash[33] = { 0 };
		printf("%s=\"%s\"\n", av[i], md5(av[i], hash));
	}
	return 0;
}

#else

void	error(const char *msg, const int err) {

	write(2, "error: ", 7);
	write(2, msg, strlen(msg));
	switch (c) {
		case 1:
			write(2, " : ")
			break ;
	}
}

int	main(int ac, char *av[]) {

	if (ac < 1) {
		printf("error: %s: ")
	}
	return 0;
}

#endif