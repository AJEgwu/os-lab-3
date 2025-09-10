#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    const char *pattern = (argc > 1) ? argv[1] : "c";

    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    pid_t c1 = fork();
    if (c1 < 0) { perror("fork"); exit(1); }

    if (c1 == 0) {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(fd[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    pid_t c2 = fork();
    if (c2 < 0) { perror("fork"); exit(1); }

    if (c2 == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(fd[0]);
        execlp("grep", "grep", pattern, (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;
}
