#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

char buffer[256];
char dirr[12][256];
char *cmd[10];

int main(int argc, char *argv[]){

    if(argc == 1){

        FILE *fp = fopen("movedir.txt", "r");

        if(fp != NULL){
            for(int i = 0; i < 2; i++){
                fgets(dirr[i], sizeof(dirr[i]), fp);
                dirr[i][strcspn(dirr[i], "\n")] = '\0';
            }
        }

        else {
            perror("file");
            printf("your 'movedir.txt' is non-existent. please re-launch this program in the following format './automove <dir1> <dir2>'.\n");
            exit(1);
        }

        fclose(fp);

        char watchdir[256];
        strcpy(watchdir, dirr[0]);

        char *star = strstr(watchdir, "/*");

        if(star != NULL){
            *star = '\0';
        }

        while(1){

            DIR *dir = opendir(watchdir);

            if(dir == NULL){
                perror("opendir");
                exit(1);
            }

            struct dirent *entry;
            int empty = 1;

            while((entry = readdir(dir)) != NULL){
                if(strcmp(entry->d_name, ".") != 0 &&
                   strcmp(entry->d_name, "..") != 0){
                    empty = 0;
                    break;
                }
            }

            closedir(dir);

            if(!empty){

                char command[512];

                snprintf(command, sizeof(command),
                         "sudo mv %s %s",
                         dirr[0], dirr[1]);

                pid_t pid = fork();

                if(pid == 0){
                    char *args[] = {
                        "sh",
                        "-c",
                        command,
                        NULL
                    };

                    execvp("sh", args);

                    perror("execvp");
                    exit(1);
                }

                else if(pid > 0){
                    waitpid(pid, NULL, 0);
                }

                else {
                    perror("fork");
                    exit(1);
                }
            }
            sleep(3);
        }
    }

    if(argc == 3){

        FILE *fpin = fopen("movedir.txt", "w");

        if(fpin == NULL){
            perror("movedir.txt");
            return 1;
        }

        fprintf(fpin, "%s\n", argv[1]);
        fprintf(fpin, "%s\n", argv[2]);

        fclose(fpin);
    }

    if(argc == 2){

        if(strcmp(argv[1], "clear") == 0){

            FILE *fclr = fopen("movedir.txt", "w");

            if(fclr == NULL){
                perror("movedir.txt");
                return 1;
            }

            fclose(fclr);
        }
    }

    return 0;
}
