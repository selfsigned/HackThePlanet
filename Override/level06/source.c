#include <stdio.h>
#include <sys/ptrace.h>
#include <string.h>
#include <stdlib.h>

int auth(char *serial, int input_number)
{
	int i;
	int computed_value;
	int s_len;

	serial[strcspn(serial, "\n")] = 0;
	s_len = strnlen(serial, 32);
	if (s_len <= 5)
		return 1;
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		puts("\x1B[32m.---------------------------.");
		puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1B[32m'---------------------------'");
		return (1);
	}
	else {
		computed_value = (serial[3] ^ 0x1337) + 6221293;
		for (i = 0; i < s_len; ++i) {
			if (serial[i] <= 31)
				return (1);
			computed_value += (computed_value ^ (unsigned int)serial[i]) % 1337;
		}
		return input_number != computed_value;
	}
}

int main(int argc, const char **argv, const char **envp)
{
	int input_number;
	char serial[32];

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(serial, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &input_number);
	if (auth(serial, input_number))
		return (1);
	puts("Authenticated!");
	system("/bin/sh");
	return (0);
}
