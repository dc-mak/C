#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define INT_CHARS 11
#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
	*out_string  = calloc(1, max_buffer + 1);
	check_mem(*out_string);
	check(max_buffer > 0, "Insuffiient buffer size.");

	//char *result = fgets(*out_string, max_buffer, stdin);
	//check(result != NULL, "Input");
	int i = 0;
	char in = fgetc(stdin);
	for (i = 0; in != '\n' && in != '\0' && i < max_buffer; i++) {
		(*out_string)[i] = in;
		in = fgetc(stdin);
	}
	(*out_string)[i] = '\0';

	return 0;

	error:
	if (*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_int(int *out_int)
{
	char *input = NULL;
	int rc = read_string(&input, MAX_DATA);
	check(rc == 0, "Failed to read number.");

	*out_int = atoi(input);

	free(input);
	return 0;
error:
	if (input) free(input);
	return -1;
}

void itoa(char *out_string, int max_buffer, int n)
{
	char const digits[] = "0123456789";
	out_string[max_buffer-1] = '\0';
	char *pos = out_string;
	int i = 0;
	int shifter = n;

	if (n < 0) *pos++ = '-';

	do {
		++i;
		++pos;
		shifter /= 10;
	} while (shifter != 0 && i < max_buffer);
	*pos = '\0';

	i = n < 0 ? -1 : 1;
	do {
		*--pos = digits[i * (n % 10)];
		n /= 10;
	} while (n != 0);
}

int write_out(const char *fmt, ...)
{
	va_list argp;
	int max_buffer;
	char int_string[INT_CHARS+1];
	char *out_string;
	va_start(argp, fmt);

	for (int i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch(fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;
				
				case 'd':
					// 32 bit int <= 10 char + "-" + "\0"
					itoa(int_string, INT_CHARS+1, va_arg(argp, int));
					for (int i = 0; int_string[i] != '\0'
							&& i < INT_CHARS+1; i++)
						putchar(int_string[i]);
					break;

				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char *);
					for (int i = 0; out_string[i] != '\0'
							&& i < max_buffer; i++)
						putchar(out_string[i]);
					break;

				case 'c':
					putchar(va_arg(argp, int));
					break;

				case '\\':
					if (fmt[i+1] == '\n') {
						i++;
						putchar('\n');
					}

				default:
					sentinel("Invalid format");
			}
		} else {
			putchar(fmt[i]);
		}
	}
	va_end(argp);
	return 0;
error:
	return -1;
}


// putchar
// int has at most 12 char (including - sign and '\0' terminator)

int read_scan(const char *fmt, ...)
{
	int rc = 0;
	int *out_int = NULL;
	char *out_char = NULL;
	char **out_string = NULL;
	int max_buffer = 0;

	va_list argp;
	va_start(argp, fmt);

	for (int i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch (fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

				case 'd':
					out_int = va_arg(argp, int *);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;

				case 'c':
					out_char = va_arg(argp, char *);
					*out_char = fgetc(stdin);
					break;

				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char**);
					rc = read_string(out_string, max_buffer);
					check(rc == 0, "Failed to read string.");
					break;

				default:
					sentinel("Invalid format.");
			}
		} else {
			fgetc(stdin);
		}
		check(!feof(stdin) && !ferror(stdin), "Input error.");
	}

	va_end(argp);
	return 0;

error:
	va_end(argp);
	return -1;
}

int main(int argc, char *argv[])
{
	char *first_name = NULL;
	char initial = ' ';
	char *last_name = NULL;
	int age = 0;

	printf("What's your first name? ");
	int rc = read_scan("%s", MAX_DATA, &first_name);
	check(rc == 0, "Failed first name.");

	printf("What's your initial? ");
	rc = read_scan("%c\n", &initial);
	check(rc == 0, "Failed initial.");

	// if you forget MAX_DATA is just loops
	printf("What's your last name? ");
	rc = read_scan("%s", MAX_DATA, &last_name);
	check(rc == 0, "Failed last name.");

	printf("How old are you? ");
	rc = read_scan("%d", &age);

	printf("---- RESULT ----\n");
	write_out("First Name: %s\n", strlen(first_name), first_name);
	write_out("Initial: '%c'\n", initial);
	write_out("Last Name: %s\n", strlen(last_name), last_name);
	write_out("Age: %d\n", age);

	free(first_name);
	free(last_name);
	return 0;

error:
	return -1;
}
