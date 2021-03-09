#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int func(char* p) {
    DIR *dir;
    struct dirent *dp;

    if ((dir = opendir(p)) == NULL) {
        perror("opendir()");
        return 1;
    }

    while((dp = readdir(dir)) != NULL) {
        char *path = malloc(sizeof(p) + sizeof('/') + sizeof(dp->d_name));
        sprintf(path, "%s/%s", p, dp->d_name);

        struct stat s;
        stat(path, &s);

        if (S_ISREG(s.st_mode)) {
            printf("%s : %ld bytes\n", dp->d_name, s.st_size);
        } 
        else if (S_ISDIR(s.st_mode) && strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            int pid = fork();
            if (pid == 0) {
                func(path);
                return 0;
            } else {
                wait(NULL);
            }
        }  

        free(path);      
    }

    closedir(dir);
    return 0;
}

int main(int argc, char* argv[], char* env[]) {
    func(argv[1]);
    return 0;    
}