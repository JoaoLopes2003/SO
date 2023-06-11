#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

int main() {
    int fd;
    char nome[] = "fifo";

    fd = open(nome, O_WRONLY);

    if (fd == -1) {
        perror("Failed to open FIFO.");
        return 1;
    }

    ssize_t bytes;
    char buffer[2048];

    while ((bytes = read(0, &buffer, 2048))>0) {
        write(fd, &buffer, bytes);
    }

    close(fd);

    return 0;
}
