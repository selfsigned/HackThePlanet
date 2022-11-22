#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, const char **argv)
{
	char ptr[132];
	FILE *v5;

	v5 = fopen("/home/user/end/.pass", "r");
	memset(ptr, 0, sizeof(ptr));
	if (!v5 || argc != 2)
		return -1;
	fread(ptr, 1u, 66, v5);
	ptr[65] = 0;
	ptr[atoi(argv[1])] = 0;
	fread(&ptr[66], 1u, 65, v5);
	fclose(v5);
	if (strcmp(ptr, argv[1]) == 0)
		execl("/bin/sh", "sh", 0);
	else
		puts(&ptr[66]);
	return (0);
}
