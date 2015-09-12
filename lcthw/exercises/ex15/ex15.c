#include <stdio.h>

void first_way(int count, char *names[], int ages[])
{
	// first way of using indexing
	while (count--) {
		printf("%s has %d years alive.\n", *(names + count), *(ages + count));
	}

	printf("---1)\n");
}

void second_way(int count, char **cur_name, int *cur_age)
{
	// second way of using pointers
	while (count--) {
		printf("%s is %d years old.\n", cur_name[count], cur_age[count]);
	}

	printf("---2)\n");
}

void third_way(int count, char **cur_name, int *cur_age)
{
	// third way of using pointersrs
	while (count--) {
		printf("%s is %d years old again.\n",
				*(cur_name + count), *(cur_age + count));
	}

	printf("---3)\n");
}

void fourth_way(int count, char *cur_name[], int cur_age[],
		char **names, int *ages)
{
	int i = 0;

	// fourth way with pointers in a stupid way
	while (cur_name != names-1 && cur_age != ages - 1) {
		printf("%s lived %d years so far.\n", *cur_name--, *cur_age--);
	}

	printf("---4)\n");
}

int main(int argc, char *argv[])
{
	// create two arrays we care about
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = { "Alan", "Frank", "Mary", "John", "Lisa" };

	// safely get size of names
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	first_way(count, names, ages);

	// set-up the pointers to the start of the array
	int *cur_age = (int *)names;
	char **cur_name = names;

	second_way(count, cur_name, cur_age);
	third_way(count, cur_name, cur_age);
	fourth_way(count, names+count-1, ages+count-1, names, ages);

	// command line arguments
	cur_name = argv;
	while (cur_name - argv < argc) {
		printf("argument: %s\n", *cur_name++);
	}
		
	// print pointers
	i = 0;
	while (i< count) {
		printf("name[%d]: %p\tage[%d]: %p\n", i, names+i, i, ages+i);
		i++;
	}

	printf("---5)\n");

	char *tmp = *(names + 2);
	printf("%s at %p which itself stored at %p\n", tmp, tmp, &tmp);
	int *ptr = &count;
	printf("%d at %p (or %d) which itself stored at %p\n",
			*ptr, ptr, ptr, &ptr);

	return 0;
}

/* There are plenty of ways to mess up pointers.
 * Most will end in a segfault at this level.
 */
