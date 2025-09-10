#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

static void msleep(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

int main(void) {
    int sleeps[] = {1,2,3};

    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();
        if (pid < 0) { perror("fork"); exit(1); }
        if (pid == 0) {
            sleep(sleeps[i]);
            _exit(10 + i);
        }
    }

    int done = 0;
    while (done < 3) {
        int status;
        pid_t w = waitpid(-1, &status, WNOHANG);
        if (w == 0) {
            msleep(100);
            continue;
        } else if (w > 0) {
            if (WIFEXITED(status)) {
                printf("child %d finished status=%d\n", w, WEXITSTATUS(status));
            } else {
                printf("child %d finished abnormally\n", w);
            }
            done++;
        } else {
            perror("waitpid");
            exit(1);
        }
    }
    return 0;
}
