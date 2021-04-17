# soal-shift-sisop-modul-2-E01-2021
## Soal No.1

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi. 
### (a)
Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
### (b)
untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).
### (c)
Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta
### (d)
memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).
### (e)
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis `6 jam` sebelum waktu ulang tahun Stevany).
### (f)
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).

**Note :**
- Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
- Semua poin dijalankan oleh 1 script di latar belakang, termasuk mendownload file zip-nya. Jadi cukup jalankan script 1x serta ubah time dan date untuk check hasilnya.

> Preview :
https://drive.google.com/drive/folders/1NzRiPPoVlR_H8P51cxN4jaceeFQGk4un
> *tontonnya 720p biar jelas.. ಠ‿ಠ
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename() (Yang di bahasa C) .... FORBIDDENNN!!
- Tidak boleh pake cron !!!
- Menggunakan fork dan exec.
- Link
>Foto : https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view

> Musik : https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view

> Film : https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view

## Penyelesaian No. 1

Dikarenakan akan dikerjakan di latar belakang / background, maka akan digunakan daemon (template dari modul).

Berikut awalan code yang masih termasuk dalam template daemon di modul
```
int main() {
  pid_t pid, sid;       // Variabel untuk menyimpan PID
  
  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);


  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/nabil/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
```
Kecuali pada `chdir` diganti ke direktori user `/home/[user]` dalam hal ini `nabil` sebagai `user`
### 1.a dan 1.b
Dilakukan fork dan exec untuk mengeksekusi perintah pada bagian ini.
```
if (child_id == 0 && beda < 21600) {
	int idx;
	char *prog = "/usr/bin/wget";
	char *prog2 = "/bin/mkdir";
	char *argv[][6] = {  {prog,"--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O", "./Musik_for_Stefany.zip", NULL},
						{prog,"--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O", "./Foto_for_Stefany.zip", NULL},
						{prog,"--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O", "./Film_for_Stefany.zip", NULL} };
	char *argv2[][4] = { {prog2,"-p","./Musyik", NULL},
						{prog2,"-p","./Pyoto", NULL},
						{prog2,"-p","./Fylm", NULL} };
	for (idx = 0; idx < 6; idx++)
	{
		if (0 == fork()) continue;
		while ((wait(&status)) > 0);
		if(idx < 3)
		execv(prog, argv[idx]);
		else if(idx < 6)
		execv(prog2, argv2[idx-3]);
	}
	break;
	//perlu end
	// this is child
	}
```
Penggunaan `fork` dengan `for` untuk secara mudah menyesuaikan program `exec` yang dibutuhkan. `prog` dan `argv[]` untuk mendownload (1.b) dan `prog2` dan `argv2[]` untuk membuat folder baru.

### 1.c dan 1.d
Dilakukan fork dan exec untuk mengeksekusi perintah pada bagian ini.
```
if(flag == 0 && beda < 21600){
	int idx;
	while ((wait(&status)) > 0);
	sleep(7);
	char *prog3 = "/usr/bin/unzip";
	char *argv3[][6] = { {prog3,"-q","./Musik_for_Stefany.zip", "-d", "./", NULL},
						{prog3,"-q","./Foto_for_Stefany.zip", "-d", "./", NULL},
						{prog3,"-q","./Film_for_Stefany.zip", "-d", "./", NULL} };
	for (idx = 0; idx < 4; idx++)
	{
		if (0 == fork()) continue;
		sleep(7);
		if(idx < 3)
		execv(prog3, argv3[idx]);
	}
	sleep(5);
	glob_t globbuf[3];
	globbuf[0].gl_offs = 2;
	glob("./FOTO/*.jpg", GLOB_DOOFFS, NULL, &globbuf[0]);
	glob("./Pyoto/", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf[0]);
	globbuf[0].gl_pathv[0] = "cp";
	globbuf[0].gl_pathv[1] = "-R";
	globbuf[1].gl_offs = 2;
	glob("./MUSIK/*.mp3", GLOB_DOOFFS, NULL, &globbuf[1]);
	glob("./Musyik/", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf[1]);
	globbuf[1].gl_pathv[0] = "cp";
	globbuf[1].gl_pathv[1] = "-R";
	globbuf[2].gl_offs = 2;
	glob("./FILM/*.mp4", GLOB_DOOFFS, NULL, &globbuf[2]);
	glob("./Fylm/", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf[2]);
	globbuf[2].gl_pathv[0] = "cp";
	globbuf[2].gl_pathv[1] = "-R";
	
	for (idx = 0; idx < 4; idx++)
	{
		if (0 == fork()) continue;
		if(idx < 3)
		execvp("cp", &globbuf[idx].gl_pathv[0]);
	}
	flag = 1;
}
```
`prog3` dan `argv3` digunakan untuk unzip (1.c) caranya sama seperti pada bagian `1.a dan 1.b`, karena saat memindahkan terdapat wildcard maka digunakan `glob` untuk mengeksekusi `cp`.
### 1.e
Pengukuran `waktu` (time.h) di atur sejak awal dan berada pada awal setiap `if` dari `fork`.
```
struct tm t;

   t.tm_sec    = 0;
   t.tm_min    = 22;
   t.tm_hour   = 22;
   t.tm_mday   = 9;
   t.tm_mon    = 3;
   t.tm_year   = 121;
   t.tm_wday   = 5;

   double beda;

   time_t rawtime;

   pid_t child_id;
    int status;

    child_id = fork();

    // chdir("/home/nabil/");

  while (1) {
    time(&rawtime);
      beda = difftime(mktime(&t),rawtime);
      if (child_id < 0) {
         exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0 && beda < 21600) {
		  ...
```
### 1.f
Dilakukan fork dan exec untuk mengeksekusi perintah pada bagian ini.
```
if(flag && beda < 0){
	int stattt;
	if (0 == fork()){
	sleep(3);
	char *prog3 = "zip";
	char *argv3[7] = {prog3,"-r","./Lopyu_Stefany.zip", "./Musyik", "./Fylm","./Pyoto", NULL};
	execvp(prog3, argv3);
	} else {
	while ((wait(&stattt)) > 0);
	sleep(9);
	char *prog4 = "rm";
	char *argv4[9] = {prog4,"-rf", "./FILM","./FOTO","./MUSIK", "./Musyik", "./Fylm","./Pyoto", NULL};
	execvp(prog4, argv4);
	}
}
```
Penggunaan `fork` dengan `for` untuk secara mudah menyesuaikan program `exec` yang dibutuhkan. `prog3` dan `argv3[]` untuk Zip dan `prog4` dan `argv4[]` untuk mendelete folder2.

## Soal No.2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.
### 2.a
Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “**/home/[user]/modul2/petshop**”.Dan program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
### 2.b
Membuat program untuk mengkategorikan foto peliharaan sesuai jenis peliharaan, dengan membuat folder untuk setiap jenis peliharaan yang ada dalam zip. 
**Contoh:** 
Jenis peliharaan kucing akan disimpan dalam “**/petshop/cat**”, jenis peliharaan kura-kura akan disimpan dalam “**/petshop/turtle**”.
### 2.c
Setelah folder kategori berhasil dibuat, program dapat memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
**Contoh:** 
“**/petshop/cat/joni.jpg**”. 
### 2.d
Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. 
**Contoh:** 
foto dengan nama “**dog;baro;1_cat;joni;2.jpg**” dipindah ke folder “**/petshop/cat/joni.jpg**” dan “**/petshop/dog/baro.jpg**”.
### 2.e
Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun
```
**Catatan :**
- Setiap data peliharaan disimpan sebagai nama foto dengan format **[jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]**. Jika terdapat lebih dari satu peliharaan, data dipisahkan menggunakan underscore(_).
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename().
- Menggunakan fork dan exec.

## Penyelesaian No.2 :
### 2.a
Pertama dideklarasikan direktori petshop
```char PET_LOC[] = "/home/ridhojagis/modul2/petshop";```

Lalu dilakukan spawn proses dengan menggunakan ```fork()``` untuk melakukan proses pembuatan direktori petshop dan kemudian meng-unzip file **pets.zip** setelah direktori berhasil dibuat.
```
pid = fork();
if (pid == 0) 
{
    char *argv[] = {"mkdir", "-p", PET_LOC, NULL};
    execv("/bin/mkdir", argv);
}
else 
{
    while ((wait(&status)) > 0);
    unzip_pets();
    dir_pets();
}
```

```
void unzip_pets() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        char *argv[] = {"unzip", "/home/ridhojagis/Downloads/pets.zip",
                        "-x",    "*/*",
                        "-d",    PET_LOC,
                        NULL};
        execv("/usr/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    }
    while ((wait(&status)) > 0);
}
```
Digunakan ```-x */*``` agar folder beserta isi pada folder tersebut yang ada didalam zip tidak ikut ter unzip.

### 2.b
Untuk membuat folder kategori jenis peliharaan diperlukan travers pada setiap file untuk mendapatkan jenis peliharaan berdasarkan nama pada file tersebut.
```
void proses(char bin[], char *arg[]) {
    int status;
    pid_t pid;
    pid = fork();
    if (pid == 0)
        execv(bin, arg);
    else
        ((wait(&status)) > 0);
}

void mkdir_pets(char *filename) {
    char *token, *subtoken;
    char *saveptrtok, *saveptrsub;
    char save_filename[150];
    char *strptr = filename;

    strcpy(save_filename, filename);

    while (1) {
        char new_pet_dir[100];
        char old_pet_loc[200], new_pet_loc[200];

        token = strtok_r(strptr, "_", &saveptrtok);
        if (!token) break;

        // make dir pet
        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;

        sprintf(new_pet_dir, "%s/%s", PET_LOC, subtoken);
        char *argv_pet_dir[] = {"mkdir", "-p", new_pet_dir, NULL};
        proses("/bin/mkdir", argv_pet_dir);
        token = NULL;

	.

	.

	.
    }
}

void dir_pets() {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(PET_LOC);

    if (!dir) return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            char filename[30];
            strcpy(filename, dp->d_name);

            mkdir_pets(filename);
            del_pets(dp->d_name);
        }
    }
}
```
Pertama nama setiap file yang ditravers akan dimasukan ke dalam string ```filename[30]``` dengan menggunakan fungsi string copy ```strcpy(filename, dp->d_name)```. 
Kemudian digunakan ```new_pet_dir[100]``` untuk menyimpan string berupa direktori jenis peliharaan.

Karena setiap nama file dipisahkan dengan karakter "_" dan ";" maka digunakan strtok.
```token = strtok_r(strptr, "_", &saveptrtok)``` untuk memisahkan 2 jenis peliharaan dan ```subtoken = strtok_r(token, ";", &saveptrsub)``` untuk mengambil nama jenis peliharaan. 

```
sprintf(new_pet_dir, "%s/%s", PET_LOC, subtoken)
```
String dari nama jenis peliharaan yang didapatkan kemudian digabungkan dengan ```PET_LOC[]```(string direktori petshop) dan disimpan kedalam ```new_pet_dir[100]```.
Kemudian dilakukan proses untuk membuat direktori jenis peliharaan :
```
char *argv_pet_dir[] = {"mkdir", "-p", new_pet_dir, NULL};
proses("/bin/mkdir", argv_pet_dir);
```

### 2.c dan 2.d
Untuk memindahkan file berdasarkan kategori peliharaan kedalam folder kategorinya dapat dilakukan dengan cara mengcopy setiap file ke dalam kategori jenisnya dan sekaligus me-rename nama file tersebut. Setelah file berhasil ter-copy kedalam folder kategorinya, dilakukan delete untuk setiap file yang telah dicopy.
```
void del_pets(char *filename) {
    char filepath[200];
    sprintf(filepath, "%s/%s", PET_LOC, filename);

    char *argv[] = {"rm", "-f", filepath, NULL};
    proses("/bin/rm", argv);
}

void mkdir_pets(char *filename) {
    char *token, *subtoken;
    char *saveptrtok, *saveptrsub;
    char save_filename[150];
    char *strptr = filename;

    strcpy(save_filename, filename);

    while (1) {
        char new_pet_dir[100];
        char old_pet_loc[200], new_pet_loc[200];

       	.

	.

	.

        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;

        sprintf(old_pet_loc, "%s/%s", PET_LOC, save_filename);
        sprintf(new_pet_loc, "%s/%s.jpg", new_pet_dir, subtoken);
   
        char *argv_pet_loc[] = {"cp", old_pet_loc, new_pet_loc, NULL};
        proses("/bin/cp", argv_pet_loc);

	.

	.

	.
    }
}
```
dilakukan ```strtok_r(token, ";", &saveptrsub)``` untuk kedua kalinya agar mendapatkan nama dari pets tersebut. ```old_pet_loc[200]``` digunakan untuk menyimpan direktori file yang akan dicopy dan ```new_pet_loc[200]``` digunakan untuk menyimpan direktori tujuannya.

Setelah itu dilakukan proses copy file dari direktori lama ke direktori tujuan :
```
char *argv_pet_loc[] = {"cp", old_pet_loc, new_pet_loc, NULL};
proses("/bin/cp", argv_pet_loc);
```
```filepath[200]``` digunakan untuk menyimpan direktori file yang telah dicopy, dengan menggunakan ```sprintf(filepath, "%s/%s", PET_LOC, filename)```. 

Setelah file berhasil dicopy ke direktori tujuan, kemudian file yang telah dicopy akan dihapus.
```
char *argv[] = {"rm", "-f", filepath, NULL};
proses("/bin/rm", argv);
```

### 2.e
Untuk membuat file ```keterangan.txt``` dan mengisinya dengan nama serta umur dari tiap file dilakukan fungsi ```ket_append(new_pet_dir, name, cut_jpg(subtoken))```.
```
void mkdir_pets(char *filename) {
    char *token, *subtoken;
    char *saveptrtok, *saveptrsub;
    char save_filename[150];
    char *strptr = filename;

    // printf("test: %s\n", filename);
    strcpy(save_filename, filename);

    while (1) {
        char new_pet_dir[100];
        char old_pet_loc[200], new_pet_loc[200];

        .

	.

	.

        char name[20];
        strcpy(name, subtoken);

        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;

        ket_append(new_pet_dir, name, cut_jpg(subtoken));
        token = NULL;

        strptr = NULL;
    }
}
```
Sebelumnya dideklarasikan ```name[20]``` untuk menyimpan string berupa nama dari hewan peliharaan yang sebelumnya telah didapatkan. Untuk menyimpannya digunakan ```strcpy(name, subtoken)```.
Lalu dilakukan juga ```subtoken = strtok_r(token, ";", &saveptrsub)``` yang ketiga kalinya untuk mendapatkan umur dari hewan peliharaan pada file tersebut. 

Tapi dikarenakan hasil string dari subtoken masih terdapat ".jpg", oleh karena itu dilakukan pemotongan string dengan fungsi berikut :
```
char *cut_jpg(char *year) {
    int i;
    for (i = 0; i < strlen(year); i++) {
        if (year[i + 1] == '\0') return year;
        if (year[i + 1] == 'j' && year[i + 2] == 'p') {
            year[i] = '\0';
            return year;
        }
    }
}
```

String berupa umur yang telah didapatkan kemudian dipassing ke dalam fungsi ```ket_append```.
```
void ket_append(char *dir, char *name, char *year) {
    char text[100];
    char output[150];

    sprintf(text, "name\t: %s\numur\t: %s\n\n", name, year);
    sprintf(output, "%s/keterangan.txt", dir);
    FILE *fptrout = fopen(output, "a");
    fputs(text, fptrout);
    fclose(fptrout);
}
```
Pada fungsi ini digunakan ```text[100]``` yang berisikan string informasi nama serta umur dari file yang ditravers. Kemudian ```sprintf(output, "%s/keterangan.txt", dir)``` digunakan untuk menyimpan direktori file ```keterangan.txt``` ke dalam ```output[150]```.
Setelah itu dilakukan open file dengan menggunakan ```FILE *fptrout = fopen(output, "a")``` lalu didalam file tersebut dituliskan string ```text[100]``` dengan menggunakan ```fputs(text, fptrout)```.
