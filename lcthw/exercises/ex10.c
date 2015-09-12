#include <stdio.h>

int main(int argc, char *argv[])
{
	
	int i = 0;
	int j = 0;
	char letter = argv[1][i];
	for (j = 1; j < argc; j++) {
		for (i = 0, letter = argv[j][i]; argv[j][i] != '\0'; i++) {

			letter = argv[j][i];

			if (letter >= 97 && letter <= 122) {
				letter -= 32;
			}

			if (letter == 'A' || letter == 'E' || letter == 'I' ||
					letter == 'O' || letter == 'U') {

				printf("%d: %c\n", i, letter);

			} else if (letter == 'Y' && i > 2) {

				// it's only sometimes Y
				printf("%d: %c\n", i, letter);

			} else {

				printf("%d: %c is not a vowel\n", i, letter);

			}
		}
		printf("\n");
	}

	return 0;
}

/* if statement is better at catching the case where 'y'/'Y' is not a vowel
 * putting the break inside the if makes no difference */
