#include <stdio.h>

// argc will be the number of strings pointed to by argv 
// by default, the 1st arg is the name of the program that is being executed
int main(int argc, char* argv[], char* env[]) {
    printf("Command line variables\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    printf("Environment variables\n");
    int i = 0;
    while (env[i] != NULL) {
        printf("%s\n", env[i]);
        i++;
    }
}