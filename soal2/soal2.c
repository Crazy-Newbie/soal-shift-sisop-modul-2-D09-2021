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
  int status;
  char path[1000];
  pid_t pid3;
  DIR *dir = opendir(Path);
  struct dirent *dp;
 
  if(!dir) return;
 
  while ((dp = readdir(dir)) != NULL){
	if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") != 0){
    
  	//2B
  	//We need to split the file's name using delimiter
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
 	 
  	//2C
  	//Move each picture to the right folder
  	//char mfolder[100] = "/home/frozz/modul2/petshop";
  	//strcat(mfolder,dp->d_name);
  	//char petfile[100] = "";
  	//strcpy(petfile
 	 
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
            ((wait(&status)) > 0);
        }
        listFilesRecursively(location);
        
    }
    
    

    return 0;

}
