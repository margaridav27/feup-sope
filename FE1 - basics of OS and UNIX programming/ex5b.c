#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* env[]) {
    printf("Command line variables\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    printf("Environment variables\n");

    for (int i = 1; i < argc; i++) {
        int j = 0;
        while (env[j] != NULL) {
            if (strcmp(strtok(env[j], "="), argv[i]) == 0) {
                printf("%s", strtok(env[j], "\0")); // since every string ends with the null char
                printf("\n");
                break;
            }
            j++;
        }
    }

    /*
    for (int i = 1; i < argc; i++) {
        int j = 0;
        while (env[j] != NULL) {
            tok = strtok(env[j], delim);

            if (strcmp(tok, argv[i]) == 0) {

                while ((tok = strtok(NULL, delim))!= NULL) {
                    printf("%s", tok);
                }
                
                printf("\n");
                break;
            }

            j++;
        }
    } 
    */
}