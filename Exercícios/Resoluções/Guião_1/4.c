#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main () {
    int fd1 = 0;
    int fd2 = open("DESTINO.txt", O_CREAT | O_WRONLY, 0600);

    ssize_t bytes;
    long counter = 0;
    char caracter;
    char buffer[1024];
    int linha = 1;

    while ((bytes = read(fd1, &caracter, 1))>0) {
        buffer[counter] = caracter;
        counter++;
        if (caracter=='\n') {
            

            write(fd2, &buffer, counter);

            counter = 0;
        }
    }

    close(fd2);

    return 0;
}
