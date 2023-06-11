#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int encontraMatriz (int x, int **matriz, int colunas, int linhas, int *resultados) {
    int pipe_fd[2];

    if (pipe(pipe_fd)<0) {
        perror("pipe");
        return 1;
    }

    for (int i = 0;i<linhas;i++) {
        pid_t pid;

        int encontrado = 0;
        if ((pid = fork())==0) {
            close (pipe_fd[0]);

            for (int j = 0;j<colunas && !encontrado;j++) {
                if (matriz[i][j]==x) {
                    encontrado++;
                    write(pipe_fd[1],&i,sizeof(int));

                    close (pipe_fd[1]);
                    _exit(0);
                }
            }

            close (pipe_fd[1]);
            _exit(0);
        }
    }

    close (pipe_fd[1]);

    int count = 0;

    while (read(pipe_fd[0],&resultados[count],sizeof(int))) {
        count++;
    }

    close (pipe_fd[0]);

    return count;
}

int main(int argc, char *argv[]) {

    /*
        Cria a matriz de valores aleatŕios entre 0 e 99
    */

    srand(time(NULL));

    int linhas = 10;
    int colunas = 10000000;

    int **matriz = (int**) malloc(linhas * sizeof(int *));
    for (int i = 0;i<linhas;i++) {
        matriz[i] = (int*) malloc(colunas * sizeof(int));
    }

    for (int i = 0;i<linhas;i++) {
        for (int j = 0;j<colunas;j++) {
            matriz[i][j] = rand() % 10000000;
        }
    }

    /*
        Encontra as linhas onde o elemento existe
    */

    int elementoEncontrar = 10;
    int *resultados = malloc (sizeof(int)*linhas);

    int encontrados = encontraMatriz (elementoEncontrar, matriz, colunas, linhas, resultados);

    for (int i = 0;i<encontrados;i++) {
        printf ("Foi encontrado o elemento %d, na linha %d.\n", elementoEncontrar, resultados[i]);
    }

    for (int i = 0;i<linhas;i++) {
        free (matriz[i]);
    }

    free (matriz);

    return 0;
}
