#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(fd[0]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc");
        _exit(1);
    } else {
        close(fd[0]);
        FILE *out = fdopen(fd[1], "w");
        if (!out) { perror("fdopen"); exit(1); }
        for (int i = 0; i < 5; ++i) fprintf(out, "line %d\n", i);
        fclose(out);
        waitpid(pid, NULL, 0);
    }
    return 0;
}
