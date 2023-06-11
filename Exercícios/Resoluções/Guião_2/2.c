#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;

    if ((pid = fork()) == 0) {
        printf("[filho] pid próprio = %d\n", getpid());
        printf("[filho] pid pai = %d\n", getppid());
        printf("[filho] pid = %d\n", pid);
    }
    else {
        printf("[pai] pid próprio = %d\n", getpid());
        printf("[pai] pid pai = %d\n", getppid());
        printf("[pai] pid filho = %d\n", pid);
    }

    return 0;
}
