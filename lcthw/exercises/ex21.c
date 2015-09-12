// Program to get some info/practice with types.
#include <stdio.h>
#include <inttypes.h>
int main() 
{
	// apparently you can initialise in a loop from C99 onwards
	for (int i = 0; i < 10; i++) printf("%d ", i);

	printf("\n");
	// some values. btw, sizeof(uintptr_t) >= sizeof(size_t) so don't assume equality
	printf("ptrdiff_min: %"PRIdPTR "\tptrdiff_max: %"PRIdPTR "\tsize_max: %"PRIuPTR"",
			PTRDIFF_MIN, PTRDIFF_MAX, SIZE_MAX);

	printf("\n");
	// ptr ints
	intptr_t intptr = 0;
	printf("intptr_t:\neg: %"PRIdPTR"\tmax: %"PRIdPTR"\tmin: %"PRIdPTR"\tsize: %zu\n",
			intptr, INTPTR_MAX, INTPTR_MIN, sizeof(intptr_t));

	uintptr_t uintptr = 42;
	printf("uintptr_t:\neg: %"PRIuPTR"\tmax: %"PRIuPTR"\tmin: %"PRIuPTR"\tsize: %zu\n",
			uintptr, UINTPTR_MAX, (uintptr_t) 0, sizeof(uintptr_t));

	printf("\n");
	// max ints
	intmax_t intmax = -42;
	printf("intmax_t:\neg: %"PRIdMAX "\tmax: %"PRIdMAX "\tmin: %"PRIdMAX "\tsize: %zu\n",
			intmax, INTMAX_MAX, INTMAX_MIN, sizeof(intmax_t));

	uintmax_t uintmax = 42;
	printf("uintmax_t:\neg: %"PRIuMAX "\tmax: %"PRIuMAX "\tmin: %"PRIuMAX "\tsize: %zu\n",
			uintmax, UINTMAX_MAX, (uintmax_t) -42, sizeof(uintmax_t));

	printf("\n");
	// signed ints
	int8_t int8 = -42;
	printf("int8_t:\neg: %"PRId8 "\tmax: %"PRId8 "\tmin: %"PRId8 "\tsize: %zu\n",
			int8, INT8_MAX, INT8_MIN, sizeof(int8_t));

	int16_t int16 = -42;
	printf("int16_t:\neg: %"PRId16 "\tmax: %"PRId16 "\tmin: %"PRId16 "\tsize: %zu\n",
			int16, INT16_MAX, INT16_MIN, sizeof(int16_t));

	int32_t int32 = -42;
	printf("int32_t:\neg: %"PRId32 "\tmax: %"PRId32 "\tmin: %"PRId32 "\tsize: %zu\n",
			int32, INT32_MAX, INT32_MIN, sizeof(int32_t));

	int64_t int64 = -42;
	printf("int64_t:\neg: %"PRId64 "\tmax: %"PRId64 "\tmin: %"PRId64 "\tsize: %zu\n",
			int64, INT64_MAX, INT64_MIN, sizeof(int64_t));

	printf("\n");
	// unsigned ints
	uint8_t uint8 = 42;
	printf("uint8_t:\neg: %"PRIu8 "\tmax: %"PRIu8 "\tmin: %"PRIu8 "\tsize: %zu\n",
			uint8, UINT8_MAX, (uint8_t) 0, sizeof(uint8_t));

	uint16_t uint16 = 42;
	printf("uint16_t:\neg: %"PRIu16 "\tmax: %"PRIu16 "\tmin: %"PRIu16 "\tsize: %zu\n",
			uint16, UINT16_MAX, (uint16_t) 0, sizeof(uint16_t));

	uint32_t uint32 = 42;
	printf("uint32_t:\neg: %"PRIu32 "\tmax: %"PRIu32 "\tmin: %"PRIu32 "\tsize: %zu\n",
			uint32, UINT32_MAX, (uint32_t) 0, sizeof(uint32_t));

	uint64_t uint64 = 42;
	printf("uint64_t:\neg: %"PRIu64 "\tmax: %"PRIu64 "\tmin: %"PRIu64 "\tsize: %zu\n",
			uint64, UINT64_MAX, (uint64_t) 0, sizeof(uint64_t));

	printf("\n");
	// sample least and 
	uint_least32_t uint_least32 = 42;
	printf("uint_least32_t: \neg: %"PRIuLEAST32"\tmax: %"PRIuLEAST32"\tmin: %"PRIuLEAST32"\tsize: %zu\n",
			uint_least32, UINT_LEAST32_MAX, (uint_least32_t) 0, sizeof(uint_least32_t));

	int_fast16_t int_fast16 = -54;
	printf("uint_fast16_t: \neg: %"PRIdFAST16"\tmax: %"PRIdFAST16"\tmin: %"PRIdFAST16"\tsize: %zu\n",
			int_fast16, UINT_FAST16_MAX, (int_fast16_t) 0, sizeof(int_fast16_t));


	/*
	*/
}
