#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char caesar_chipper(char *text, int shift) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = (text[i] + (char)shift - 'A') % 26 + 'A';
        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = (text[i] + (char)shift - 'a') % 26 + 'a';
    }
}

int main() {
    char text[30] = "Download Success";

    pid_t child_id;
    child_id = fork();

    if (child_id != 0) {
        // char *argv[] = {"wget", "https://picsum.photos/763", NULL};
        // printf("wget %s\n", argv[1]);
        // execv("/bin/wget", argv);
        caesar_chipper(text, 5);
        printf("%s", text);
    }

    return 0;
}