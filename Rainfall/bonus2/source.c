#include <stdio.h>
#include <string.h>

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
	char v4[76];
	char dest[76];
	char *env_lang;

	if (argc != 3)
		return 1;
	memset(dest, 0, sizeof(dest));
	strncpy(dest, argv[1], 40);
	strncpy(&dest[40], argv[2], 32);
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
	memcpy(v4, dest, sizeof(v4));
	return greetuser(v4[0]);
}
