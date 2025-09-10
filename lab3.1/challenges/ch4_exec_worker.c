#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) {
        char *const args[] = { "./bin/worker", "arg1", "arg2", NULL };
        char *const envp[] = { "MYVAR=hello", NULL };
        execve("./bin/worker", args, envp);
        perror("execve");
        _exit(1);
    } else {
        waitpid(pid, NULL, 0);
        printf("[parent] worker finished\n");
    }
    return 0;
}
