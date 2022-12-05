#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char input_password[100];
	char password[41];
	char input_username[100];
	int char_written = 0;
	FILE *stream = NULL;

	bzero(input_username, sizeof(input_username));
	bzero(password, 41);
	bzero(input_password, sizeof(input_password));
	stream = fopen("/home/users/level03/.pass", "r");
	if (!stream)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	char_written = fread(password, 1, 41, stream);
	password[strcspn(password, "\n")] = 0;
	if (char_written != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	fclose(stream);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(input_username, 100, stdin);
	input_username[strcspn(input_username, "\n")] = 0;
	printf("--[ Password: ");
	fgets(input_password, 100, stdin);
	input_password[strcspn(input_password, "\n")] = 0;
	puts("*****************************************");
	if (strncmp(password, input_password, 41))
	{
		printf(input_username);
		puts(" does not have access!");
		exit(1);
	}
	printf("Greetings, %input_username!\n", input_username);
	system("/bin/sh");
	return (0);
}
