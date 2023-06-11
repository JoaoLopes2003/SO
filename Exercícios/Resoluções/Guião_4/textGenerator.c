#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int size = atoi(argv[1]);

    int fd = open("ORIGEM.txt", O_WRONLY | O_CREAT, 0600);

    srand(time(NULL));

    char mudar_linha = '\n';
    for (int i = 0;i<size;i++) {
        int num = rand() % 97;
        char caracter = 48 + num;

        write (fd, &caracter, 1);

        int enter = rand() % 100;
        if (enter==1) {
            i++;
            write (fd, &mudar_linha, 1);
        }
    }

    return 0;
}
