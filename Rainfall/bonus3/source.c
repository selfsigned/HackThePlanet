#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, const char **argv)
{
	char ptr[132];
	FILE *file_ptr;

	file_ptr = fopen("/home/user/end/.pass", "r");
	memset(ptr, 0, sizeof(ptr));
	if (!file_ptr || argc != 2)
		return -1;
	fread(ptr, 1, 66, file_ptr);
	ptr[65] = 0;
	ptr[atoi(argv[1])] = 0;
	fread(&ptr[66], 1, 65, file_ptr);
	fclose(file_ptr);
	if (strcmp(ptr, argv[1]) == 0)
		execl("/bin/sh", "sh", 0);
	else
		puts(&ptr[66]);
	return (0);
}
