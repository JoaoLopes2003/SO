#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int medianOfThree(int arr[], int left, int right) {
    int mid = (left + right) / 2;

    if (arr[left]>arr[mid]) {
        swap(&arr[left],&arr[mid]);
    }
    if (arr[mid]>arr[right]) {
        swap(&arr[right],&arr[mid]);
    }
    if (arr[left]>arr[mid]) {
        swap(&arr[left],&arr[mid]);
    }

    return mid;
}

int partition(int arr[], int left, int right) {
    int pivotIndex = medianOfThree(arr, left, right);
    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex],&arr[right]);
    int storeIndex = left;

    for (int i = left;i<right;i++) {
        if (arr[i]<pivotValue) {
            swap(&arr[i],&arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(&arr[storeIndex],&arr[right]);

    return storeIndex;
}

void quickSort(int arr[], int left, int right) {
    if (left<right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex-1);
        quickSort(arr, pivotIndex+1, right);
    }
}

int existeElemento(int **matrix, int linhas, int colunas, int x) {
    pid_t pid;
    int nProc = linhas;
    int status;
    int posLinhasPresente = 0;
    int linhasPresente[linhas];

    for (int i = 0;i<linhas;i++) {
        linhasPresente[i] = -1;
    }

    for (int i = 0;i<nProc;i++) {
        if ((pid = fork())==0) {
            int j = 0;

            for (;j<colunas && matrix[i][j]!=x;j++);
            if (matrix[i][j]==x) {
                printf("O filho com identificador de processo %d encontrou o valor %d. na posição (%d,%d)\n", getpid(), x, i, j);
                _exit(i+1);
            }
            _exit(0);
        }
    }

    for (int i = 0;i<nProc;i++) {
        pid_t terminated_pid = wait(&status);
        if (WEXITSTATUS(status)>0) {
            linhasPresente[posLinhasPresente] = WEXITSTATUS(status)-1;
            posLinhasPresente++;
        }
    }

    if (!posLinhasPresente) return 0;

    quickSort(linhasPresente, 0, posLinhasPresente-1);

    for (int i = 0;i<posLinhasPresente;i++) {
        printf("Linha -> %d\n", linhasPresente[i]);
    }
    
    return 1;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int linhas = 8;
    int colunas = 20000000;

    int **matrix = (int**) malloc(linhas * sizeof(int *));
    for (int i = 0;i<linhas;i++) {
        matrix[i] = (int*) malloc(colunas * sizeof(int));
    }

    for (int i = 0;i<linhas;i++) {
        for (int j = 0;j<colunas;j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    if (existeElemento(matrix, linhas, colunas, atoi(argv[1]))) {
        printf("O valor %d foi encontrado\n", atoi(argv[1]));
    }
    else {
        printf("O valor %d não foi encontrado\n", atoi(argv[1]));
    }

    int queroImprimnir = 0;

    for (int i = 0;i<linhas & queroImprimnir;i++) {
        for (int j = 0;j<colunas;j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0;i<linhas;i++) {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}
