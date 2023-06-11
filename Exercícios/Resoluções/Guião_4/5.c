#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int pipe_fd[2];

    if (pipe(pipe_fd)<0) {
        perror("pipe");
        return 1;
    }

    pid_t pid;

    if ((pid = fork())==0) {
        close (pipe_fd[0]);

        for (int i = 0;i<100000;i++) {
            write (pipe_fd[1], &i, sizeof(int));
            printf("%d\n", i);
        }

        close (pipe_fd[1]);

        _exit(0);
    }

    close(pipe_fd[1]);

    int i;
    while (read (pipe_fd[0],&i,sizeof(int))) {
        printf("%d\n", i);
    }

    close (pipe_fd[0]);

    return 0;
}
