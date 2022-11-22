#include <stdio.h>
#include <string.h>

int language;

int greetuser(char src)
{
  __int128 dest; // [esp+10h] [ebp-48h] BYREF
  __int16 v3; // [esp+20h] [ebp-38h]
  char v4; // [esp+22h] [ebp-36h]

  switch ( language )
  {
    case 1:
//      dest = xmmword_8048717;
//      v3 = *((_WORD *)&xmmword_8048717 + 8);
//      v4 = *((_BYTE *)&xmmword_8048717 + 18);
      strcpy((char *)&dest, U"Hyvää päivää ");
      break;
    case 2:
      strcpy((char *)&dest, "Goedemiddag! ");
      break;
    case 0:
      strcpy((char *)&dest, "Hello ");
      break;
  }
  strcat((char *)&dest, &src);
  return puts((const char *)&dest);
}
int main(int argc, const char **argv)
{
  char v4[76]; // [esp+0h] [ebp-ACh] BYREF
  char dest[76]; // [esp+50h] [ebp-5Ch] BYREF
  char *env_lang; // [esp+9Ch] [ebp-10h]

  if ( argc != 3 )
    return 1;
  memset(dest, 0, sizeof(dest));
  strncpy(dest, argv[1], 40);
  strncpy(&dest[40], argv[2], 32);
  env_lang = getenv("LANG");
  if ( env_lang )
  {
    if ( !memcmp(env_lang, "fi", 2) )
    {
      language = 1;
    }
    else if ( !memcmp(env_lang, "nl", 2) )
    {
      language = 2;
    }
  }
  memcmp(v4, dest, sizeof(v4));
  return greetuser(v4[0]);
}
