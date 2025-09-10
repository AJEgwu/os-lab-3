#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s N\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    if (N <= 0 || N > 50) {
        fprintf(stderr, "N must be 1..50\n");
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        pid_t pid = fork();
        if (pid < 0) { perror("fork"); return 1; }
        if (pid == 0) {
            printf("[child %d] index=%d\n", getpid(), i);
            _exit((i + 1) & 0xFF);
        }
    }

    int finished = 0;
    while (finished < N) {
        int status;
        pid_t w = waitpid(-1, &status, 0);
        if (w == -1) { perror("waitpid"); return 1; }
        if (WIFEXITED(status)) {
            printf("[parent] child %d finished, status=%d\n", w, WEXITSTATUS(status));
        } else {
            printf("[parent] child %d finished abnormally\n", w);
        }
        finished++;
    }
    return 0;
}
