// wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext
// fyoto https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
// musyik https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
// fylm https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view

// fyoto wget --no-check-certificate "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download" -O Foto_for_Stefany.zip
// musyik wget --no-check-certificate "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" -O Musik_for_Stefany.zip
// fylm wget --no-check-certificate "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download" -O Film_for_Stefany.zip

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <glob.h>

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

  int flag = 0;
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
      } else if(child_id > 0){
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
         
         // this is parent
      }


    sleep(5);
  }
}