#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv)
{
  int input;
  char *exearg[2];
  uid_t uid;
  gid_t gid;

  input = atoi(argv[1]);
  if (input == 423) {
    exearg[0] = strdup("/bin/sh");
    exearg[1] = NULL;
    gid = getegid();
    uid = geteuid();
    setresgid(gid,gid,gid);
    setresuid(uid,uid,uid);
    execv("/bin/sh",exearg);
  } else {
    fwrite("No !\n",1,5,stderr);
  }

  return 0;
}
