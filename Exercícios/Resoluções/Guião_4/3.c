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

        int i = 10;
        write (pipe_fd[1], &i, sizeof(int));
        printf("%d\n", i);

        _exit(0);
    }

    close(pipe_fd[1]);

    int i;
    read (pipe_fd[0],&i,sizeof(int));
    printf("%d\n", i);

    wait(NULL);

    return 0;
}
