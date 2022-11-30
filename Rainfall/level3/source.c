#include <stdlib.h>
#include <stdio.h>

unsigned int m;

void v(void)
{
	char buffer[520];

	fgets(buffer, 512, stdin);
	printf(buffer);
	if (m == 64) {
		fwrite("Wait what?!\n", 1, 12, stdout);
		system("/bin/sh");
	}
}

int main(void)
{
	v();
	return (0);
}
