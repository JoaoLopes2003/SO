#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    printf("pid próprio = %d\n", getpid());
    printf("pid pai = %d\n", getppid());

    return 0;
}
