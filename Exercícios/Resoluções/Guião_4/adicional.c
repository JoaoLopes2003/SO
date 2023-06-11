#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct linha {
    int size_linha;
    int nLinha;
    int offSet;
};

int main(int argc, char *argv[]) {
    char palavra[10] = "Tiago";

    int fd1 = open("ORIGEM.txt", O_RDONLY, 0600);
    int pipe_fd[2];

    if (pipe(pipe_fd)<0) {
        perror("pipe");
        return 1;
    }

    int processos = 1;
    for (int i = 0;i<processos;i++) {
        pid_t pid;

        if ((pid = fork())==0) {
            close (pipe_fd[1]);
            int fd2 = open("ORIGEM.txt", O_RDONLY, 0600);

            struct linha l;
            while (read(pipe_fd[0], &l, sizeof(struct linha))) {
                lseek(fd2, l.offSet-l.size_linha, SEEK_SET);

                char linha[10000];
                read(fd2, &linha, l.size_linha);
                if (strstr(linha, palavra)) {
                    printf ("Encontrou a String na linha %d\n", l.nLinha+1);
                }

                close(fd2);
            }

            close (pipe_fd[0]);
            _exit(0);
        }
    }
    
    close (pipe_fd[0]);

    ssize_t bytes;
    char p;
    struct linha l;
    l.size_linha = 0;
    l.nLinha = 0;
    l.offSet = 0;
    while ((bytes = read(fd1,&p,1))>0) {
        if (p=='\n') {
            l.size_linha++;
            l.offSet++;
            write (pipe_fd[1], &l, sizeof(struct linha));

            l.size_linha = 0;
            l.nLinha++;
        }
        else {
            l.offSet++;
            l.size_linha++;
        }
    }

    close (pipe_fd[1]);
    close(fd1);

    for (int i = 0;i<processos;i++) {
        wait(NULL);
    }

    return 0;
}
