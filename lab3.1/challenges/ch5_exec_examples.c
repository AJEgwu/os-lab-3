#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t a = fork();
    if (a < 0) { perror("fork"); exit(1); }
    if (a == 0) {
        execl("/bin/echo", "echo", "one", "two", (char *)NULL);
        perror("execl");
        _exit(1);
    }
    waitpid(a, NULL, 0);

    pid_t b = fork();
    if (b < 0) { perror("fork"); exit(1); }
    if (b == 0) {
        char *const argvv[] = { "echo", "one", "two", NULL };
        execv("/bin/echo", argvv);
        perror("execv");
        _exit(1);
    }
    waitpid(b, NULL, 0);

    return 0;
}
