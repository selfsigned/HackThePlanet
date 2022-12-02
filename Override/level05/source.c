#include <stdio.h>

int main()
{
	char s[100];
	unsigned int i = 0;

	fgets(s, 100, stdin);
	for (i = 0; i < strlen(s); ++i)
	{
		if (s[i] >= "A" && s[i] <= "Z")
			s[i] ^= 32;
	}
	printf(s);
	exit(0);
}
