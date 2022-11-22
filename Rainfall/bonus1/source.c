#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv)
{
	char dest[40]; // [esp+14h] [ebp-2Ch] BYREF
	int val; // [esp+3Ch] [ebp-4h]

	val = atoi(argv[1]);
	if ( val > 9 )
		return 1;
	memcpy(dest, argv[2], 4 * val);
	if ( val == 1464814662 )
		execl("/bin/sh", "sh", 0);
	return 0;
}
