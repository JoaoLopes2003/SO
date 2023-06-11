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
        perror("Faileld to create FIFO.");;
        return 1;
    }

    return 0;
}
