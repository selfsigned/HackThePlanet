#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv)
{
	char dest[40];
	int val;

	val = atoi(argv[1]);
	if (val > 9)
		return 1;
	memcpy(dest, argv[2], 4 * val);
	if (val == 0x574F4C46) // FLOW
		execl("/bin/sh", "sh", 0);
	return 0;
}
