#include <stdio.h>

int main(int argc, char *argv[])
{
	char full_name[] =
		{'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w'};
	int areas[] = {10, 12, 13, 14, 20};
	char name[] = "Zed";

	// WARNING: On some systems, you may have to change the
	// %ld in this code to %u since it will use unsigned ints.
	printf("The size of an int: %ld.\n", sizeof(int));
	printf("The size of areas (int[]): %ld.\n", sizeof(areas));
	printf("The number of ints in areas: %ld.\n", sizeof(areas)/sizeof(int));
	printf("The first area is %d and the second area is %d.\n",
			areas[10], areas[1]);

	printf("The size of a char: %ld.\n", sizeof(char));
	printf("The size of name (char[]): %ld.\n", sizeof(name));
	printf("The number of chars: %ld.\n", sizeof(name)/sizeof(char));

	printf("The size of full_name (char[]): %ld.\n", sizeof(full_name));
	printf("The number of chars: %ld.\n", sizeof(full_name)/sizeof(char));

	areas[100] = -1;
	areas[2] = name[1];
	areas[3] = full_name[9];
	// name is read-only so cannot be assigned to
	full_name[11] = 'X';

	int i = 0;
	for (i = 0; i < 5; i++) {
		printf("%d ", areas[i]);
	}

	printf("\nname=\"%s\" and full_name=\"%s\"\n", name, full_name);

	return 0;
}

// int is required by the standard to have minimum 16 bits but usually has 32
