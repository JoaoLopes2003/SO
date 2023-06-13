#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int input_file_fd = open("/etc/passwd", O_RDONLY);
    int output_file_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_file_fd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    int stdout_fd = dup(STDOUT_FILENO);
    int stdin_fd = dup(STDIN_FILENO);
    int stderr_fd = dup(STDERR_FILENO);

    dup2(input_file_fd, STDIN_FILENO);
    dup2(output_file_fd, STDOUT_FILENO);
    dup2(error_file_fd, STDERR_FILENO);


    pid_t pid;

    if ((pid = fork()) == 0) {
        ssize_t bytes;
        char buffer[1024];
        while((bytes = read(STDIN_FILENO, &buffer, 1024))>0) {
            write(STDOUT_FILENO, &buffer, bytes);
        }
        _exit(1);
    }
    else {
        perror ("Fork");
    }

    dup2(stdin_fd, STDIN_FILENO);
    dup2(stdout_fd, STDOUT_FILENO);
    dup2(stderr_fd, STDERR_FILENO);

    close(input_file_fd);
    close(output_file_fd);
    close(error_file_fd);

    char terminei[] = "Terminei\n";
    write(STDOUT_FILENO, &terminei, sizeof(terminei));

    return 0;
}
