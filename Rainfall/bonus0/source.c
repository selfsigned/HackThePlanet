#include <stdio.h>

void p(uint dest, uint s)
{
    uchar *puVar1;
    char buffer[4096];
    
    puts(s);
    read(0, &buffer, 4096);
    puVar1 = strchr(&buffer, 10);
    *puVar1 = 0;
    strncpy(dest, &buffer, 20);
    return;
}

char pp(char *dest)
{
  char a[20]; // [esp+28h] [ebp-30h] BYREF
  char b[28]; // [esp+3Ch] [ebp-1Ch] BYREF

  p(a, " - ");
  p(b, " - ");
  strcpy(dest, a);
  *(_WORD *)&dest[strlen(dest)] = unk_80486A4;
  return strcat(dest, b);
}

int main(int argc, const char **argv, const char **envp)
{
  char s[42];

  pp(s);
  puts(s);
  return 0;
}
