#include <unistd.h>
#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
  char input_password[96]; // [rsp+10h] [rbp-110h] BYREF
  int v5; // [rsp+70h] [rbp-B0h]
  char password[48]; // [rsp+80h] [rbp-A0h] BYREF
  char input_username[96]; // [rsp+B0h] [rbp-70h] BYREF
  int v8; // [rsp+110h] [rbp-10h]
  int v9; // [rsp+114h] [rbp-Ch]
  FILE *stream; // [rsp+118h] [rbp-8h]

  bzero(input_username, sizeof(input_username));
  v8 = 0;
  bzero(password, 41);
  bzero(input_password, sizeof(input_password));
  v5 = 0;
  stream = 0LL;
  v9 = 0;
  stream = fopen("/home/users/level03/.pass", "r");
  if ( !stream )
  {
    fwrite("ERROR: failed to open password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  v9 = fread(password, 1uLL, 0x29uLL, stream);
  password[strcspn(password, "\n")] = 0;
  if ( v9 != 41 )
  {
    fwrite("ERROR: failed to read password file\n", 1uLL, 0x24uLL, stderr);
    fwrite("ERROR: failed to read password file\n", 1uLL, 0x24uLL, stderr);
    exit(1);
  }
  fclose(stream);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets(input_username, 100, stdin);
  input_username[strcspn(input_username, "\n")] = 0;
  printf("--[ Password: ");
  fgets(input_password, 100, stdin);
  input_password[strcspn(input_password, "\n")] = 0;
  puts("*****************************************");
  if ( strncmp(password, input_password, 0x29uLL) )
  {
    printf(input_username);
    puts(" does not have access!");
    exit(1);
  }
  printf("Greetings, %input_username!\n", input_username);
  system("/bin/sh");
  return 0;
}
