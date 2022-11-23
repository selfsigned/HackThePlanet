#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	*auth;
int	service;

int	main()
{
	char s[5];
	char v5[2];
	char v6[129];

	while (1)
	{
		printf("%p, %p \n", auth, (void *)service);
		if (!fgets(s, 128, stdin))
			break;
		if (memcmp(s, "auth ", 5) == 0)
		{
			auth = malloc(4);
			auth[0] = 0;
			if (strlen(v5) <= 30)
				strcpy(auth, v5);
		}
		if (memcmp(s, "reset", 5) == 0)
			free(auth);
		if (memcmp(s, "service", 6) == 0)
			service = (int)strdup(v6);
		if (memcmp(s, "login", 5) == 0)
		{
			if (auth[8])
				system("/bin/sh");
			else
				fwrite("Password:\n", 1, 10, stdout);
		}
	}
	return (0);
}
