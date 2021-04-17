#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
 
char petloc[] = "/home/ridhojagis/modul2/petshop";

void proses(char bin[], char *arg[]) {
    int status;
    pid_t pid;
    pid = fork();
    if(pid == 0)
	execv(bin,arg);
    else 
	((wait(&status))>0);
    
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
	    

            char *token;
	    char filejenis[100] = "/home/ridhojagis/modul2/petshop/";
            strcpy(token,strtok(dp->d_name,";"));
	    strcat(filejenis,token);

      	    char *argv[4] = {"mkdir", "-p", filejenis, NULL};
            proses("/bin/mkdir", argv);

  	    char filejpg[100] = "/home/ridhojagis/modul2/petshop/";
	    strcat(filejpg,"\"");
	    strcat(filejpg,strcat(dp->d_name,"\""));
		//printf("%s", filejpg);

           // char *argv2[5] = {"mv", "-f", filejpg, filejenis, NULL};
           // proses("/bin/mv", argv2);

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}

int main() {
  pid_t pid1,pid2,pid3;
  int status,status2,status3;

  pid1 = fork();

  if (pid1 < 0) {
	exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (pid1 == 0) {
	char *argv[4] = {"mkdir", "-p", petloc, NULL};
	execv("/bin/mkdir", argv);
  } 
  else {
    while ((wait(&status)) > 0);
    pid2 = fork();

    if(pid2 == 0){
      char *argv[7] = {"unzip", "/home/ridhojagis/Downloads/pets.zip", "-x", "*/*", "-d", petloc, NULL};
      execv("/usr/bin/unzip", argv);
    }
    else {
      while ((wait(&status2)) > 0);
printf("Hello word\n" );
      listFilesRecursively(petloc);
    }
  }
}
