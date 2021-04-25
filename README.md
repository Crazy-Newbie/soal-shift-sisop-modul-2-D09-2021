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
# Soal 2
Soal nomor 2 ini diminta untuk mengkategorikan foto-foto peliharaan dari file ZIP yang diberikan untuk membantu Loba. Pengerjaan untuk soal ini menggunakan `fork` dan `exec`. 

# 2a
Diminta untuk mengextract File yang ada di `pets.zip`, dan di dalam file zip tersebut terdapat folder yang tidak diperlukan dan perlu dihapus. File yang ada di zip tersebut disimpan ke `/home/user/modul2/petshop`. 

Program ini diawali dengan pembuatan folder yang akan disimpan setelah mengextract file zip tersebut ke dalam lokasi yang telah di tentukan `/home/user/modul2/petshop`. Program akan berjalan setelah `pid1` ini melakukan `fork` dan `execv`. Perintah `execv` menggunakan `mkdir` untuk pembuatan folder tersebut. Folder tersebut dialokasikan di dalam `char location[] = "/home/user/modul2/petshop"`, dan dipanggil kedalam `execv` tersebut.

```
pid1 = fork();
    if(pid1 == 0){
        char *argv[] = {"mkdir", "-p", location, NULL};
        execv("/bin/mkdir", argv);
    }
```

Setelah itu dilakukan mengextract file `pets.zip` tersebut yang diawali dengan melakukan fork untuk `pid2` dan `execv`. Karena folder tidak dibutuhkan, di dalam command `execv` semua yang di extract adalah isi konten dari `pets.zip` yang file nya adalah tipe `.jpg`. 

```
pid2 = fork();
        if (pid2 == 0)
        {
            char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", location, NULL};
            execv("/usr/bin/unzip", argv);
        }
```


# 2b
Diminta untuk membuat folder untuk mengkategorikan setiap hewan. Untuk melakukan hal tersebut dipanggil fungsi `listFilesRecursively("/home/ezhie/modul2/petshop")` untuk melanjutkan program yang sedang berjalan untuk soal-soal berikutnya.


Memakai `struct dirent` dan `while ((dp = readdir(dir)) != NULL)` agar travers file dapat berjalan terus. Program akan mengambil string dari nama file hingga bertemu tanda ";" pertama, lalu lakukan mkdir agar membuat folder sesuai dengan jenis hewannya.

```
while ((dp=readdir(dir)) !=NULL){
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
        ...
```

# 2c

# 2d

# 2e

# Kendala 
1. Pada saat di nomor 2b program tidak berjalan di ubuntu saya tetapi di ubuntu orang lain bisa dan itu membuat saya tidak bisa cek apakah kodingan saya benar benar bisa atau tidak dan inilah yang membuat saya butuh bantuan teman saya untuk menjalankan program saya.
2. Program yang dijalankan terdapat error Segmentation fault (core dumped) dikarenakan pada kendala nomor satu di ubuntu saya

# Soal 3
Fork id1, id2, dan id3 untuk membuat child proses sebanyak 4  kali.
## 3.a
Buat nama direktori dan pathnya terlebih dahulu, menggunakan command; 
```
	strftime(dirname,100,"%Y-%m-%d_%X", localtime(&rawtime));
	sprintf(dirpath, "/home/rizaldinur/%s",dirname)
```
Kemudian manfaatkan fork untuk child yang paling awal, yakni `if(id1==0 && id2==0 && id3==0)` , lalu buat directory dengan command; 
```
	char *dirargv[] = {"mkdir", "-p",  dirpath, NULL};
	execv("/bin/mkdir",dirargv);  
```

## 3.b
Proses child selanjutnya, setelah menggunakan system call `wait()` untuk menunggu proses membuat directory selesai, lakukan download gambar dari url yang telah diberikan sebanyak 10 kali, dengan nama sesuai timestamp, dan tiap iterasi download dengan interval 5 detik. 
Buat nama file dan pathnya dulu dengan command ; 
```
	strftime(filename,100,"%Y-%m-%d_%X", localtime(&rawtime));
        sprintf(filepath, "%s/%s.jpg",dirpath,filename);
```
Tentukan ukuran foto sesuai epoch unix dan perhitungan di soal dengan command ; 
```
	size = (int)time(NULL);
        size=(size%1000)+50;
```
Perjelas url yang akan didownload, dengan menambahkan size dari foto di url;
```
	sprintf(url, "https://picsum.photos/%d", size);
```
Kemudian lakukan download gambar dengan command `wget`, sesuai dengan filepath yang telah dibuat;
```
	char *dlargv[] = {"wget", url,"-O", filepath, NULL};
        execv("/usr/bin/wget", dlargv);
```
## 3.c
Proses child selanjutnya, buat file `status.txt1` yang berisi status download yang telah di shift sejauh lima huruf menggunakan kode caesar cipher; 
```
	 else if(id1==0 && id2>0 && id3==0){
		while ((wait(&status)) > 0);
		FILE *dlog = fopen(statuspath, "w");
		caesarcipher(statusdl,5);
		fprintf(dlog,"%s", statusdl);
		fclose(dlog);
	 }
```
Kemudian setelah membuat file download status, lakukan zip pada direktori dan delete direktori tersebut, menggunakan command `-rm`, spesifiknya adlaah ; 
```
	else if(id1==0 && id2>0 && id3>0){
		while ((wait(&status)) > 0); //tunggu semua selesai, baru zip dan delete direktori
		sprintf(zipname, "%s.zip", dirname);
		char *zipargv[] = {"zip", "-rm",zipname, dirname,NULL};
		execv("/usr/bin/zip", zipargv);
    	}
```

Program utama diakhiri dengan command `sleep(40)` supaya program dieksekusi setiap interval 40 detik.

## 3.c dan 3.e
Membuat file bash script `killer.sh` untuk "membunuh" proses di atas, yakni dengan ; 
```
	 FILE* killer= fopen("killer.sh", "w");
	 fprintf(killer,"#!/bin/bash\nif [ \"$ARGV[1]\" = \"-z\" ];then\n\tkillall soal3\nelse\n\tPID=$(pidof soal3)\n\tkill -9 $PID\nfi");
	 fclose(killer);
```
