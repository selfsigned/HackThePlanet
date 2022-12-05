#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int decrypt(char input)
{
	unsigned int i;
	unsigned int length;
	char dictionary[29];

	strcpy(dictionary, "Q}|u`sfg~sf{}|a3");
	length = strlen(dictionary);
	for (i = 0; i < length; ++i)
		dictionary[i] ^= input;
	if (!strcmp(dictionary, "Congratulations!"))
		return (system("/bin/sh"));
	else
		return (puts("\nInvalid Password"));
}

int test(int a1, int a2)
{
	int result;
	char input;

	switch (a2 - a1)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			result = decrypt(a2 - a1);
			break;
		default:
			input = rand();
			result = decrypt(input);
			break;
	}
	return (result);
}

int main()
{
	unsigned int seed;
	int savedregs;

	seed = time(0);
	srand(seed);
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &savedregs);
	test(savedregs, 322424845); // 322424845 == 0x1337d00d
	return (0);
}
