#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char nome[] = "fifo";

    fd = open(nome, O_WRONLY);

    if (fd == -1) {
        perror("Failed to open FIFO.");
        return 1;
    }

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}
