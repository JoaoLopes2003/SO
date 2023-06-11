#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc<2) return 0;

    char **args = malloc(200*sizeof(char*));

    int i = 0;
    do {
        args[i] = strsep(&argv[1], " ");
        i++;
    } while (args[i-1]);

    pid_t pid;

    if ((pid = fork()) == 0) {
        execvp(args[0], args);
        perror("Erro");
        _exit(1);
    }

    int status;
    pid_t terminated_pid = wait(&status);

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        printf("child %d terminated with exit code %d\n", terminated_pid, code);
    }
    else {
        printf("error\n");
    }

    return 0;
}
