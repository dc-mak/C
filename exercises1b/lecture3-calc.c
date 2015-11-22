/* Dhruv Makwana, IB, Trinity College
 * Programming in C/C++ Lecture notes exercises.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

int calculate(int const a, char const op, int const b)
{
	switch(op) {
		case '^' : {
					   int j = 1;
					   for (int i = 0; i < b; i++)
						   j *= a;
					   return j;
				   }
		case '*' : return b * a;
		case '/' : return b / a;
		case '%' : return b % a;
		case '-' : return b - a;
		default  : return b + a;
	}
}

bool isOp(char const op) {
	switch (op) {
		case '^':
		case '*':
		case '/':
		case '%':
		case '-':
		case '+': return true;
		default : return false;
	}
}

int main(int argc, char *argv[])
{
	int const len = 100;
	long stack[len];
	long top = -1;

	printf("%d arguments\n", argc);
	for (int i = 1; i < argc; i++) {

		printf("Processing: %s\n", argv[i]);
		if (strlen(argv[i]) == 1 && isOp(*argv[i])) {

			printf("\tOperation %c\n", *argv[i]);
			if (top >= 1) {
				long const a = stack[top--];
				long const b = stack[top--];
				stack[++top] = calculate(a, *argv[i], b);
				printf("\t %ld %c %ld = %ld\n", a, *argv[i], b, stack[top]);
			} else {
				fprintf(stderr, "Invalid input\n");
				return 1;
			}

		} else {

			if (top < len-1) {

				errno = 0;
				stack[++top] = strtol(argv[i], NULL, 10);
				if (errno != 0) {
					fprintf(stderr, "Invalid input\n");
					return 1;
				}
				printf("\tNumber %ld pushed\n", stack[top]);

			} else {

				fprintf(stderr, "Out of stack\n");
				return 1;

			}
		}
	}

	printf("Result: %ld\n", stack[0]);
}
