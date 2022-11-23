#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv) {
	int a = atoi(argv[1]);

	fprintf(stdout, "a = %d, 4 * a = %d\n", a, 4 * a);
	return (0);
}