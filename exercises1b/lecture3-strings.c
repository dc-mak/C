/* Dhruv Makwana, IB, Trinity College
 * Programming in C/C++ Lecture notes exercises.
 */

/* Q1. Just means *(p-2). Legal when in the program's address space. */

/* Q2. Naive string search: pointer to first occurence of s in f.
 *	   Also insecure as shit.
 */

#include <stdio.h>
#include <stdbool.h>

bool starts_here(char *s, char *f)
{
	while (*s != '\0' && *f != '\0') {
		if (*s != *f)
			return false;
		s++;
		f++;
	}

	return true;
}

char *strfind(char const *s, char const *f)
{
	char *f_tmp = (char *) f;

	while (*f_tmp != '\0') {
		if (starts_here((char *) s, f_tmp))
			return f_tmp;
		f_tmp++;
	}

	return NULL;
}

int main() 
{
	char *to_search = "This a test string to see if the correct pointer to Dhruv is found.";
	char *to_find   = "Dhruv";

	char *pos = strfind(to_find, to_search);

	printf("Predicted mem location: %p\n", to_search + 52);

	if (pos == NULL) {
		printf("Null ;-(\n");
	} else {
		printf("At mem location %p, is string: ", pos);
		for (int i = 0; i < 5; i++) printf("%c", pos[i]);
		printf("\n");
	}
}
