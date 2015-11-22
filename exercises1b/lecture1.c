/* Dhruv Makwana, IB, Trinity College
 * Programming in C/C++ Lecture notes exercises.
 */

/* Q1. 'a' is a char but "a" is an immutable character array.
 * Q2. j is not initialised and also, it will terminate as soon as j >= 5.
 */

#include <stdio.h>
#include <stdbool.h>

int main() 
{
	int const len = 5;
	int arr[] = {'v', 'u', 'h', 'r', 'D'};

	bool swaps = true;
	int i = len-1;

	while (swaps && i >= 0) {

		swaps = false;
		for (int j = 0; j < i; j++) {
			if (arr[j+1] < arr[j]) {
				swaps = true;
				int tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
			}
		}
		
		i--;
	}

	for (int i = 0; i < len; i++) {
		printf("%c (%d) ", arr[i], arr[i]);
	}

	printf("\n");
}
