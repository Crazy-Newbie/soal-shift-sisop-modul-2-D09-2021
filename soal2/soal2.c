#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char location[] = "/home/ezhie/modul2/petshop";
int status;
char keterangan[100];


void listFilesRecursively(char *Path){
  char path[1000];
  pid_t pid3, pid4, pid5, pid6;
  DIR *dir = opendir(Path);
  struct dirent *dp;
 
  if(!dir) return;
 
  while ((dp = readdir(dir)) ! =NULL){
	if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") != 0)
    {
    
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

        //2c
        char movefl[100] = "/home/ezhie/modul2/petshop/";
        strcat(movefl, dp->d_name);
        char filename[50] = "";
        strcpy(filename, dp->d_name);
        char s1[1] = ";";
        char s2[1] = "_";
        char s3[1] = ".j";

        pid4 = fork();

        if(!(strstr(dp->dp_name, deli2)))
        {
            
            if (pid4 == 0)
            {
                char *argv[] = {"mv", "-f", movefl, filename, NULL};
                char name[] = "";
                execv("/bin/mv", argv);
                strcpy(keterangan, newFile);
                strcat(keterangan, "keterangan.txt");
                fptr = fopen(keterangan, "a");
                int count = 2;
                for (int i = 1; i < 50; i++)
                {
                    if (count == 2)
                    {
                        if (filename[i]==s1[0])
                        {
                            count--;
                            fprintf(fptr, "nama : ");
                        }
                        continue;
                    }
                    
                    if (count == 1)
                    {
                        if (filename[i]==s1[0])
                        {
                            count--;
                            fprintf(fptr, "\numur : ");
                        }
                        fprintf(fptr,"%c", filename[i]);
                        strncat(name,&filename[i],1);
                        continue;
                    }
                    if(filename[i]==s3[0] && filename[i+1]==s3[1]){
                        fprintf(fptr, " tahun\n\n");
                        break;	
                    }
                    fprintf(fptr, "%c", filename[i]);

            }
            else
            {
                ((wait(&status))>0);
                pid5 = fork();
                strcpy(rename,newfile);
                strcat(rename,"/");
                strcat(rename,name);
                strcat(rename,".jpg");
                strcat(newfile,"/");
                strcat(newfile, dp->d_name);
                if (pid5 == 0)
                {
                    char *argv[] = {"mv",newfile,rename,NULL};
                    execv("/bin/mv", argv);
                }
            }
            

        }
        else
        {
            char copy[100] = "";
            char temp[10] = "";
            int flag = 1;

            int count2 = 2;
            pid5 = fork();
            
            if (pid5 == 0)
            {
                for(i = 0; i < 50; i++)
                {
                    if (count == 2)
                    {
                        if (filename[i]==s1[0])
                        {
                            count2--;
                            strcpy(cpyfile,locto);
                            strcat(cpyfile,"/");
                            strcat(cpyfile,temp);
                            char *argv6[] = {"mkdir","-p", cpyfile, NULL};
                            execv("/bin/mkdir", argv6);
                            char *argv7[] = {"cp", mvfile, cpyfile, NULL};
                            execv("/bin/cp", argv7);
                            char buatketerangan[50]="";
                            strcpy(buatketerangan,cpyfile);
                            strcat(buatketerangan,"/keterangan.txt");
                            fptr = fopen(buatketerangan,"a");
                            strcpy(temp,empty);
                            continue;
                        }
                        strcat(temp, &filename[i], 1);
                        continue;

                    }
                    
                }
            } else
            {
                ((wait(&status)) > 0);
            }
            
            
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
            listFilesRecursively(location);
        }
        
        
    }
    
    

    return 0;

}
