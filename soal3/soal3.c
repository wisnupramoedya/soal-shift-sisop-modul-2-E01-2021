#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

const char FILE_DIR[100] =
    "/home/wisnupramoedya/Programming/Bash/modul-2/"
    "soal-shift-sisop-modul-2-E01-2021/soal3";

typedef unsigned long long ull;

char caesar_chipper(char *text, int shift) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = (text[i] + (char)shift - 'A') % 26 + 'A';
        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = (text[i] + (char)shift - 'a') % 26 + 'a';
    }
}

void wait_rm_n_zip_dir(char *foldername) {
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) exit(EXIT_FAILURE);

    if (child_id == 0) {
        // this is child
        char text[30] = "Download Success";
        caesar_chipper(text, 5);

        char output[150];
        sprintf(output, "%s/%s/%s", FILE_DIR, foldername, "status.txt");
        FILE *fptrout = fopen(output, "w");
        fputs(text, fptrout);
        fclose(fptrout);

        char zip_filename[30];
        sprintf(zip_filename, "%s.zip", foldername);
        char *argv[] = {"zip", "-r", zip_filename, foldername, NULL};
        execv("/bin/zip", argv);
        exit(EXIT_SUCCESS);
    } else {
        // this is parent
        while (wait(&status) > 0)
            ;
        char *argv[] = {"rm", "-f", "-r", foldername, NULL};
        execv("/bin/rm", argv);
    }
}

void rm_n_zip_dir(char *foldername) {
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) exit(EXIT_FAILURE);

    if (child_id == 0) {
        // this is child
        wait_rm_n_zip_dir(foldername);
        exit(EXIT_SUCCESS);
    }
}

void image_download(char *url, char *filename) {
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) exit(EXIT_FAILURE);

    if (child_id == 0) {
        // this is child
        // printf("%s: %s\n", url, filename);
        char *argv[] = {"wget", url, "-q", "-O", filename, NULL};
        execv("/bin/wget", argv);
        exit(EXIT_SUCCESS);
    }
}

void image_setting(char *fileloc) {
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) exit(EXIT_FAILURE);

    if (child_id == 0) {
        int img_counter = 10;
        while (img_counter--) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            ull unix_epoch_sec = (ull)t;
            unix_epoch_sec = time(NULL);
            ull side = (unix_epoch_sec % 1000) + 50;
            char url[30];
            sprintf(url, "https://picsum.photos/%llu", side);
            // printf("%d. pid: %d child: %d\n%s\n", img_counter, getpid(),
            //        child_id, url);

            char filename[50];
            sprintf(filename, "%s/%04d-%02d-%02d_%02d:%02d:%02d.jpg", fileloc,
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                    tm.tm_min, tm.tm_sec);
            // printf("t %s\n", filename);

            image_download(url, filename);

            sleep(5);
        }

        exit(EXIT_SUCCESS);
    } else {
        while (wait(&status) > 0)
            ;
        rm_n_zip_dir(fileloc);
    }
}

void make_dir(char *filename) {
    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0) exit(EXIT_FAILURE);

    if (child_id == 0) {
        // this is child
        char *argv[] = {"mkdir", "-p", filename, NULL};
        execv("/bin/mkdir", argv);

        exit(EXIT_SUCCESS);
    } else {
        while (wait(&status) > 0)
            ;
        image_setting(filename);
    }
}

int main(int argc, char const *argv[]) {
    // 1. Get isi file .txt ke variabel string (fgets)
    // 2. Buat int counter nama file
    // 3. Write ke file baru .log sesuai nomor file
    // 4. Hapus isi semua file lama .txt

    pid_t pid, sid;  // Variabel untuk menyimpan PID
    pid = fork();    // Menyimpan PID dari Child Process

    // /* Keluar saat fork gagal
    //  * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // /* Keluar saat fork berhasil
    //  * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir(FILE_DIR)) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int counter = 3;
    while (counter--) {
        // Tulis program kalian di sini
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char date[25];
        sprintf(date, "%04d-%02d-%02d_%02d:%02d:%02d", tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

        // printf("%s\n", date);

        pid_t child_id;
        int status;

        child_id = fork();

        if (child_id < 0) exit(EXIT_FAILURE);

        if (child_id == 0) {
            make_dir(date);
            exit(EXIT_SUCCESS);
        }

        sleep(40);
    }

    return 0;
}