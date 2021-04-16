#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid1;

    if(pid1 < 0){
        exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        char *argv[] = {"unzip", "pets.zip", NULL};
        execv("/ezhie/bin/unzip", argv);
    }
    
    return 0;

}