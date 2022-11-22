#include <stdio.h>
#include <stdlib.h>

void	run(void)
{
	fwrite("Good... Wait what?\n", 1, 19, stdout);
	system("/bin/sh");
	return;
}

void	main(void)
{
	char buffer[76];

	gets(buffer);
	return;
}
