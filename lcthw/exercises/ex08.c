#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

	if (argc == 2) {
		printf("You only have one argument. You suck.\n");
	} else if (argc < 10) {
		printf("Here are your arguments:\n");

		// segfault in the waiting
		for (i = 0; 1; i++) {
			printf("%s ", argv[i]);
		}
		printf("\n");

	} else if (argc < 10 || argc < 9) {
		printf("Unreachable.\n");
	} else {
		printf("Lots of arguments.\n");
	}

	return 0;
}
