#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

int main() {
    char nome[] = "fifo";

    if (mkfifo(nome, 0666) == -1) {
        perror("Failed to create FIFO.");;
        return 1;
    }

    int fd_Leitura = open(nome, O_RDWR);
    if (fd_Leitura == -1) {
        perror("Failed to open FIFO.");
        return 1;
    }

    int fd_Escrita = open("LOG.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
    
    ssize_t bytes;
    char buffer[2048];
    char new_Line = '\n';

    while ((bytes = read(fd_Leitura, &buffer, 2048))>0) {
        write(fd_Escrita, &buffer, bytes);
        write(fd_Escrita, &new_Line, 1);
    }

    return 0;
}
