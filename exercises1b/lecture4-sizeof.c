#include <stdio.h>

void f(int j[5])
{
	printf("sizeof(j[5]) = %zd\n", sizeof j);
}

void f2(int j[][10])
{
	printf("sizeof(j[][10]) = %zd\n", sizeof j);
}

int main()
{
	printf("sizeof(char) = %zd\n", sizeof(char));
	printf("sizeof(int) = %zd\n", sizeof(int));
	int a;
	printf("sizeof(a) = %zd\n", sizeof a);
	char b[5];
	printf("sizeof(b[5]) = %zd\n", sizeof(b[5]));
	char *c = &b[0];
	printf("sizeof(c) = %zd\n", sizeof(c));
	struct {int d; char e;} s;
	printf("sizeof(s) = %zd\n", sizeof(s));
	f(NULL);
	f2(NULL);
}	
