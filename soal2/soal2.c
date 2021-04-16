#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t pid1;

    if(pid1 < 0){
        exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        char *argv[] = {"unzip", "pets.zip", "-d", "/home/ezhie/praktikum_2/soal2", NULL};
        execv("/usr/bin/unzip", argv);
    }

    return 0;

}
