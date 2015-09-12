#include <stdio.h>

/* This is a comment. */
int main(int argc, char *argv[])
{
	int distance = 100;

	// this is also a comment
	printf("You are %d miles away.\n", distance);
	printf("You are %d miles away.\n");
	printf("This is %s very %s.\n", "something", "interesting");
	printf("Very %s%s.\n", "interesting"/*, "indeed"*/);

	return 0;
}

// Program usually crashes if the binary is messed with.
/* include		preprocessor
 * stdio.h		standard input/output header
 * int			integer primitive type
 * main			execution point
 * argc			argument list length
 * argv			arguments
 * char *[]		pointer to first array of characters
 * printf		print formatted
 * return 0		signal to OS that execution has completed "without error"
 */
