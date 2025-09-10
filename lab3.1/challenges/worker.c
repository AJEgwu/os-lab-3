#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("worker:");
    for (int i = 0; i < argc; ++i) printf(" %s", argv[i]);
    const char *mv = getenv("MYVAR");
    if (mv) printf("  MYVAR=%s", mv);
    printf("\n");
    return 0;
}
