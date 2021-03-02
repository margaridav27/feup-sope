#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[], char* env[]) {
    DIR *dir;
    struct dirent *dp;

    if ((dir = opendir(argv[1])) == NULL) {
        printf("Failed to open the directory.\n");
    }

    while((dp = readdir(dir)) != NULL) {
        char *path = malloc(sizeof(argv[1]) + sizeof('/') + sizeof(dp->d_name));

        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path, dp->d_name);

        struct stat s;
        stat(path, &s);

        printf("Filename: %s - %ld bytes\n", dp->d_name, s.st_size);
    }

    closedir(dir);
}