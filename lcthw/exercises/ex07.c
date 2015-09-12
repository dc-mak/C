#include <stdio.h>

int main(int argc, char *argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.5432;
	char initial = 'C';
	char first_name[] = "Dhruv";
	char last_name[]  = "Makwana";

	printf("You are %d miles away.\n", distance);
	printf("You have %f levels of powers.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have a middle initial %c.\n", initial);
	printf("I have a first name %s.\n", first_name);
	printf("I have a last name %s.\n", last_name);
	printf("My name is %s %c. %s.\n", first_name, initial, last_name);
	
	int bugs = 100;
	double bug_rate = 1.2;
	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);

	// long universe_of_defects = 9223372036854775808L;
	unsigned long universe_of_defects = 18446744073709551615UL;
	printf("The universe has %lu bugs.\n", universe_of_defects);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double part_of_universe = expected_bugs / universe_of_defects;
	printf("That is only %e portion of the universe.\n", part_of_universe);

	// this makes no sense, just a demo of something weird
	char nul_byte = '\0';
	int care_percentage = bugs * nul_byte;
	printf("Which means (this is null %c) you should care %d%%.\n",
			nul_byte, care_percentage);

	return 0;
}

/* changed %ld to %d
 * passing printf the wrong arguments means it takes the wrong amount of bytes
 *    off the stack that represents the arguments
 * tried to overflow long, 1024L just turned to 0, random lead to negative
 * as a string, nul_byte is "(null)" but character is nothing
 * don't seem to get a *compiler* error for too large a long assignment
 * unsigned long needs UL suffix and %lu format specifier
 * because the hardware representation of a char is 8 bit number
 */
