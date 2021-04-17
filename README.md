# soal-shift-sisop-modul-2-E01-2021

## Soal No.3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

### 3.a
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

### 3.b
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

### 3.c
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

### 3.d
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan **program bash**.

### 3.e
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Ranora meminta bantuanmu untuk membantunya dalam membuat program tersebut. Karena kamu anak baik dan rajin menabung, bantulah Ranora dalam membuat program tersebut!
Note:
- Tidak boleh menggunakan system() dan mkdir()
- **Program utama** merupakan **SEBUAH PROGRAM C**
- **Wajib** memuat algoritma Caesar Cipher pada program utama yang dibuat

## Penyelesaian No.3 :
Pada mulanya, kami menggunakan forking dan membuat program menjadi daemon. Hal ini menggunakan kodingan yang ada di Modul 2. Untuk isian akan menjadi seperti berikut.

### 3.a
Untuk membuat sebuah directory dengan format date sesuai timestamp YYYY-mm-dd_HH:ii:ss. Maka digunakan method date dan mempassing local time menuju struct tm. Lantas isian tersebut dipassing menjadi string ke dalam variabel string date.
```
time_t t = time(NULL);
struct tm tm = *localtime(&t);

char date[25];
sprintf(date, "%04d-%02d-%02d_%02d:%02d:%02d", tm tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
```

Hasil dari date lantas dipassing ke fungsi yang ada dari hasil fork child yang kami buat. Fungsi tersebut dinamakan make_dir(date). Lalu, dilakukan exit terhadap child tersebut.
```
pid_t child_id;
int status;

child_id = fork();

if (child_id < 0) exit(EXIT_FAILURE);

if (child_id == 0) {
    make_dir(date);
    exit(EXIT_SUCCESS);
}
```

Kodingan di atas ini akan menjadi format program child yang akan kami buat ke depannya. Serta karena akan berlangsung setiap 40 detik, maka dilakukan pemanggilan while dengan akhiran sleep(40).

Lalu, di dalam fungsi make_dir(date), dilakukan fork kembali dengan memanggil fungsi exec pada child. Algoritma pada child untuk membuat directory yang sudah dipassing sebagai berikut.
```
char *argv[] = {"mkdir", "-p", filename, NULL};
execv("/bin/mkdir", argv);
```

### 3.b
Karena setelah directory dibuat akan dilakukan download 10 foto, maka untuk program child akan dilakukan tunggu sebelum menjalankan program parent agar dipastikan directory sudah terbuat. Selanjutnya dilakukan pemanggilan fungsi image_setting(filename).
```
while (wait(&status) > 0)
    ;
image_setting(filename);
```

Di dalam fungsi tersebut, karena diperlukan mendownload foto persegi dengan ukuran (n%1000) + 50 px dengan n adalah detik Epoch Unix, maka dilakukan passing time(null) ke sebuah unsigned long long yang selanjutnya dihitung dengan rumus tersebut agar menjadi sisi persegi. Nilai tersebut lantas dimasukkan ke url.
```
ull unix_epoch_sec = (ull)t;
unix_epoch_sec = time(NULL);
ull side = (unix_epoch_sec % 1000) + 50;
char url[30];
sprintf(url, "https://picsum.photos/%llu", side);
```

Dengan cara yang sama dilakukan pembuatan filename file downloadan dengan format timestamp YYYY-mm-dd_HH:ii:ss.
```
char filename[50];
sprintf(filename, "%s/%04d-%02d-%02d_%02d:%02d:%02d.jpg", fileloc,
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
        tm.tm_min, tm.tm_sec);
```

Selanjutnya, kami memanggil fungsi utama yakni image download(url, filename). Tak lupa, dilakukan sleep(5) karena setiap 5 detik.
```
image_download(url, filename);

sleep(5);
```

Setiap image_download dibuatkan child program seperti di atas dengan isian child yang memanggil wget dengan exec.
```
char *argv[] = {"wget", url, "-q", "-O", filename, NULL};
execv("/bin/wget", argv);
exit(EXIT_SUCCESS);
```

### 3.c
Selanjutnya, kami mencoba memanggil fungsi rm_n_zip(dir) yang membuat child yang memanggil wait_rm_n_zip_dir(foldername).

Di dalam fungsi wait_rm_n_zip_dir(foldername), dilakukan pengubahan text "Download Success" ke encrypt Caesar Chipper dengan shift 5.
```
char text[30] = "Download Success";
caesar_chipper(text, 5);
```

Isian dari algoritma caesar chipper adalah mengubah text dan menggeser hurufnya 5 langkah. Di sini, dilakukan perbandingan sesuai huruf besar dan kecil dan penggeseran 5 langkah dengan modulo 26. Hitungan utama adalah berikut (text[i] + (char)shift - 'A') % 26 + 'A'. Yang dikembangkan menjadi:
```
int i;
for (i = 0; i < strlen(text); i++) {
    if (text[i] >= 'A' && text[i] <= 'Z')
        text[i] = (text[i] + (char)shift - 'A') % 26 + 'A';
    else if (text[i] >= 'a' && text[i] <= 'z')
        text[i] = (text[i] + (char)shift - 'a') % 26 + 'a';
}
```

Selanjutnya, tulisan dimasukkan ke output dengan file output "w".
```
char output[150];
sprintf(output, "%s/%s/%s", FILE_DIR, foldername, "status.txt");
FILE *fptrout = fopen(output, "w");
fputs(text, fptrout);
fclose(fptrout);
```

Selanjutnya, tetap di program child dilakukan zip dengan fungsi exec.
```
char zip_filename[30];
sprintf(zip_filename, "%s.zip", foldername);
char *argv[] = {"zip", "-r", zip_filename, foldername, NULL};
execv("/bin/zip", argv);
```

Program sebagai parent akan menunggu child selesai dan setelahnya menghapus directory yang tadinya sudah dizip dengan fungsi rm pada exec. Sehingga hanya menyisakan file zip saja.
```
while (wait(&status) > 0)
    ;
char *argv[] = {"rm", "-f", "-r", foldername, NULL};
execv("/bin/rm", argv);
```

### 3.d
Sebelum masuk ke while utama pada fungsi main. Program akan memanggil fungsi create_killer().

Di dalamnya, akan dilakukan pemanggilan child. Di mana akan dilakukan penulisan algoritma killer ke dalam file bash.
```
char output[100],
    text[] =
        "#!/bin/bash\nmyarr=($(ps aux | grep './soal3' | awk '{ print "
        "$2 }'))\nif [[ $1 = \"-z\" ]]\nthen\nfor i in "
        "\"${myarr[@]}\"\ndo\nkill -9 $i\ndone\nelif [[ $1 = \"-x\" "
        "]]\nthen\nkill -9 ${myarr[0]}\nfi\n";
printf("%s", text);
sprintf(output, "%s/killer.sh", FILE_DIR);
FILE *fptrout = fopen(output, "w");
fputs(text, fptrout);
fclose(fptrout);
```

### 3.e
Di dalam file bashnya, akan dilakukan fungsi if di mana apabila argumen -z akan mengkill seluruh fungsi yang digrep dengan nama soal3. Sedangkan -x akan mengkill program paling atas pada ps aux | grep './soal3' karena sebagai parent.
```
"#!/bin/bash\nmyarr=($(ps aux | grep './soal3' | awk '{ print "
"$2 }'))\nif [[ $1 = \"-z\" ]]\nthen\nfor i in "
"\"${myarr[@]}\"\ndo\nkill -9 $i\ndone\nelif [[ $1 = \"-x\" "
"]]\nthen\nkill -9 ${myarr[0]}\nfi\n"
```