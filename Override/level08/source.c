#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void	log_wrapper(FILE *stream, const char *message, const char *argv1)
{
	char dest[264];

	strcpy(dest, message);
	snprintf(dest, 254 - strlen(dest), argv1);
	dest[strcspn(dest, "\n")] = 0;
	fprintf(stream, "LOG: %s\n", dest);
	return ;
}

int main(int argc, const char **argv)
{
	FILE *backup_log;
	FILE *argv_stream;
	int fd;
	char buf;
	char dest[104];

	buf = -1;
	if (argc != 2)
		printf("Usage: %s filename\n", *argv);
	backup_log = fopen("./backups/.log", "w");
	if (!backup_log)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(backup_log, "Starting back up: ", argv[1]);
	argv_stream = fopen(argv[1], "r");
	if (!argv_stream)
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
		buf = fgetc(argv_stream);
		if (buf == -1)
			break;
		write(fd, &buf, 1);
	}
	log_wrapper(backup_log, "Finished back up ", argv[1]);
	fclose(argv_stream);
	close(fd);
	return (0);
}