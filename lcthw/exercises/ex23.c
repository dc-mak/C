#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>
#define LIM 1000
// I'd never do this in real life.
#define duff(val, c1, c2, c3, c4, c5, c6, c7, c8, code, cond); \
	switch ((val)) {\
		case (c1):\
			do {\
				(code);\
				case (c2): (code);\
				case (c3): (code);\
				case (c4): (code);\
				case (c5): (code);\
				case (c6): (code);\
				case (c7): (code);\
				case (c8): (code);\
			} while ((cond)); }\

double get_time_as_ms(clock_t start, clock_t end)
{
	return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

int normal_copy(char *from, char *to, int count)
{
	clock_t start = clock();

	int i = 0;
	for (i = 0; i < count; i++) {
		to[i] = from[i];
	}

	clock_t end = clock();
	log_info("Normal copy: %fms", get_time_as_ms(start, end));
	return i;
}

int duffs_device(char *from, char *to, int count)
{
	clock_t start = clock();

	int n = (count + 7) / 8;
	switch (count % 8) {
		case 0:
			do {
				*to++ = *from++;
				case 7:
				*to++ = *from++;
				case 6:
				*to++ = *from++;
				case 5:
				*to++ = *from++;
				case 4:
				*to++ = *from++;
				case 3:
				*to++ = *from++;
				case 2:
				*to++ = *from++;
				case 1:
				*to++ = *from++;
			} while (--n > 0);
	}

	clock_t end = clock();
	log_info("Duff's copy: %fms", get_time_as_ms(start, end));
	return count;
}

int zeds_device(char *from, char *to, int count)
{
	clock_t start = clock();

	int n = (count + 7) / 8;
	switch (count % 8) {
		case 0:
		again :
		*to++ = *from++;
		case 7:
		*to++ = *from++;
		case 6:
		*to++ = *from++;
		case 5:
		*to++ = *from++;
		case 4:
		*to++ = *from++;
		case 3:
		*to++ = *from++;
		case 2:
		*to++ = *from++;
		case 1:
		*to++ = *from++;
		if (--n > 0)
			goto again;
	}

	clock_t end = clock();
	log_info("Zed's copy: %fms", get_time_as_ms(start, end));
	return count;
}

int valid_copy(char *data, int count, char expects)
{
	for (int i = 0; i < count; i++) {
		if (data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}
	
	return 1;
}

int main(int argc, char *argv[])
{
	char from[LIM] = { 'a' };
	char to[LIM] = { 'c' };
	int rc = 0;

	// set up the from to have some stuff
	memset(from, 'x', LIM);
	// set it to a failure mode
	memset(to, 'y', LIM);
	check(valid_copy(to, LIM, 'y'), "Not initialised right.");

	// use normal_copy
	rc = normal_copy(from, to, LIM);
	check(rc == LIM, "Normal copy failed: %d", rc);
	check(valid_copy(to, LIM, 'x'), "Normal copy failed.");

	// reset
	memset(to, 'y', LIM);

	// duffs version
	rc = duffs_device(from, to, LIM);
	check(rc == LIM, "Duff's device failed: %d", rc);
	check(valid_copy(to, LIM, 'x'), "Duff's device failed copy.");

	// reset
	memset(to, 'y', LIM);

	// Zed's version
	rc = zeds_device(from, to, LIM);
	check(rc == LIM, "Zed's device failed: %d", rc);
	check(valid_copy(to, LIM, 'x'), "Zed's device failed copy.");
	
	return 0;

	error:
	return 1;
}
