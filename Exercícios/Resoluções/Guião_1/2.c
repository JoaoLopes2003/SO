#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main() {
    int fd1 = 0;
    int fd2 = 1;

    ssize_t bytes;
    char buffer[1024];

    while ((bytes = read(fd1, &buffer, 10))>0) {
        write(fd2, &buffer, bytes);
    }

    return 0;
}
