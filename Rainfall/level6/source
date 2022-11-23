#include <stdio.h>
#include <stdlib.h>

int m()
{
	return puts("Nope");
}

typedef int (*t_func)();

int n()
{
	return system("/bin/cat /home/user/level7/.pass");
}

int main(int argc, char** argv)
{
	char *dest;
	t_func *func;

	dest = (char *)malloc(64);
	func = (void **)malloc(4);

	*func = m;
	strcpy(dest, argv[1]);
	return (*func)();
}
