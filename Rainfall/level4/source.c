#include <stdio.h>
#include <stdlib.h>

unsigned int m;

int p(char *format)
{
	return (printf(format));
}

void n(void)
{
	char s[520];

	fgets(s, 512, stdin);
	p(s);
	if (m == 16930116) {
		system("/bin/cat /home/user/level5/.pass");
	}
}

int main(void)
{
	n();
	return (0);
}
