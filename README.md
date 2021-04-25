# soal-shift-sisop-modul-2-D09-2021
# Soal 1
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

## 1.a
(a) membuat nama 3 file yaitu pyoto, fylm, dan musyik 
```
void direktori(){
    char *argv[] = {"mkdir", "Pyoto", "Fylm", "Musyik", NULL};
    execv("/bin/mkdir", argv); 
}
```

## 1.b
(b) download menggunakan **wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext**. 
```
void download(){
    int i, status[3];
    char *argv[3][200]={{"wget", "--no-check-certificate", "drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-q", "-o", "/dev/null", "-O", "Musik_for_Stevany.zip", NULL},
                          {"wget", "--no-check-certificate", "drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-q", "-o", "/dev/null", "-O", "Foto_for_Stevany.zip", NULL},
                          {"wget", "--no-check-certificate", "drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-q", "-o", "/dev/null", "-O", "Film_for_Stevany.zip", NULL}};                      
    for(i=0; i<3; i++)
    {
        if (0==fork()){
            while ((wait(&status[i])) > 0);
            continue;
        }
        else        
            execve("/usr/bin/wget", &argv[i][0], NULL);
    }
}
```

## 1.c
(c) meng-extract / unzip file setelah didownload 
```
void unzip(){
    char *argv2[3][100]={{"unzip", "-q", "Musik_for_Stevany.zip", NULL},
                         {"unzip", "-q", "Foto_for_Stevany.zip", NULL},
                         {"unzip", "-q", "Film_for_Stevany.zip", NULL}};
    int i, status[3];
    for(i=0; i<3; i++){
        if(0==fork()){
            while ((wait(&status[i])) > 0);
            continue;
        }
        else
            execve("/usr/bin/unzip", &argv2[i][0], NULL);              
    }
}
```
