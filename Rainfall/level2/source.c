#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void p(void)
{
	unsigned int ret;
	char src[76];

	fflush(stdout);
	gets(src);
	ret = __builtin_return_address(0);
	if ((ret & 0xb0000000) == 0xb0000000) {
		printf("(%p)\n", ret);
		exit(1);
	}
	puts(src);
	strdup(src);
}

int main(void)
{
	p();
	return (0);
}
