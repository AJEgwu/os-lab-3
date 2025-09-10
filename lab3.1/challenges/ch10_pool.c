#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s M task1 task2 ...\n", argv[0]);
        return 1;
    }
    int M = atoi(argv[1]);
    if (M <= 0) {
        fprintf(stderr, "M must be > 0\n");
        return 1;
    }

    int next = 2;
    int running = 0;
    int total = argc - 2;

    while (next < argc || running > 0) {
        while (running < M && next < argc) {
            pid_t pid = fork();
            if (pid < 0) { perror("fork"); return 1; }
            if (pid == 0) {
                printf("[worker %d] start %s\n", getpid(), argv[next]);
                sleep(1);
                printf("[worker %d] done %s\n", getpid(), argv[next]);
                _exit(0);
            } else {
                running++;
                next++;
            }
        }
        int status;
        pid_t w = waitpid(-1, &status, 0);
        if (w == -1) { perror("waitpid"); return 1; }
        running--;
    }

    printf("Processed %d tasks with concurrency %d\n", total, M);
    return 0;
}
