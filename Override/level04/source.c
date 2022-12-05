#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int stat_loc = 0;
	char s[128];
	int orig_eax = 0;
	pid_t child;

	child = fork();
	memset(s, 0, sizeof(s));
	if (child)
	{
		/* Parent process */
		do {
			wait(&stat_loc);
			if (WTERMSIG(stat_loc) == 0 || WIFSIGNALED(stat_loc))
			{
				puts("child is exiting...");
				return (0);
			}
			orig_eax = ptrace(PTRACE_PEEKUSER, child, (ORIG_EAX*4), 0); // system call in child detection
		} while (orig_eax != 11);
		puts("no exec() for you");
		kill(child, 9);
	}
	else
	{
		/* Child process */
		prctl(1, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(s);
	}
	return (0);
}
