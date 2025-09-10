#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        _exit(0);
    } else {
        printf("Child %d exited; parent sleeping 10s. Check ps -l in another terminal.\n", pid);
        sleep(10);
        waitpid(pid, NULL, 0);
        printf("wait() done.\n");
    }
    return 0;
}
