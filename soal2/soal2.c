#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

char PET_LOC[] = "/home/wisnupramoedya/modul2/petshop";

void proses(char bin[], char *arg[]) {
    int status;
    pid_t pid;
    pid = fork();
    if (pid == 0)
        execv(bin, arg);
    else
        ((wait(&status)) > 0);
}

void del_pets(char *filename) {
    char filepath[200];
    sprintf(filepath, "%s/%s", PET_LOC, filename);

    // printf("rm -f %s\n", filepath);
    char *argv[] = {"rm", "-f", filepath, NULL};
    proses("/bin/rm", argv);
}

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

void ket_append(char *dir, char *name, char *year) {
    char text[100];
    char output[150];

    sprintf(text, "name\t: %s\numur\t: %s\n\n", name, year);
    sprintf(output, "%s/keterangan.txt", dir);
    FILE *fptrout = fopen(output, "a");
    fputs(text, fptrout);
    fclose(fptrout);
}

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

        token = strtok_r(strptr, "_", &saveptrtok);
        if (!token) break;

        // printf("%s\n", token);

        // make dir pet
        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;
        // printf(" --> %s\n", subtoken);

        sprintf(new_pet_dir, "%s/%s", PET_LOC, subtoken);
        char *argv_pet_dir[] = {"mkdir", "-p", new_pet_dir, NULL};
        proses("/bin/mkdir", argv_pet_dir);
        token = NULL;

        // cp to location
        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;
        // printf(" ----> %s\n", subtoken);

        sprintf(old_pet_loc, "%s/%s", PET_LOC, save_filename);
        sprintf(new_pet_loc, "%s/%s.jpg", new_pet_dir, subtoken);
        // printf("cp %s %s\n", old_pet_loc, new_pet_loc);
        char *argv_pet_loc[] = {"cp", old_pet_loc, new_pet_loc, NULL};
        proses("/bin/cp", argv_pet_loc);
        token = NULL;

        // keterangan
        char name[20];
        strcpy(name, subtoken);

        subtoken = strtok_r(token, ";", &saveptrsub);
        if (!subtoken) break;
        // printf(" ----> %s\n", subtoken);

        ket_append(new_pet_dir, name, cut_jpg(subtoken));
        token = NULL;

        strptr = NULL;
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

void unzip_pets() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        char *argv[] = {"unzip", "/home/wisnupramoedya/Downloads/pets.zip",
                        "-x",    "*/*",
                        "-d",    PET_LOC,
                        NULL};
        execv("/usr/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    }
    while ((wait(&status)) > 0)
        ;
}

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) exit(EXIT_FAILURE);

    if (pid == 0) {
        char *argv[] = {"mkdir", "-p", PET_LOC, NULL};
        execv("/bin/mkdir", argv);
    } else {
        while ((wait(&status)) > 0)
            ;
        // soal 2a
        unzip_pets();

        // soal 2b
        dir_pets();
    }
}
