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
        FILE *in = fdopen(fd[0], "r");
        if (!in) { perror("fdopen"); _exit(1); }
        long sum = 0, x;
        while (fscanf(in, "%ld", &x) == 1) sum += x;
        fclose(in);
        printf("sum = %ld\n", sum);
        _exit(0);
    } else {
        close(fd[0]);
        FILE *out = fdopen(fd[1], "w");
        if (!out) { perror("fdopen"); exit(1); }
        for (int i = 1; i <= 10; ++i) fprintf(out, "%d\n", i);
        fclose(out);
        waitpid(pid, NULL, 0);
    }
    return 0;
}
