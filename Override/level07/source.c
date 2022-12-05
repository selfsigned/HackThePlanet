#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define LOWORD(l) ((uint16_t)(l))
#define HIWORD(l) ((uint16_t)(((uint32_t)(l) >> 16) & 0xFFFF))
#define LOBYTE(w) ((uint8_t)(w))
#define HIBYTE(w) ((uint8_t)(((uint16_t)(w) >> 8) & 0xFF))


int clear_stdin()
{
	int result;

	do {
		result = getchar();
	} while (result != 10 && result != -1);

	return result;
}

unsigned int get_unum()
{
	unsigned int unum;

	fflush(stdout);
	scanf("%u", &unum);
	clear_stdin();
	return unum; 
}

int store_number(int *data)
{
	unsigned int unum;
	unsigned int index;

	printf(" Number: ");
	unum = get_unum();
	printf(" Index: ");
	index = get_unum();
	if ((index % 3 == 0) || HIBYTE(unum) == 183)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	else
	{
		data[index] = unum;
		return (0);
	}
}

int read_number(int *data)
{
	unsigned int unum;

	printf(" Index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, data[unum]);
	return 0;
}

int main(int argc, const char **argv, const char **envp)
{
	int storage[100];
	int number;
	char input[20];

	number = 0;
	memset(input, 0, sizeof(input));
	memset(storage, 0, sizeof(storage));
	while (*argv)
	{
		memset((void *)*argv, 0, strlen(*argv));
		++argv;
	}
	while (*envp)
	{
		memset((void *)*envp, 0, strlen(*envp));
		++envp;
	}
	puts(
		"----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                          \n"
		"    store - store a number into the data storage    \n"
		"    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n"
		"----------------------------------------------------\n"
	);
	while (1)
	{
		printf("Input command: ");
		number = 1;
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = 0;
		if (!memcmp(input, "store", 5))
		{
			number = store_number(storage);
		}
		if (!memcmp(input, "read", 4))
		{
			number = read_number(storage);
		}
		if (!memcmp(input, "quit", 4))
			return (0);

		if (number)
			printf(" Failed to do %s command\n", input);
		else
			printf(" Completed %s command successfully\n", input);
		memset(input, 0, sizeof(input));
	}
}
