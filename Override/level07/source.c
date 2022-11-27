int clear_stdin()
{
  int result; // eax

  do
    result = getchar();
  while ( (_BYTE)result != 10 && (_BYTE)result != 0xFF );
  return result;
}

//----- (080485E7) --------------------------------------------------------
int get_unum()
{
  int v1[3]; // [esp+1Ch] [ebp-Ch] BYREF

  v1[0] = 0;
  fflush(stdout);
  __isoc99_scanf(&unk_8048AD0, v1);
  clear_stdin();
  return v1[0];
}
// 8048500: using guessed type int __cdecl __isoc99_scanf(_DWORD, _DWORD);
// 80485E7: using guessed type int var_C[3];

//----- (0804861F) --------------------------------------------------------
void __noreturn prog_timeout()
{
  int v0; // eax

  v0 = sys_exit(1);
}
// 804861F: using guessed type void __noreturn prog_timeout();

//----- (08048630) --------------------------------------------------------
int __cdecl store_number(int a1)
{
  unsigned int unum; // [esp+18h] [ebp-10h]
  unsigned int v3; // [esp+1Ch] [ebp-Ch]

  printf(" Number: ");
  unum = get_unum();
  printf(" Index: ");
  v3 = get_unum();
  if ( v3 == 3 * (v3 / 3) || HIBYTE(unum) == 183 )
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  else
  {
    *(_DWORD *)(a1 + 4 * v3) = unum;
    return 0;
  }
}

//----- (080486D7) --------------------------------------------------------
int __cdecl read_number(int a1)
{
  int unum; // [esp+1Ch] [ebp-Ch]

  printf(" Index: ");
  unum = get_unum();
  printf(" Number at data[%u] is %u\n", unum, *(_DWORD *)(a1 + 4 * unum));
  return 0;
}

//----- (08048723) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  _BYTE v6[400]; // [esp+24h] [ebp-1B8h] BYREF
  int number; // [esp+1B4h] [ebp-28h]
  char s[4]; // [esp+1B8h] [ebp-24h] BYREF
  int v9; // [esp+1BCh] [ebp-20h]
  int v10; // [esp+1C0h] [ebp-1Ch]
  int v11; // [esp+1C4h] [ebp-18h]
  int v12; // [esp+1C8h] [ebp-14h]
  unsigned int v13; // [esp+1CCh] [ebp-10h]

  v13 = __readgsdword(0x14u);
  number = 0;
  *(_DWORD *)s = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  memset(v6, 0, sizeof(v6));
  while ( *argv )
  {
    memset((void *)*argv, 0, strlen(*argv));
    ++argv;
  }
  while ( *envp )
  {
    memset((void *)*envp, 0, strlen(*envp));
    ++envp;
  }
  puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");
  while ( 1 )
  {
    printf("Input command: ");
    number = 1;
    fgets(s, 20, stdin);
    s[strlen(s) - 1] = 0;
    if ( !memcmp(s, "store", 5u) )
    {
      number = store_number((int)v6);
      goto LABEL_13;
    }
    if ( !memcmp(s, "read", 4u) )
    {
      number = read_number((int)v6);
      goto LABEL_13;
    }
    if ( !memcmp(s, "quit", 4u) )
      return 0;
LABEL_13:
    if ( number )
      printf(" Failed to do %s command\n", s);
    else
      printf(" Completed %s command successfully\n", s);
    *(_DWORD *)s = 0;
    v9 = 0;
    v10 = 0;
    v11 = 0;
    v12 = 0;
  }
}
