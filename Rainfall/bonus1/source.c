#include <stdlib.h>
#include <string.h>

int	main(int argc, const char **argv)
{
	char dest[40];
	int v5;

	v5 = atoi(argv[1]);
	if (v5 > 9)
		return 1;
	memcpy(dest, argv[2], 4 * v5);
	if (v5 == 1464814662)
		execl("/bin/sh", "sh", 0);
	return 0;
}
