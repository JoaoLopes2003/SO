#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    execlp("ls", "ls", "-l", "--color", NULL);
    perror("Erro");

    return 0;
}
