#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char	*c;

void m()
{
	time_t tVar1;

	tVar1 = time((time_t *)0);
	printf("%s - %d\n", c, tVar1);
	return;
}

int main(int argc,char** argv)
{
	void **a;
	void **b;
	FILE *password;

	a = malloc(8);
	a[0] = 1;
	a[1] = malloc(8);

	b = malloc(8);
	b[0] = 2;
	b[1] = malloc(8);

	strcpy((char *)a[1], argv[1]);
	strcpy((char *)b[1], argv[2]);
	password = fopen("/home/user/level8/.pass", "r");
	fgets(c, 68, password);
	puts("~~");
	return (0);
}
