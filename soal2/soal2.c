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


void listFilesRecursively(char *Path){
  char path[1000];
  pid_t pid3;
  DIR *dir = opendir(Path);
  struct dirent *dp;
 
  if(!dir) return;
 
  while ((dp = readdir(dir)) != NULL){
	if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") != 0){
    
  	//2b
  	char token[100]= "";
  	strcpy(token,dp->d_name);
  	char pfolder[100] = "/home/ezhie/modul2/petshop/";
  	strtok(token,";");
  	strcat(pfolder,token);
  	pid3 = fork();
  	if(pid3 == 0){
    	char *argv3[] = {"mkdir","-p",pfolder,NULL};
    	execv("/usr/bin/mkdir",argv3);
  	}
  	else{
    	((wait(&status))>0);
  	}
 	 
  	strcpy(path,Path);
  	strcpy(path,"/");
  	strcat(path,dp->d_name);
 	 
  	listFilesRecursively(path);
	}
  }	 
 
  closedir(dir);  
} 	 


int main()
{
    pid_t pid1,pid2;

    if(pid1 < 0){
       return EXIT_FAILURE;
    }
    
    pid1 = fork();
    if(pid1 == 0){
        char *argv[] = {"mkdir", "-p", location, NULL};
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
            ((wait(&status)) > 0);
        }
        listFilesRecursively(location);
        
    }
    
    

    return 0;

}
