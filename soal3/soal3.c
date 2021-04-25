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
  //3D buat program bash script killer
  FILE* killer= fopen("killer.sh", "w");
  fprintf(killer,"#!/bin/bash\nif [ \"$ARGV[1]\" = \"-z\" ];then\n\tkillall soal3\nelse\n\tPID=$(pidof soal3)\n\tkill -9 $PID\nfi");
  fclose(killer);
  
  
  if(fork()==0){
    char* modargv[]= {"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", modargv);
  }
  
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
    time(&rawtime);
    strftime(dirname,100,"%Y-%m-%d_%X", localtime(&rawtime));
    sprintf(dirpath, "/home/rizaldinur/%s",dirname);
    sprintf(statuspath, "%s/status.txt",dirpath);
    if(id1==0 && id2==0 && id3==0){
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
            char *dlargv[] = {"wget", url,"-O", filepath, NULL};
            execv("/usr/bin/wget", dlargv);
            
            sleep(5);
        }
    }
    else if(id1==0 && id2>0 && id3==0){//3C. status txt, cipher ,zip
        while ((wait(&status)) > 0);
        FILE *dlog = fopen(statuspath, "w");
        caesarcipher(statusdl,5);
        fprintf(dlog,"%s", statusdl);
        fclose(dlog);
    }
    else if(id1==0 && id2>0 && id3>0){
        while ((wait(&status)) > 0); //tunggu semua selesai, baru zip dan delete direktori
        sprintf(zipname, "%s.zip", dirname);
        char *zipargv[] = {"zip", "-rm",zipname, dirname,NULL};
        execv("/usr/bin/zip", zipargv);
    }
    
    sleep(40);
  }

}

