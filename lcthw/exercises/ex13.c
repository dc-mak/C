#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 1;
	
	// let's make our own array of strings
	char *states[] = { "California", "Oregon", "Washington", "Texas" };
	
	argv[3] = states[2];
	states[2] = argv[1];

	// arguments: go through each string argv
	// why am I skipping argv[0]? 
	for (printf("init\n"), i = 1; printf("test\n"), i < argc; i++, printf("end\n")) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	// states
	for (i = 0; i < 6; i++) {
		printf("state %d: %s\n", i, states[i]);
	}
	
	// null
	printf("NULL assignment\n");
	*states = NULL;
	for (i = 0; i < 6; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	return 0;
}
