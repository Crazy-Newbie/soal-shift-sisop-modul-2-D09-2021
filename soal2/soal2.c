#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char location[] = "/home/ezhie/modul2/petshop";


int main()
{
    pid_t pid1,pid2;

    if(pid1 < 0){
       return EXIT_FAILURE;
    }
    
    pid1 = fork();
    if(pid1 == 0){
        char *argv[] = {"mkdir", "-p", "-d", location, NULL};
        execv("/bin/mkdir", argv);
    }
    else
    {
        while((wait(&status)) > 0);
        pid2 = fork();
        if (pid2 == 0)
        {
            char *argv[] = {"unzip", "pets.zip", "-d", location, NULL};
            execv("/usr/bin/unzip", argv);
        }
        else
        {
            while((wait(&status)) > 0);
            pid3 = fork();
            if(pid3 == 0)
            {
                char *argv[] = {"rm", "-rf", "!", "-name", "'*.jpg'", location, NULL};
                execv("/bin/rm", argv);
            }
        }
        
        
    }

    return 0;

}
