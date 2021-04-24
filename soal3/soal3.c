#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void caesarcipher(char* rawstr,int key){
    char ch;
    int i;
    for (i=0;rawstr[i]!='\0';i++){
        ch = rawstr[i];
        if(ch>='a'&&ch<='z'){
            ch=ch+key;
            if (ch > 'z') ch = ch-'z'+'a'-1;
            rawstr[i] = ch;
        }
        else if(ch>='A'&&ch<='Z'){
            ch=ch+key;
            if (ch > 'Z') ch = ch-'Z'+'A'-1;
            rawstr[i] = ch;
        }
    }
}

int main() {
  pid_t pid, sid;        

  pid = fork();    

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }


  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  
  while (1) {
    int status,status2;
    time_t rawtime;
    pid_t id1, id2,id3;
    id1= fork();
    id2= fork();
    id3= fork();

    //3A. buat dir dulu
    char dirname[100];
    char dirpath[210];
    char filename[100];
    char url[100];
    char filepath[350];
    int size,i;
    char statuspath[250];
    char statusdl[] = "Download Success";
    char zipname[120];
    
    if(id1==0 && id2==0 && id3==0){
        time(&rawtime);
        strftime(dirname,100,"%Y-%m-%d_%X", localtime(&rawtime));
        sprintf(dirpath, "~/Soal3/%s",dirname);
        char *dirargv[] = {"mkdir", "-p",  dirpath, NULL};
        execv("/bin/mkdir",dirargv);  
    }
    //3B. download file dg nama format timestamp dan size tertentu
    //download 10x, tiap rentang 5s
    else if(id1==0 && id2==0 && id3>0){
        while ((wait(&status)) > 0);//tunggu buat dir first
        for(i=0;i<10;i++){
            time(&rawtime);
            strftime(filename,100,"%Y-%m-%d_%X", localtime(&rawtime));
            sprintf(filepath, "%s/%s.jpg",dirpath,filename);
            size = (int)time(NULL);
            size=(size%1000)+50;
            sprintf(url, "https://picsum.photos/%d", size);
            char *dlargv[] = {"wget","-O", filepath, url, NULL};
            execv("/usr/bin/wget", dlargv);
            
            sleep(5);
        }
    }
    
    else if(id1==0 && id2>0 && id3==0){
        while ((wait(&status)) > 0);//tunggu download selesai baru status txt
        sprintf(statuspath, "%s/status.txt",dirpath);
        char *txtargv[] = {"touch",statuspath,NULL };
        execv("/usr/bin/touch", txtargv);
    }
    //3C. status txt, cipher ,zip
    else if(id1==0 && id2>0 && id3>0){
        while ((wait(&status)) > 0);//tunggu buat status.txt first,baru isi
        caesarcipher(statusdl,5);    
        char *echoargv[] = {"echo",statusdl, ">" , statuspath};
        execv("usr/bin/echo",echoargv);
    }
    
    else if(id1>0 && id2==0 && id3==0){
        while ((wait(&status)) > 0); //tunggu semua selesai, baru zip dan delete direktori
        sprintf(zipname, "%s.zip", dirname);
        char *zipargv[] = {"zip", "-rm",zipname, dirpath};
        execv("/usr/bin/zip", zipargv);
    }
    
    sleep(40);
  }

}

