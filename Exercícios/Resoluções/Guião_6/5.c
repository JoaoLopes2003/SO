#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>

/*
    Neste exercício o caracter |, que representa o pipeline no terminal, foi substituído
    pelo caracter !, pois ao executar o programa no terminal, este assumia que estavamos
    a tentar fazer pipeline entre o nosso executável e os programas passados como argumento,
    dando um resultado que não o esperado.
*/



char*** parseComandos(char **linha, int n_Argumentos) {

    // Calcular número de comandos

    int n_Comandos = 1;
    for (int i = 1;linha[i]!=NULL;i++) {
        if (linha[i][0]=='!') {
            n_Comandos++;
        }
    }

    // Preencher a matrix de tamanho n_Comandos
    
    char ***comandos = (char***) malloc((n_Comandos+1) * sizeof(char**));
    comandos[n_Comandos] = NULL;

    int i, k;
    for (i = 0, k = 0;i<n_Argumentos;i++,k++) {

        // Calcular o número de argumentos

        int argc = 1;
        for (int j = i;linha[j]!=NULL && linha[j][0]!='!';j++) argc++;

        // Alocar memória para os argumentos

        comandos[k] = (char**) malloc(argc * sizeof(char*));

        int j;
        for (j = 0;j<argc-1;j++) {
            comandos[k][j] = strdup(linha[i+j]);
        }
        comandos[k][j] = NULL;
        i += argc-1;
    }

    return comandos;
}

void executePipeline(char ***comandos) {
    
    // Calcular número de comandos

    int n_Comandos = 0;
    for (int i = 0;comandos[i]!=NULL;i++) n_Comandos++;

    // Criar os pipes necessários

    int pipes[n_Comandos-1][2];

    for (int i = 0;i<n_Comandos-1;i++) {
        if (pipe(pipes[i])==-1) {
            perror("Pipe");
            _exit(1);
        }
    }

    // Executa os comandos
    for (int i = 0;i<n_Comandos;i++) {
        
        pid_t pid;
        if ((pid=fork())==-1) {
            perror("Fifo");
            _exit(1);
        }
        else if (pid==0) {
            // Redirecionar os descritores de inputs e outputs dos programas

            if (i>0) {
                if (dup2(pipes[i-1][0],STDIN_FILENO)==-1) {
                    perror("Dup2");
                    _exit(1);
                }
            }

            if (i<n_Comandos-1) {
                if (dup2(pipes[i][1],STDOUT_FILENO)==-1) {
                    perror("Dup2");
                    _exit(1);
                }
            }

            // Fechar todos os pipes

            for (int j = 0;j<n_Comandos-1;j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Executar o comando

            execvp(comandos[i][0],comandos[i]);
            perror("Exec");
            _exit(1);
        }
    }

    for (int i = 0;i<n_Comandos-1;i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0;i<n_Comandos;i++) {
        if (wait(NULL)==-1) {
            perror("Wait");
            _exit(1);
        }
    }
}

int main(int argc, char *argv[]) {

    // Fazer parsing dos comandos

    argv++;
    char ***comandos = parseComandos(argv, argc-1);

    // Executar o pipeline

    executePipeline(comandos);

    // Libertar a memória alocada para os comandos

    for (int i = 0;comandos[i]!=NULL;i++) {
        for (int j = 0;comandos[i][j]!=NULL;j++) {
            free(comandos[i][j]);
        }
        free(comandos[i]);
    }
    free(comandos);

    return 0;
}
