#include <stdio.h>
#include <stdlib.h>

unsigned int m;

void n(void)
{
	unsigned int s;

	fgets(&s, 512, stdin);
	p(&s);
	if (m == 16930116) {
		system("/bin/cat /home/user/level5/.pass");
	}
}

int main(void)
{
	n();
	return (0);
}
