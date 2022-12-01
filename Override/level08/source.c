#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

uint64_t  log_wrapper(FILE *a1, const char *a2, const char *a3)
{
	char dest[264];
	uint64_t v6;

	v6 = __readfsqword(40);
	strcpy(dest, a2);
	snprintf(&dest[strlen(dest)], 254 - strlen(dest), a3);
	dest[strcspn(dest, "\n")] = 0;
	fprintf(a1, "LOG: %s\n", dest);
	return (__readfsqword(40) ^ v6);
}

int main(int argc, const char **argv)
{
	FILE *v4;
	FILE *stream;
	int fd;
	char buf;
	char dest[104];
	uint64_t v9;

	v9 = __readfsqword(40);
	buf = -1;
	if (argc != 2)
		printf("Usage: %s filename\n", *argv);
	v4 = fopen("./backups/.log", "w");
	if (!v4)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(v4, "Starting back up: ", argv[1]);
	stream = fopen(argv[1], "r");
	if (!stream)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	strcpy(dest, "./backups/");
	strncat(dest, argv[1], 99 - strlen(dest));
	fd = open(dest, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}
	while (true)
	{
		buf = fgetc(stream);
		if (buf == -1)
			break;
		write(fd, &buf, 1);
	}
	log_wrapper(v4, "Finished back up ", argv[1]);
	fclose(stream);
	close(fd);
	return (0);
}