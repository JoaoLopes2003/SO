#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;

    if ((pid = fork()) == 0) {
        execlp("ls", "ls", "-l", "--color", NULL);
        perror("Erro");
        _exit(1);
    }
    else {
        int status;
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            printf("child %d terminated with exit code %d\n", terminated_pid, code);
        }
        else {
            printf("error\n");
        }
    }

    return 0;
}
