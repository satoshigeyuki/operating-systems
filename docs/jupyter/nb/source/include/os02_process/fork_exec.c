#com 1
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char ** environ;

int main() {
  pid_t pid = fork();           /* 現プロセスをコピー */
  if (pid == -1) {
    err(1, "fork");
  } else if (pid == 0) {        /* 新しいプロセス(子プロセス) */
    char * const argv[] = { "/bin/ls", "-l", 0 };
    execv(argv[0], argv);
    /* 成功すればexecveはリターンしない.
       i.e., リターンしたらエラー */
    err(1, "execve");
  } else {
    int ws;
    pid_t cid = waitpid(pid, &ws, 0);
    if (cid == -1) err(1, "waitpid");
    if (WIFEXITED(ws)) {
      printf("exited, status=%d\n", WEXITSTATUS(ws));
      fflush(stdout);
    } else if (WIFSIGNALED(ws)) {
      printf("killed by signal %d\n", WTERMSIG(ws));
      fflush(stdout);
    }
  }
  return 0;
}
