#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main() {
    int fd1 = open("ORIGEM.txt", O_RDONLY, 0600);
    int fd2 = open("DESTINO.txt", O_CREAT | O_WRONLY, 0600);

    ssize_t bytes;
    long counter = 0;
    char caracter;

    while ((bytes = read(fd1, &caracter, 1))>0 && caracter!='\n') counter++;

    if (caracter=='\n') counter++;

    char buffer[counter];

    lseek(fd1, 0, SEEK_SET);
    read(fd1, &buffer, counter);
    write(fd2, &buffer, counter);

    close(fd1);
    close(fd2);

    return 0;
}
