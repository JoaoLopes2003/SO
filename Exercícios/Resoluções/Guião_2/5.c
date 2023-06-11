#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int existeElemento(int **matrix, int linhas, int colunas, int x) {
    pid_t pid;
    int nProc = linhas;
    int status;

    for (int i = 0;i<nProc;i++) {
        if ((pid = fork())==0) {
            int j = 0;

            for (;j<colunas && matrix[i][j]!=x;j++);
            if (matrix[i][j]==x) {
                printf("O filho com identificador de processo %d encontrou o valor %d. na posição (%d,%d)\n", getpid(), x, i, j);
                _exit(1);
            }
            _exit(0);
        }
    }

    for (int i = 0;i<nProc;i++) {
        pid_t terminated_pid = wait(&status);
        if (WEXITSTATUS(status)) {
            return 1;
        }
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    int linhas = 10;
    int colunas = 100;

    int **matrix = (int**) malloc(linhas * sizeof(int *));
    for (int i = 0;i<linhas;i++) {
        matrix[i] = (int*) malloc(colunas * sizeof(int));
    }

    for (int i = 0, h = 0;i<linhas;i++) {
        for (int j = 0;j<colunas;j++,h++) {
            matrix[i][j] = h;
        }
    }

    if (existeElemento(matrix, linhas, colunas, atoi(argv[1]))) {
        printf ("O valor %d foi encontrado\n", atoi(argv[1]));
    }
    else {
        printf ("O valor %d não foi encontrado\n", atoi(argv[1]));
    }

    for (int i = 0;i<linhas;i++) {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}
