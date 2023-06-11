#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#define FILENAME "OLA"

struct person {
    char name[200];
    int age;
};

int new_person(char* name, int age) {
    struct person pessoa;
    strcpy(pessoa.name, name);
    pessoa.age = age;

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0600);
    //lseek(fd, 0, SEEK_END);
    ssize_t r = write(fd, &pessoa, sizeof(struct person));
    if (r<0) {
        perror("Error");
        return -1;
    }

    printf ("%ld\n",lseek(fd, -sizeof(struct person), SEEK_CUR));

    close(fd);

    return 0;
}

int updateIdade(char *name, int age) {
    int fd = open(FILENAME, O_RDWR, 0600);

    ssize_t bytes;
    struct person pessoa;

    while ((bytes = read(fd, &pessoa, sizeof(struct person)))>0) {
        if (!strcmp(pessoa.name, name)) {
            pessoa.age = age;

            lseek(fd, -sizeof(struct person), SEEK_CUR);
            write(fd, &pessoa, sizeof(struct person));
            
            break;
        }
    }
    
    close(fd);
    return 1;
}

int updateIdadeIndex(int index, int age) {
    int fd = open(FILENAME, O_RDWR, 0600);

    lseek(fd, index+200, SEEK_CUR);

    write(fd, &age, 4);

    close(fd);

    return 1;
}

int main(int argc, char *argv[]) {

    if(argv[1][1]=='i') {
        new_person(argv[2], atoi(argv[3]));
    }
    else if (argv[1][1]=='u') {
        updateIdade(argv[2], atoi(argv[3]));
    }
    else if (argv[1][1]=='o') {
        updateIdadeIndex(atoi(argv[2]), atoi(argv[3]));
    }

    return 0;
}
