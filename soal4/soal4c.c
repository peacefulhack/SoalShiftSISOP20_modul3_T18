#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main() {
  int p1[2];
  pid_t child;

  pipe(p1);


  if ((child=fork()) == 0) {
    dup2(p1[1], 1);
    close(p1[0]);
    char *argv[] = {"ls", NULL};
    execv("/bin/ls", argv);
  }
  else{
  child=wait(NULL);
  dup2(p1[0], 0);
  close(p1[1]);
  char *argv[] = {"wc", "-l", NULL};
  execv("/usr/bin/wc", argv);
  }
}
