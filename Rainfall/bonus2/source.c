#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language;

int greetuser(char src)
{
	char	dest[20];

	switch (language)
	{
	case 1:
		strcpy(dest, "Hyvää päivää ");
		break;
	case 2:
		strcpy(dest, "Goedemiddag! ");
		break;
	case 0:
		strcpy(dest, "Hello ");
		break;
	}
	strcat(dest, &src);
	return puts(dest);
}

int main(int argc, const char **argv)
{
	char str1[76];
	char str2[76];
	char *env_lang;

	if (argc != 3)
		return 1;
	memset(str2, 0, sizeof(str2));
	strncpy(str2, argv[1], 40);
	strncpy(&str2[40], argv[2], 32);
	env_lang = getenv("LANG");
	if (env_lang)
	{
		if (memcmp(env_lang, "fi", 2) == 0)
		{
			language = 1;
		}
		else if (memcmp(env_lang, "nl", 2) == 0)
		{
			language = 2;
		}
	}
	memcpy(str1, str2, sizeof(str1));
	return greetuser(str1[0]);
}
