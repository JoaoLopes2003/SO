#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc<2) return 0;

    pid_t pid;

    for (int i = 1;i<=argc;i++) {
        if ((pid = fork()) == 0) {
            execlp(argv[i], argv[i], NULL);
            perror("Erro");
            _exit(1);
        }
    }

    for (int i = 0;i<argc-1;i++) {
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
