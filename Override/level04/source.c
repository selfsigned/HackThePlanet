#include <sys/ptrace.h>
#include <sys/wait.h>

int main()
{
	int stat_loc = 0;
	char s[128];
	int v6;
	int v7;
	int v8 = 0;
	pid_t v9;

	v9 = fork();
	memset(s, 0, sizeof(s));
	if (v9)
	{
		do {
			wait(&stat_loc);
			v6 = stat_loc;
			if ((stat_loc & 127) == 0 || (v7 = stat_loc, (char)((stat_loc & 127) + 1) >> 1 > 0))
			{
				puts("child is exiting...");
				return (0);
			}
			v8 = ptrace(PTRACE_PEEKUSER, v9, 44, 0);
		} while (v8 != 11);
	puts("no exec() for you");
	kill(v9, 9);
	}
	else
	{
		prctl(1, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(s);
	}
	return (0);
}
