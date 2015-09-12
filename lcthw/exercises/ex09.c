#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	while (i < 25) {
		if (i == -1)
			break;
		printf ("%d ", i);
		i++;
	}
	printf("\n");

	i = 25;
	while (i > 0) {
		printf ("%d ", i);
		i--;
	}
	printf("\n");

	i = 25;
	while (i > 0) {
		if (i % 2 == 0)
			printf ("%d ", i);
		i--;
	}
	printf("\n");
}
