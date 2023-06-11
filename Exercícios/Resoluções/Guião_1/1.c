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
    char buffer[2048];

    while ((bytes = read(fd1, &buffer, 2048))>0) {
        write(fd2, &buffer, bytes);
    }

    close(fd1);
    close(fd2);

    return 0;
}
