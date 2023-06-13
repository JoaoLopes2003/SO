#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    int pipe_fd[2];

    if (pipe(pipe_fd)<0) {
        perror("Pipe");
        return 1;
    }

    int output_file_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_file_fd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    int stdout_fd = dup(STDOUT_FILENO);
    int stderr_fd = dup(STDERR_FILENO);

    dup2(output_file_fd, STDOUT_FILENO);
    dup2(error_file_fd, STDERR_FILENO);


    pid_t pid;

    if ((pid = fork()) == 0) {

        dup2(pipe_fd[0], STDIN_FILENO);

        close(pipe_fd[0]);
        close(pipe_fd[1]);

        execlp("wc", "wc", NULL);
        perror ("Execlp");
        _exit(1);
    }
    else {
        perror ("Fork");
    }

    close(pipe_fd[0]);

    dup2(stdout_fd, STDOUT_FILENO);
    dup2(stderr_fd, STDERR_FILENO);

    ssize_t bytes;
    char buffer[1024];
    while((bytes = read(STDIN_FILENO, &buffer, 1024))>0) {
        write(pipe_fd[1], &buffer, bytes);
    }

    close(output_file_fd);
    close(error_file_fd);

    char terminei[] = "Terminei\n";
    write(STDOUT_FILENO, &terminei, sizeof(terminei));

    return 0;
}
