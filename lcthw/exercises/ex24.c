#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE_EYES, GREEN_EYES, BROWN_EYES,
	BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

/* I think the lesson here is just use fgets and the sscanf. */
int main(int argc, char *argv[])
{
	Person you = {.age = 0 };
	int rc = 0;
	char *in = NULL;

	printf("What's you First Name? ");
	rc = fscanf(stdin, "%s", you.first_name);
	getchar();
	// or char ch; while ((ch = getchar()) != '\n' && ch != EOR);
	check(rc > 0, "Failed to read first name.");

	printf("What's you Last Name? ");
	// in = gets(you.last_name);
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read last name.");

	printf("How old are you? ");
	in = fgets(in, MAX_DATA-1, stdin);
	check(in != NULL, "Failed to read age.");
	you.age = strtol(in, NULL, 10);
	check(in != NULL, "You have to enter a number.");

	printf("What colour are your eyes:\n");
	for (int i = 0; i <= OTHER_EYES; i++) {
		printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
	}

	printf("> ");

	int eyes = -1;
	rc = scanf(" %d", &eyes);
	getchar();
	// or char ch; while ((ch = getchar()) != '\n' && ch != EOR);
	check(rc > 0, "You hae to enter a number.");
	you.eyes = eyes - 1;
	// check(you.eyes <= OTHER_EYES
	//		&& you.eyes >= 0, "Do it right, that's not an option.");

	printf("How much do you make an hour? ");
	in = fgets(in, MAX_DATA-1, stdin);;
	check(in != NULL, "Failed to read income.");
	you.income = strtof(in, NULL);
	check(in != NULL, "You have to enter a number.");

	printf("---- RESULTS ----\n");

	printf("First Name: %s", you.first_name);
	printf("Last Name: %s", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Income: %f\n", you.income);

	return 0;

	error:
	return -1;
}
