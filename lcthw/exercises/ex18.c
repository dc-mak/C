#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Our old friend die from ex17 */
void die(const char *message)
{
	if (errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	exit(1);
}

// typedef creates a fake type, in
// this case for a function pointer

typedef int (*compare_cb) (int a, int b);

typedef int *(*sort_alg_cb) (int *numbers, int count, compare_cb cmp);

/**
 * A classic bubble sort function that uses
 * the compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int tmp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		for (j = 0; j < count-1; j++) {
			if (cmp(target[j], target[j+1]) > 0) {
				tmp = target[j+1];
				target[j+1] = target[j];
				target[j] = tmp;
			}
		}
	}
	
	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	else
		return a % b;
}

int bad_func(int a, int b, int c)
{
	return a+b+c;
}

int *sel_sort(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int j = 0;
	int min = 0;
	int tmp = 0;

	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error");

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		min = i;
		for (j = i+1; j < count; j++) {
			if (cmp(target[min], target[j]) > 0)
				min = j;
		}
		tmp = target[min];
		target[min] = target[i];
		target[i] = tmp;
	}

	return target;
}

/** 
 * Used to test that we are sorting things correctly
 * by doing the sort then printing it out.
 */
void test_sorting(int *numbers, int count, sort_alg_cb sort, compare_cb cmp)
{
	int i = 0;
	int *sorted = sort(numbers, count, cmp);

	if (!sorted)
		die("Failed to sort as required.");

	for (i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	
	printf("\n");

	free(sorted);
}

void destroy(compare_cb cmp)
{
	int i = 0;

	unsigned char *data = (unsigned char *)cmp;

	for (i = 0; i < 25; i++) {
		data[i] = i;
	}

	printf("\n");
}

void dump(compare_cb cmp)
{
	int i = 0;

	unsigned char *data = (unsigned char *)cmp;

	for (i = 0; i < 25; i++) {
		printf("%02x:", data[i]);
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 4 3 2 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv+1;

	int *numbers = malloc(count * sizeof(int));
	if (!numbers) die("Memory error.");

	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, bubble_sort, sorted_order);
	test_sorting(numbers, count, sel_sort, reverse_order);
	test_sorting(numbers, count, sel_sort, strange_order);
	// test_sorting(numbers, count, bad_func);
	// test_sorting(numbers, count, NULL);

	free(numbers);

	printf("SORTED:");
	dump(sorted_order);

	destroy(sorted_order);

	printf("SORTED:");
	dump(sorted_order);

	return 0;
}

/* I think 55:48:89:e5 starts a function
 * 
 * type check doesn't work for wrong function
 * 
 * NULL segfaults as usual
 */
