#include <stdio.h>
#include <stdlib.h>

unsigned int m;

void n(void)
{
	uint s;

	fgets(&s, 0x200, stdin);
	p(&s);
	if (m == 0x1025544) {
		system("/bin/cat /home/user/level5/.pass");
	}
	return;
}

void main(void)
{
	n();
	return;
}
