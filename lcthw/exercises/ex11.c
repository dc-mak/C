#include <stdio.h>

int main(int argc, char *argv[])
{
	int numbers[4] = { 0 };
	// it adds a null character to the end of this automagically
	char name[4] = { 'a', 'a', 'a', 'a'} ;

	printf("Initial:\n---\n");
	// first, print them out raw
	printf("numbers: %d %d %d %d\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);

	printf("name each: %c %c %c %c\n",
			name[0], name [1], name [2], name [3]);

	printf("name: %s\n", name);
	// printf("end: %s\n", name[4]);

	printf("\nAfter mess around:\n---\n");

	// set-up the numbers
	numbers[0] = 'Z';
	numbers[1] = 'e';
	numbers[2] = 'd';
	numbers[3] = 'A';

	// set-up name
	name[0] = 82;
	name[1] = -56;
	name[2] = 65;
	name[3] = -1;

	// then print them out initialised
	printf("numbers: %c %c %c %c\n",
			numbers[0], numbers[1], numbers[2], numbers[3]);

	printf("name each: %d %d %d %d\n",
			name[0], name[1], name[2], name[3]);

	// print the name like a string
	printf("name: %s (as string)\n", name);

	// treat whole name array like an integer
	// this will work if set-up name has no -1 assignments
	// at which point the corresponding hex digit is one less
	int some = (((int) name[3])<<24) + (((int) name[2])<<16) +
				(((int) name[1])<<8) + ((int) name[0]);

	printf("name: %02x %02x %02x %02x \n\t%s\n\t%s",
			name[3], name[2], name[1], name[0],
			"(as hex pattern - only look at last two characters",
			"1 byte = 2^8 = 16^2)\n");


	// and with pointers
	int *tmp = (int*) name;
	printf("name: %x (as hex) %d (decimal)\n", *tmp, *tmp);
	printf("some: %x (hex) %d (dec)\n", some, some);
	
	// another
	printf("\nanother:\n---\n");
	char *another = "Zed";

	printf("another each: %c %c %c %c\n",
			another[0], another[1], another[2], another[3]);

	// segfault... see below, another is in read-only memory with ""
	another[3] = 'A';
	printf("another: %s\n", another);

	return 0;
}

/* assigning a character array fully appends a null character
 * however doing one and then assigning allows breaking printf output
 *
 * "" vs char *: latter is assigned in read-only memory
 *
 * debugger represents values as per their type and not their assignment
 *
 * you could use bit shifting to do so (or in printf just use it)
 *    or use pointers to point to a 4-byte char array as an int
 *
 * code does not keep working if you assign a character array a string
 * 
 */
