#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

#define FILENAME "matrix.txt"

int main(int argc, char *argv[]) {

    int numero;
    int fd;
    pid_t pid;
    int status;
    int linhas = 5;
    int colunas = 20;

    char newLine = '\n';

    for (int i = 0;i<linhas;i++) {
        if ((pid = fork()) == 0) {
            srand(time(NULL)+i);

            fd = open(FILENAME, O_CREAT | O_WRONLY, 0600);

            lseek(fd,i*colunas*sizeof(int) + i*sizeof(char),SEEK_CUR);
            
            numero = i * colunas;
            for (int j = 0;j<colunas;j++) {
                numero = (rand() % 100) * 197812;
                printf("%d\n", numero);

                write(fd,&numero,sizeof(int));
            }

            write(fd,&newLine,sizeof(char));

            close(fd);

            _exit(0);
        }
    }

    for (int i = 0;i<linhas;i++) {
        wait(&status);
    }

    // Procurar número

    int procurado = atoi(argv[1]);
    pid_t terminated_pid;

    for (int i = 0;i<linhas;i++) {
        if ((pid = fork()) == 0) {
            fd = open(FILENAME, O_CREAT | O_RDONLY, 0600);

            lseek(fd,i*colunas*sizeof(int) + i*sizeof(char),SEEK_CUR);
            
            for (int j = 0;j<colunas;j++) {
                read(fd,&numero,sizeof(int));

                if (numero==procurado) {
                    printf("Encontrou o número %d na posição %ld do ficheiro\n", procurado, i*colunas*sizeof(int) + j*sizeof(int));

                    close(fd);
                    _exit(1);
                }
            }

            close(fd);
            _exit(0);
        }
    }

    for (int i = 0;i<linhas;i++) {
        wait(&status);

        if (WEXITSTATUS(status)) {
            return 0;
        }
    }

    return 0;
}
