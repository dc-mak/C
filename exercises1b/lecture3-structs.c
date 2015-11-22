/* Dhruv Makwana, IB, Trinity College
 * Programming in C/C++ Lecture notes exercises.
 */

#include<stdio.h>
typedef struct structure {
	struct structure **s;
} structure;

int main()
{
	int const num = 6;
	structure str[num];
	structure *stb[num];

	for (int i = 0; i < num; i++)
		stb[num] = &str[i];

	for (int i = 0; i < num; i++)
		str[i].s = i == num-1 ? NULL : &stb[i];

	for (int i = 0; i < num; i++)
		printf("stb[%d] at %p has %p \t(in %p)\n", i, stb+i, stb[i], &stb[i]);
	printf("\n");

	for (int i = 0; i < num; i++)
		printf("str[%d] at %p has %p \t(in %p)\n", i, str+i, str[i].s, &str[i].s);

	structure *p = str;

	printf("\n(start) p = %p\n\n", p);

	printf("  ++p->s  = %p\n", ++p->s); // increments s of p
	printf("\tp = %p\n\n", p);

	printf("  p++->s  = %p\n", p++->s); // increments p
	printf("\tp = %p\n\n", p);

	printf(" *p->s    = %p\n", *p->s); // derefs s of p
	printf("\tp = %p\n\n", p);

	printf(" *p->s++  = %p\n", *p->s++); // increments s of p then derefs
	printf("\tp = %p\n\n", p);

	printf("(*p->s)++ = %p\n", (*p->s)++); // increments deref s of p
	printf("\tp = %p\n\n", p);

	printf(" *p++->s  = %p\n", *p++->s); // increments p then derefs s of it
	printf("(end)   p = %p\n\n", p);

	for (int i = 0; i < num; i++)
		printf("stb[%d] at %p has %p \t(in %p)\n", i, stb+i, stb[i], &stb[i]);
	printf("\n");

	for (int i = 0; i < num; i++)
		printf("str[%d] at %p has %p \t(in %p)\n", i, str+i, str[i].s, &str[i].s);

}
