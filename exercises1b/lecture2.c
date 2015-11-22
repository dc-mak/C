/* Dhruv Makwana, IB, Trinity College
 * Programming in C/C++ Lecture notes exercises.
 */

/* Q4. No, because i++ is textually substituted in twice. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SWAP(t,x,y)	  t const tmp = (x); (x) = (y); (y) = tmp
#define XOR_SWAP(x,y) (x) = (x) ^ (y); (y) = (x) ^ (y); (x) = (x) ^ (y)

int count_lower(char str[])
{
	int total = 0;
	for (int i = 0; str[i] != '\0'; i++)
		total += 'a' <= str[i] && str[i] <= 'z';
	return total;
}

void merge(int *arr,
			int unsigned const first,
			int unsigned const mid,
			int unsigned const last)
{
	int const left  = mid - first;
	
	printf("merge: (%d, %d, %d)\n", first, mid, last);

	int tmp[left];
	printf("\ttmp: ");
	for (int i = 0; i < left; i++) {
		printf("%d ", arr[i+first]);
		tmp[i] = arr[i+first]; // LEAVE THIS ALONE
	}
	printf("\n");

	printf("\trst: ");
	for (int i = mid; i <= last; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	int k = 0;
	int j = mid;

	for (int i = first; i <= last; i++) {

		if (k >= left) {

			while (j <= last) {
				arr[i] = arr[j];
				i++;
				j++;
			}
			break;

		} else if (j > last) {

			while (k < left) {
				arr[i] = tmp[k];
				i++;
				k++;
			}
			break;

		} else if (tmp[k] < arr[j]) {

			arr[i] = tmp[k];
			k++;

		} else /* (tmp[k] > arr[j]) */  {

			arr[i] = arr[j];
			j++;

		}

	}

}

void mergesort(int *arr,
				int unsigned const first,
				int unsigned const last)
{

	printf("before: ");
	for (int i = first; i <= last; i++) 
		printf("%d ", arr[i]);
	printf("\n");

	if (first < last) {
		int mid = first + (last - first) / 2;
		mergesort(arr, first, mid);
		mergesort(arr, mid+1, last);
		merge(arr, first, mid+1, last);
	}

	printf("after : ");
	for (int i = first; i <= last; i++) 
		printf("%d ", arr[i]);
	printf("\n\n");

}

int main()
{
	int * const arr = malloc(13 * sizeof(int));
	int const len = 13;

	{
		int const tmp[] = {2,34,6,4,27,2,0,0,1,7,9,3,2};
		for (int i = 0; i < len; i++)
			arr[i] = tmp[i];
	}

	mergesort(arr, 0, len-1);
	for (int i = 0; i < len; i++) 
		printf("%d ", arr[i]);
	printf("\n");

	free(arr);

	// SWAP
	int a = 54;
	int b = 69;

	SWAP(int, a,b);
	printf("a = %d, b = %d\n", a, b);

	XOR_SWAP(a,b);
	printf("a = %d, b = %d\n", a, b);
}
