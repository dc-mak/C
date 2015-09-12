#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declaration
void print_letters(int len, char arg[]);

void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(strlen(*(argv + i)), *(argv + i));
	}
}

void print_letters(int len, char arg[])
{
	int i = 0;
	
	// alpha
	printf("Alphabet\n");
	for (i = 0; *(arg + i) != '\0'; i++) {
		char ch = *(arg + i);
		if (isalpha(ch) || isblank(ch)) {
			printf("%c == %d    ", ch, ch);
		}
	}

	// digits
	printf("\nDigits\n");
	for (i = 0; *(arg + i) != '\0'; i++) {
		char ch = *(arg + i);
		if (isdigit(ch)) {
			printf("%c == %d    ", ch, ch);
		}
	}}

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);
	return 0;
}

/* segfaults for argc+1
 * removing forwards declarations does cause compiler complains
 */
