#include <stdio.h>
#include <strings.h>
#include <unistd.h>

void p(char *dest, char *s)
{
	char *terminator;
	char buffer[4096];

	puts(s);
	read(0, buffer, 4096);
	terminator = strchr((const char*)buffer, '\n');
	*terminator = '\0';
	strncpy(dest, buffer, 20);
	return;
}

char *pp(char *dest)
{
	char a[20];
	char b[20];
	size_t len;

	p(b, " - ");
	strcpy(dest, a);
	len = strlen(dest);
	dest[len] = ' ';
	return strcat(dest, b);
}

int main()
{
	char s[42];

	pp(s);
	puts(s);
	return 0;
}
