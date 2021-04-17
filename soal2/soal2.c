#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char location[] = "/home/ezhie/modul2/petshop";
int status;
struct dirent *dp;
DIR *dir = opendir(basePath);
FILE *fptr;
if (!dir)
    return;

int main()
{
    pid_t pid1,pid2,pid3,pid4;

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
        //2a
        pid2 = fork();
        if (pid2 == 0)
        {
            char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", location, NULL};
            execv("/usr/bin/unzip", argv);
        }
        else
        {
            while((wait(&status)) > 0);
            pid3 = fork();
            if(pid3 == 0)
            {
                while ((dp = readdir(dir)) != NULL)
                {
                    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
                    {
                        char token[100] = " ";
                        strcpy(token, dp->d_name);
                        char pfolderp[100] = "/home/ezhie/modul2/petshop";


                    }
                }
            }
        }
    }
    
    

    return 0;

}
